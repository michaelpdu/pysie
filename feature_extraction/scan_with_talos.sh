
middle_dir=/data/home/chaoying/middle_dir/tss
cd /data/home/chaoying/pysie/feature_extraction/sie_build/Linux/x64

./Talos --sieloglevel=off --talosloglevel=off --thread-count=16 --sample-path=/data/samples/html/validation_set/nor_set/normal_unique > $middle_dir/val_nor_normal_unique.txt
./Talos --sieloglevel=off --talosloglevel=off --thread-count=16 --sample-path=/data/samples/html/validation_set/nor_set/alexa_top_samples > $middle_dir/val_nor_alexa_top_samples.txt
./Talos --sieloglevel=off --talosloglevel=off --thread-count=16 --sample-path=/data/samples/html/validation_set/nor_set/grid > $middle_dir/val_nor_grid.txt
./Talos --sieloglevel=off --talosloglevel=off --thread-count=16 --sample-path=/data/home/chaoying/samples/FakeWarning/group_b > $middle_dir/val_mal_fakewarning.txt
./Talos --sieloglevel=off --talosloglevel=off --thread-count=16 --sample-path=/data/home/chaoying/samples/tss_nor > $middle_dir/val_nor_tss_nor.txt
./Talos --sieloglevel=off --talosloglevel=off --thread-count=16 --sample-path=/data/home/chaoying/samples/fp > $middle_dir/val_nor_fp.txt

