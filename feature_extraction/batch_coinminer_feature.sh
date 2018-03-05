
cd /sa/github/pysie/feature_extraction
#python pysie.py --dump-feature /sa/sample/coinminer/malicious --label 1 --dest-file /sa/middle_dir/coin_miner_cy/coin_miner_malicious.txt
#python pysie.py --dump-feature /sa/sample/coinminer/normal --label 0 --dest-file /sa/middle_dir/coin_miner_cy/coin_miner_normal.txt
cat /sa/middle_dir/coin_miner_cy/coin_miner_malicious.txt > /sa/middle_dir/coin_miner_cy/coin_miner_test.txt
cat /sa/middle_dir/coin_miner_cy/coin_miner_normal.txt >> /sa/middle_dir/coin_miner_cy/coin_miner_test.txt
#python pysie.py --dump-feature /sa/sample/coin_miner/CoinHive_Normal/ --label 0 --dest-file /sa/middle_dir/coin_miner_cy/coin_miner_normal.txt
#python pysie.py --dump-feature /sa/sample/html/normal/HTML/crawled_web_pages --label 0 --dest-file /sa/middle_dir/coin_miner_cy/html_normal_crawled.txt


# cd ../machine_learning/preprocess/
# python split.py /sa/middle_dir/coin_miner_cy/coin_miner_malicious.txt 0.5
# python split.py /sa/middle_dir/coin_miner_cy/coin_miner_normal.txt 0.5
# python split.py /sa/middle_dir/coin_miner_cy/html_normal_crawled.txt 0.5
# cat /sa/middle_dir/coin_miner_cy/coin_miner_malicious_random_0.5_group_a.txt > /sa/middle_dir/coin_miner_cy/coin_miner_train.txt
# cat /sa/middle_dir/coin_miner_cy/coin_miner_normal_random_0.5_group_a.txt >> /sa/middle_dir/coin_miner_cy/coin_miner_train.txt
# cat /sa/middle_dir/coin_miner_cy/html_normal_crawled_random_0.5_group_a.txt >> /sa/middle_dir/coin_miner_cy/coin_miner_train.txt
# cat /sa/middle_dir/coin_miner_cy/coin_miner_malicious_random_0.5_group_b.txt > /sa/middle_dir/coin_miner_cy/coin_miner_test.txt
# cat /sa/middle_dir/coin_miner_cy/coin_miner_normal_random_0.5_group_b.txt >> /sa/middle_dir/coin_miner_cy/coin_miner_test.txt
# cat /sa/middle_dir/coin_miner_cy/html_normal_crawled_random_0.5_group_b.txt >> /sa/middle_dir/coin_miner_cy/coin_miner_test.txt


cd /sa/github/pysie/machine_learning/training_process/
python predict.py /sa/middle_dir/coin_miner_cy/coin_miner_test.txt