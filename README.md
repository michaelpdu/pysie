# pysie
This project is to build HTML/JS feature extraction and model trainning

## Feature Extraction

### pysie.py
In feature_extraction, you could use *pysie.py* to extract features and dump in libsvm data format.

```
>> python pysie.py --dump-feature target_path --label label --dest-file [dest_file_path]
Note:
    a) if dest_file_path is not specified, feature list will be dumped into original_file_name.libsvm.fea
    b) label is 1 or 0, here 1 indicates malicious, 0 indicates normal
```

### talos.py
For TMSIE's compatiblity, you could use *talos.py* to extract features and dump in libsvm data format.

```
>> python talos.py --dump-feature target_path --label label --dest-file [dest_file_path]
Note:
    a) if dest_file_path is not specified, feature list will be dumped into original_file_name.libsvm.fea
    b) label is 1 or 0, here 1 indicates malicious, 0 indicates normal
```

## Split Feature Data and Generate Training&Testing Set

In machine_learning/preprocess, you could find *sploit.py* which could be used to sploit data file into two parts randomly.

```
python split.py /sa/middle_dir/tss_test/tss_malicious.txt 0.5
python split.py /sa/middle_dir/tss_test/tss_normal.txt 0.5
python split.py /sa/middle_dir/tss_test/html_normal_crawled.txt 0.5
cat /sa/middle_dir/tss_test/tss_malicious_random_0.5_group_a.txt > /sa/middle_dir/tss_test/tss_train.txt
cat /sa/middle_dir/tss_test/tss_normal_random_0.5_group_a.txt >> /sa/middle_dir/tss_test/tss_train.txt
cat /sa/middle_dir/tss_test/html_normal_crawled_random_0.5_group_a.txt >> /sa/middle_dir/tss_test/tss_train.txt
cat /sa/middle_dir/tss_test/tss_malicious_random_0.5_group_b.txt > /sa/middle_dir/tss_test/tss_test.txt
cat /sa/middle_dir/tss_test/tss_normal_random_0.5_group_b.txt >> /sa/middle_dir/tss_test/tss_test.txt
cat /sa/middle_dir/tss_test/html_normal_crawled_random_0.5_group_b.txt >> /sa/middle_dir/tss_test/tss_test.txt
```

## Build Model and Verify Effectiveness

In machine_learning/training_process, you could use *train.py* and *predict.py* to build model and verify effectiveness.

```
python train.py /sa/middle_dir/coin_miner/coin_miner_train.txt
python predict.py /sa/middle_dir/coin_miner/coin_miner_test.txt
python predict.py /sa/middle_dir/coin_miner/malicious_unique.txt
python predict.py /sa/middle_dir/coin_miner/normal_unique.txt
```

## Config for Feature Extraction

In pysie.cfg, there're many configurations for feature extraction.

```
    "common": {
        "use_system_cpu_num": true,
        "thread_num": 4
    },
```
If **thread_num** is 1, it will be single process mode, no matter what vaule in **use_system_cpu_num**. When **thread_num** is larger than 1 and **use_system_cpu_num** is false, pysie.py will fork *thread_num* processes to execute feature extraction. If **thread_num** is larger than 1 and **use_system_cpu_num** is true, there will be *cpu_num* working processes.

More detailed information about feature extraction, please refer to pysie.cfg

## Config for Machine Learning

In config.json, you could specify **mid_folder** for your training process. In following case, mid_folder is */sa/middle_dir/coin_miner*. Besides that, you also could specify which machine learning algrithm could be used and whether search best parameters in training process. It supports xgboost, libsvm and Deep Learning(keras) now. And Keras is still on the developing.

```
{
  "version": "1.0.1000",
  "filesystem": {
    "mid_folder": "/sa/middle_dir/coin_miner"
  },
  "train": {
    "__train_comments__": {
        "option for model":"[svm|xgboost|libsvm|keras]"
    },
    "model": "xgboost",
    "search_best_params": true
  },
  "model": {
    "svm": {
      "model_name": "svm_linear.model",
      "kernel": "linear"
    },
    "xgboost": {
      "model_name": "xgb.model",
      "use_system_cpu_num": true,
      "nthread": 4
    },
    "libsvm": {
      "model_name": "libsvm_linear.model"
    },
    "keras": {
      "model_name": "keras.h5",
      "num_classes": 2,
      "batch_size": 128,
      "epochs": 20,
      "input_dim": 11001
    }
  }
}

```









