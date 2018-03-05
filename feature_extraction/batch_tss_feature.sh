# python pysie.py --dump-feature /sa/sample/TSS_Generic_sample/malicious/ --label 1 --dest-file /sa/middle_dir/tss_test/tss_malicious.txt
# python pysie.py --dump-feature /sa/sample/TSS_Generic_sample/normal/ --label 0 --dest-file /sa/middle_dir/tss_test/tss_normal.txt
# python pysie.py --dump-feature /sa/sample/html/normal/HTML/crawled_web_pages --label 0 --dest-file /sa/middle_dir/tss_test/html_normal_crawled.txt

# cd ../machine_learning/preprocess/
# python split.py /sa/middle_dir/tss_test/tss_malicious.txt 0.5
# python split.py /sa/middle_dir/tss_test/tss_normal.txt 0.5
# python split.py /sa/middle_dir/tss_test/html_normal_crawled.txt 0.5
# cat /sa/middle_dir/tss_test/tss_malicious_random_0.5_group_a.txt > /sa/middle_dir/tss_test/tss_train.txt
# cat /sa/middle_dir/tss_test/tss_normal_random_0.5_group_a.txt >> /sa/middle_dir/tss_test/tss_train.txt
# cat /sa/middle_dir/tss_test/html_normal_crawled_random_0.5_group_a.txt >> /sa/middle_dir/tss_test/tss_train.txt
# cat /sa/middle_dir/tss_test/tss_malicious_random_0.5_group_b.txt > /sa/middle_dir/tss_test/tss_test.txt
# cat /sa/middle_dir/tss_test/tss_normal_random_0.5_group_b.txt >> /sa/middle_dir/tss_test/tss_test.txt
# cat /sa/middle_dir/tss_test/html_normal_crawled_random_0.5_group_b.txt >> /sa/middle_dir/tss_test/tss_test.txt

# cd ../../feature_extraction/
# python pysie.py --dump-feature /sa/sample/html/unique/malicious/ --label 1 --dest-file /sa/middle_dir/tss_test/malicious_unique.txt
# python pysie.py --dump-feature /sa/sample/html/unique/normal/ --label 0 --dest-file /sa/middle_dir/tss_test/normal_unique.txt

# cd ../machine_learning/training_process/
# python train.py /sa/middle_dir/tss_test/tss_train.txt
# python predict.py /sa/middle_dir/tss_test/tss_test.txt
# python predict.py /sa/middle_dir/tss_test/malicious_unique.txt
# python predict.py /sa/middle_dir/tss_test/normal_unique.txt


cd /sa/github/pysie/feature_extraction
# python pysie.py --dump-feature /sa/sample/coin_miner/CoinHive_malicious/ --label 1 --dest-file /sa/middle_dir/coin_miner/coin_miner_malicious.txt
# python pysie.py --dump-feature /sa/sample/coin_miner/CoinHive_Normal/ --label 0 --dest-file /sa/middle_dir/coin_miner/coin_miner_normal.txt
# python pysie.py --dump-feature /sa/sample/html/normal/HTML/crawled_web_pages --label 0 --dest-file /sa/middle_dir/coin_miner/html_normal_crawled.txt
python pysie.py --dump-feature /sa/sample/coin_miner/fp_in_normal_unique --label 0 --dest-file /sa/middle_dir/coin_miner/fp_in_normal_unique.txt

cd ../machine_learning/preprocess/
# python split.py /sa/middle_dir/coin_miner/coin_miner_malicious.txt 0.5
# python split.py /sa/middle_dir/coin_miner/coin_miner_normal.txt 0.5
# python split.py /sa/middle_dir/coin_miner/html_normal_crawled.txt 0.5
python split.py /sa/middle_dir/coin_miner/fp_in_normal_unique.txt 0.5
# cat /sa/middle_dir/coin_miner/coin_miner_malicious_random_0.5_group_a.txt > /sa/middle_dir/coin_miner/coin_miner_train.txt
# cat /sa/middle_dir/coin_miner/coin_miner_normal_random_0.5_group_a.txt >> /sa/middle_dir/coin_miner/coin_miner_train.txt
# cat /sa/middle_dir/coin_miner/html_normal_crawled_random_0.5_group_a.txt >> /sa/middle_dir/coin_miner/coin_miner_train.txt
cat /sa/middle_dir/coin_miner/fp_in_normal_unique_random_0.5_group_a.txt >> /sa/middle_dir/coin_miner/coin_miner_train.txt
# cat /sa/middle_dir/coin_miner/coin_miner_malicious_random_0.5_group_b.txt > /sa/middle_dir/coin_miner/coin_miner_test.txt
# cat /sa/middle_dir/coin_miner/coin_miner_normal_random_0.5_group_b.txt >> /sa/middle_dir/coin_miner/coin_miner_test.txt
# cat /sa/middle_dir/coin_miner/html_normal_crawled_random_0.5_group_b.txt >> /sa/middle_dir/coin_miner/coin_miner_test.txt
cat /sa/middle_dir/coin_miner/fp_in_normal_unique_random_0.5_group_b.txt >> /sa/middle_dir/coin_miner/coin_miner_test.txt

