#!/bin/bash

for i in 50 100 150 200 250 300 350 400
do
  mkdir -p result/node_result/n$i
  for k in 0 1 2
  do
    # run on 2d, 20k points
    ./disc_parallel_run data/uniform/d2/s20000/r$k 2 20000 $i 0.2 20 >> result/node_result/n$i/uni_$k
    ./disc_parallel_run data/uniform/d2/s20000/r$k 2 20000 $i 0.2 20 >> result/node_result/n$i/cls_$k
    ./disc_bulkinsert_run data/uniform/d2/s20000/r$k 2 20000 $i 0.2 20 >> result/node_result/n$i/uni_$k
    ./disc_bulkinsert_run data/uniform/d2/s20000/r$k 2 20000 $i 0.2 20 >> result/node_result/n$i/cls_$k
    ./disc_singleinsert_run data/uniform/d2/s20000/r$k 2 20000 $i 0.2 20 >> result/node_result/n$i/uni_$k
    ./disc_singleinsert_run data/uniform/d2/s20000/r$k 2 20000 $i 0.2 20 >> result/node_result/n$i/cls_$k
  done
  echo $i finished
done