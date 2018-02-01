#python pysie.py --dump-feature /sa/sample/TSS_Generic_sample/malicious/ --label 1 --dest-file /sa/middle_dir/tss_test/tss_malicious.txt
#python pysie.py --dump-feature /sa/sample/TSS_Generic_sample/normal/ --label 0 --dest-file /sa/middle_dir/tss_test/tss_normal.txt
#python pysie.py --dump-feature /sa/sample/html/normal/HTML/crawled_web_pages --label 0 --dest-file /sa/middle_dir/tss_test/html_normal_crawled.txt

cd ../machine_learning/preprocess/
python split.py /sa/middle_dir/tss_test/tss_malicious.txt 0.5
python split.py /sa/middle_dir/tss_test/tss_normal.txt 0.5
python split.py /sa/middle_dir/tss_test/html_normal_crawled.txt 0.5
cat /sa/middle_dir/tss_test/tss_malicious_random_0.5_group_a.txt > /sa/middle_dir/tss_test/tss_train.txt
cat /sa/middle_dir/tss_test/tss_normal_random_0.5_group_a.txt >> /sa/middle_dir/tss_test/tss_train.txt
cat /sa/middle_dir/tss_test/html_normal_crawled_random_0.5_group_a.txt >> /sa/middle_dir/tss_test/tss_train.txt
cat /sa/middle_dir/tss_test/tss_malicious_random_0.5_group_b.txt > /sa/middle_dir/tss_test/tss_test.txt
cat /sa/middle_dir/tss_test/tss_normal_random_0.5_group_b.txt >> /sa/middle_dir/tss_test/tss_test.txt
cat /sa/middle_dir/tss_test/html_normal_crawled_random_0.5_group_b.txt >> /sa/middle_dir/tss_test/tss_test.txt

cd ../../pysie/
python pysie.py --dump-feature /sa/sample/html/unique/malicious/ --label 1 --dest-file /sa/middle_dir/tss_test/malicious_unique.txt
python pysie.py --dump-feature /sa/sample/html/unique/normal/ --label 0 --dest-file /sa/middle_dir/tss_test/normal_unique.txt

cd ../machine_learning/training_process/
python train.py /sa/middle_dir/tss_test/tss_train.txt
python predict.py /sa/middle_dir/tss_test/tss_test.txt
python predict.py /sa/middle_dir/tss_test/malicious_unique.txt
python predict.py /sa/middle_dir/tss_test/normal_unique.txt



