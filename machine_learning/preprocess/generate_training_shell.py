import os, sys,json
from collections import OrderedDict

def read_config(cfg_path):
    with open(cfg_path, 'rb') as fh:
        cfg_dict = json.load(fh, object_pairs_hook=OrderedDict)
    return cfg_dict

def write_config(cfg_dict, cfg_path):
    with open(cfg_path, 'wb') as fh:
        fh.write(json.dumps(cfg_dict, indent=4))

def update_config_files(config):
    cwd = os.getcwd()
    pysie_dir = os.path.dirname(os.path.dirname(cwd))

    pysie_cfg_path = os.path.join(pysie_dir, "feature_extraction", 'pysie.cfg')
    talos_cfg_path = os.path.join(pysie_dir, "feature_extraction", 'talos.cfg')
    training_cfg_path = os.path.join(pysie_dir, "machine_learning", 'training_process', 'config.json')

    pysie_cfg_dict = read_config(pysie_cfg_path)
    talos_cfg_dict = read_config(talos_cfg_path)
    training_cfg_dict = read_config(training_cfg_path)

    # 1. multi thread config
    pysie_cfg_dict["common"]["use_system_cpu_num"] = config['common']['use_system_cpu_num']
    talos_cfg_dict["common"]["use_system_cpu_num"] = config['common']['use_system_cpu_num']
    training_cfg_dict["model"]["xgboost"]["use_system_cpu_num"]= config['common']['use_system_cpu_num']

    pysie_cfg_dict["common"]["thread_num"] = config['common']['thread_num']
    talos_cfg_dict["common"]["process_num"] = config['common']['thread_num']
    training_cfg_dict["model"]["xgboost"]["nthread"] = config['common']['thread_num']
    
    # 2. training config
    training_cfg_dict["model"]["xgboost"]["model_name"] = config['common']['model_name']
    training_cfg_dict["train"]["search_best_params"] = config['common']['search_best_params']
    training_cfg_dict["filesystem"]["mid_folder"] = config['common']['mid_folder']

    # 3. write config
    write_config(pysie_cfg_dict, pysie_cfg_path)
    write_config(talos_cfg_dict, talos_cfg_path)
    write_config(training_cfg_dict, training_cfg_path)

def parse(config, shell_filepath):
    # 1. upate pysie.cfg, config.json
    update_config_files(config)

    # 2. generate shell
    mid_folder = config['common']['mid_folder']
    train_sample_set_list = []
    for feature_dest_file in config["filesystem"]["training_set_malicious"]:
        train_sample_set_list.append([config["filesystem"]["training_set_malicious"][feature_dest_file], 1, os.path.join(mid_folder, feature_dest_file)])
    for feature_dest_file in config["filesystem"]["training_set_normal"]:
        train_sample_set_list.append([config["filesystem"]["training_set_normal"][feature_dest_file], 0, os.path.join(mid_folder, feature_dest_file)])
    
    validation_sample_set_list = []
    for feature_dest_file in config["filesystem"]["validation_set_malicious"]:
        validation_sample_set_list.append([config["filesystem"]["validation_set_malicious"][feature_dest_file], 1, os.path.join(mid_folder, feature_dest_file)])
    for feature_dest_file in config["filesystem"]["validation_set_normal"]:
        validation_sample_set_list.append([config["filesystem"]["validation_set_normal"][feature_dest_file], 0, os.path.join(mid_folder, feature_dest_file)])

    with open(shell_filepath, 'wb') as fh:
        fh.write("pysie_dir={}\n".format(os.path.dirname(os.path.dirname(os.getcwd()))))
        fh.write("mkdir -p {}\n".format(mid_folder))
        # 1. dump feature
        fh.write("\n\n# dump feature\n")
        fh.write("cd $pysie_dir/feature_extraction\n")
        for sample_set in (train_sample_set_list + validation_sample_set_list):
            if config["common"]["use_talos"]:
                program = "talos.py"
            else:
                program = "pysie.py"
            fh.write("python {} --dump-feature {} --label {} --dest-file {}\n".format(program, sample_set[0], sample_set[1], sample_set[2]))
        
        # 2. cat train.txt
        fh.write("\n\n# cat train.txt\n")
        pysie_train_file_path = os.path.join(mid_folder, 'train.txt')
        
        fh.write("rm {}\n".format(pysie_train_file_path))
        for sample_set in train_sample_set_list:
            fh.write("cat {} >> {}\n".format(sample_set[2], pysie_train_file_path))

        # 4. training
        fh.write("\n\n# training\n")

        pysie_training_log_path = os.path.join(mid_folder, 'training.log')        
        fh.write("rm {}\n".format(pysie_training_log_path))
        fh.write("cd $pysie_dir/machine_learning/training_process\n")
        fh.write("python train.py -d {} >> {}\n".format(pysie_train_file_path, pysie_training_log_path))

        # 5. predict
        fh.write("\n\n# predicting\n")
        for sample_set in validation_sample_set_list:
            fh.write("python predict.py -d {} >> {}\n".format(sample_set[2], pysie_training_log_path))
    print """
    Generate shell file to >> {}
    Don't forget chmod before you run it
    """.format(shell_filepath)

if __name__ == '__main__':
    if len(sys.argv) != 2 or sys.argv[1] == "-h":
        print "usage: python generate_training_shell.py shell_path"
    else:
        with open("model_training_config.json", 'rb') as fh:
            try:
                config = json.load(fh)
            except:
                print "[Error] Load model_training_config.json fail!"
                exit(-1)
            parse(config, sys.argv[1])