#!/bin/bash

for i in 40 80 120 160 200
do
  mkdir -p result/node_result_10k/n$i
  mkdir -p result/node_result_20k/n$i
  for k in 0 1 2
  do
    # run on 2d, 10k points
    ./disc_parallel_run data/uniform/d2/s10000/r$k 2 10000 $i 0.2 20 >> result/node_result_10k/n$i/uni_$k
    ./disc_parallel_run data/uniform/d2/s10000/r$k 2 10000 $i 0.2 20 >> result/node_result_10k/n$i/cls_$k
    ./disc_bulkinsert_run data/uniform/d2/s10000/r$k 2 10000 $i 0.2 20 >> result/node_result_10k/n$i/uni_$k
    ./disc_bulkinsert_run data/uniform/d2/s10000/r$k 2 10000 $i 0.2 20 >> result/node_result_10k/n$i/cls_$k
    ./disc_singleinsert_run data/uniform/d2/s10000/r$k 2 10000 $i 0.2 20 >> result/node_result_10k/n$i/uni_$k
    ./disc_singleinsert_run data/uniform/d2/s10000/r$k 2 10000 $i 0.2 20 >> result/node_result_10k/n$i/cls_$k
    # run on 2d, 20k points
    ./disc_parallel_run data/uniform/d2/s20000/r$k 2 20000 $i 0.2 20 >> result/node_result_20k/n$i/uni_$k
    ./disc_parallel_run data/uniform/d2/s20000/r$k 2 20000 $i 0.2 20 >> result/node_result_20k/n$i/cls_$k
    ./disc_bulkinsert_run data/uniform/d2/s20000/r$k 2 20000 $i 0.2 20 >> result/node_result_20k/n$i/uni_$k
    ./disc_bulkinsert_run data/uniform/d2/s20000/r$k 2 20000 $i 0.2 20 >> result/node_result_20k/n$i/cls_$k
    ./disc_singleinsert_run data/uniform/d2/s20000/r$k 2 20000 $i 0.2 20 >> result/node_result_20k/n$i/uni_$k
    ./disc_singleinsert_run data/uniform/d2/s20000/r$k 2 20000 $i 0.2 20 >> result/node_result_20k/n$i/cls_$k
    echo $i $k finished
  done
done