cd ../../feature_extraction/
# python pysie.py --dump-feature /sa/sample/html/unique/malicious/ --label 1 --dest-file /sa/middle_dir/coin_miner/malicious_unique.txt
# python pysie.py --dump-feature /sa/sample/html/unique/normal/ --label 0 --dest-file /sa/middle_dir/coin_miner/normal_unique.txt

cd ../machine_learning/training_process/
python train.py /sa/middle_dir/coin_miner/coin_miner_train.txt
python predict.py /sa/middle_dir/coin_miner/coin_miner_test.txt
python predict.py /sa/middle_dir/coin_miner/malicious_unique.txt
python predict.py /sa/middle_dir/coin_miner/normal_unique.txt




# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180203/malicoius/ --label 1 --dest-file 20180203_mal.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180203/montoring/ --label 0 --dest-file 20180203_mon.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180203/GenericWarn/ --label 0 --dest-file 20180203_gen.txt

# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180204/malicoius/ --label 1 --dest-file 20180204_mal.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180204/montoring/ --label 0 --dest-file 20180204_mon.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180204/GenericWarn/ --label 0 --dest-file 20180204_gen.txt

# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180205/malicoius/ --label 1 --dest-file 20180205_mal.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180205/montoring/ --label 0 --dest-file 20180205_mon.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180205/GenericWarn/ --label 0 --dest-file 20180205_gen.txt

# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180206/malicoius/ --label 1 --dest-file 20180206_mal.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180206/montoring/ --label 0 --dest-file 20180206_mon.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180206/GenericWarn/ --label 0 --dest-file 20180206_gen.txt

# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180207/malicoius/ --label 1 --dest-file 20180207_mal.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180207/montoring/ --label 0 --dest-file 20180207_mon.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180207/GenericWarn/ --label 0 --dest-file 20180207_gen.txt

# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180208/malicoius/ --label 1 --dest-file 20180208_mal.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180208/montoring/ --label 0 --dest-file 20180208_mon.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180208/GenericWarn/ --label 0 --dest-file 20180208_gen.txt

# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180209/malicoius/ --label 1 --dest-file 20180209_mal.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180209/montoring/ --label 0 --dest-file 20180209_mon.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180209/GenericWarn/ --label 0 --dest-file 20180209_gen.txt

# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180210/malicoius/ --label 1 --dest-file 20180210_mal.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180210/montoring/ --label 0 --dest-file 20180210_mon.txt
# python pysie.py --dump-feature /sa/tss/get_sample_from_spn/20180210/GenericWarn/ --label 0 --dest-file 20180210_gen.txt

# cd ../machine_learning/training_process/

# python predict.py /sa/github/pysie/feature_extraction/20180203_mal.txt
# python predict.py /sa/github/pysie/feature_extraction/20180203_mon.txt
# python predict.py /sa/github/pysie/feature_extraction/20180203_gen.txt

# python predict.py /sa/github/pysie/feature_extraction/20180204_mal.txt
# python predict.py /sa/github/pysie/feature_extraction/20180204_mon.txt
# python predict.py /sa/github/pysie/feature_extraction/20180204_gen.txt

# python predict.py /sa/github/pysie/feature_extraction/20180205_mal.txt
# python predict.py /sa/github/pysie/feature_extraction/20180205_mon.txt
# python predict.py /sa/github/pysie/feature_extraction/20180205_gen.txt

# python predict.py /sa/github/pysie/feature_extraction/20180206_mal.txt
# python predict.py /sa/github/pysie/feature_extraction/20180206_mon.txt
# python predict.py /sa/github/pysie/feature_extraction/20180206_gen.txt

# python predict.py /sa/github/pysie/feature_extraction/20180207_mal.txt
# python predict.py /sa/github/pysie/feature_extraction/20180207_mon.txt
# python predict.py /sa/github/pysie/feature_extraction/20180207_gen.txt

# python predict.py /sa/github/pysie/feature_extraction/20180208_mal.txt
# python predict.py /sa/github/pysie/feature_extraction/20180208_mon.txt
# python predict.py /sa/github/pysie/feature_extraction/20180208_gen.txt

# python predict.py /sa/github/pysie/feature_extraction/20180209_mal.txt
# python predict.py /sa/github/pysie/feature_extraction/20180209_mon.txt
# python predict.py /sa/github/pysie/feature_extraction/20180209_gen.txt

# python predict.py /sa/github/pysie/feature_extraction/20180210_mal.txt
# python predict.py /sa/github/pysie/feature_extraction/20180210_mon.txt
# python predict.py /sa/github/pysie/feature_extraction/20180210_gen.txt
