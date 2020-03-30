#!/bin/bash

for i in 20 40 60 80 100 120 140 160
do
  mkdir -p result/node_result_4k/n$i
  mkdir -p result/node_result_8k/n$i
  for k in 0 1 2
  do
    # run on 2d, 4k points
    ./disc_parallel_run data/uniform/d2/s4000/r$k 2 4000 $i 0.05 20 >> result/node_result_4k/n$i/uni_$k
    ./disc_parallel_run data/uniform/d2/s4000/r$k 2 4000 $i 0.05 20 >> result/node_result_4k/n$i/cls_$k
    ./disc_bulkinsert_run data/uniform/d2/s4000/r$k 2 4000 $i 0.05 20 >> result/node_result_4k/n$i/uni_$k
    ./disc_bulkinsert_run data/uniform/d2/s4000/r$k 2 4000 $i 0.05 20 >> result/node_result_4k/n$i/cls_$k
    ./disc_singleinsert_run data/uniform/d2/s4000/r$k 2 4000 $i 0.05 20 >> result/node_result_4k/n$i/uni_$k
    ./disc_singleinsert_run data/uniform/d2/s4000/r$k 2 4000 $i 0.05 20 >> result/node_result_4k/n$i/cls_$k
    # run on 2d, 8k points
    ./disc_parallel_run data/uniform/d2/s8000/r$k 2 8000 $i 0.05 20 >> result/node_result_8k/n$i/uni_$k
    ./disc_parallel_run data/uniform/d2/s8000/r$k 2 8000 $i 0.05 20 >> result/node_result_8k/n$i/cls_$k
    ./disc_bulkinsert_run data/uniform/d2/s8000/r$k 2 8000 $i 0.05 20 >> result/node_result_8k/n$i/uni_$k
    ./disc_bulkinsert_run data/uniform/d2/s8000/r$k 2 8000 $i 0.05 20 >> result/node_result_8k/n$i/cls_$k
    ./disc_singleinsert_run data/uniform/d2/s8000/r$k 2 8000 $i 0.05 20 >> result/node_result_8k/n$i/uni_$k
    ./disc_singleinsert_run data/uniform/d2/s8000/r$k 2 8000 $i 0.05 20 >> result/node_result_8k/n$i/cls_$k
    echo $i $k finished
  done
done