#!/bin/bash

for i in $(seq 0.1 0.1 1.0)
do
  mkdir -p rad_result_2d_10k/r$i
  mkdir -p rad_result_2d_20k/r$i
  mkdir -p rad_result_4d_10k/r$i
  for k in 0 1 2
  do
    # run on 2d, 10k points
    ./disc_parallel_run data/uniform/d2/s10000/r$k 2 10000 100 $i 20 >> result/rad_result_2d_10k/r$i/uni_$k
    ./disc_parallel_run data/clustered/d2/s10000/r$k 2 10000 100 $i 20 >> result/rad_result_2d_10k/r$i/cls_$k
    # run on 2d, 20k points
    ./disc_parallel_run data/uniform/d2/s20000/r$k 2 20000 100 $i 20 >> result/rad_result_2d_20k/r$i/uni_$k
    ./disc_parallel_run data/clustered/d2/s20000/r$k 2 20000 100 $i 20 >> result/rad_result_2d_20k/r$i/cls_$k
    # run on 4d, 10k points
    ./disc_parallel_run data/uniform/d4/s10000/r$k 4 10000 100 $i 20 >> result/rad_result_4d_10k/r$i/uni_$k
    ./disc_parallel_run data/clustered/d4/s10000/r$k 4 10000 100 $i 20 >> result/rad_result_4d_10k/r$i/cls_$k
    echo $i $k finished
  done
done