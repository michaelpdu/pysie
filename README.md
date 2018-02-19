# pysie
This project is to build HTML/JS feature extraction and model trainning

## Feature Extraction

In feature_extraction, you could use *pysie.py* to extract features and dump in libsvm data format.

```
>> python pysie.py --dump-feature target_path --label label --dest-file [dest_file_path]
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

