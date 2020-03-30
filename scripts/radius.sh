#!/bin/bash

for i in 0.02 0.04 0.06 0.08 0.1 0.12 0.14 0.16 0.18 0.2
do
  mkdir -p result/rad_result_2d_4k/r$i
  mkdir -p result/rad_result_2d_8k/r$i
#  mkdir -p result/rad_result_4d_10k/r$i
  for k in 0 1 2
  do
    # run on 2d, 4k points
    ./disc_parallel_run data/uniform/d2/s4000/r$k 2 4000 50 $i 20 >> result/rad_result_2d_4k/r$i/uni_$k
    ./disc_parallel_run data/clustered/d2/s4000/r$k 2 4000 50 $i 20 >> result/rad_result_2d_4k/r$i/cls_$k
    # run on 2d, 8k points
    ./disc_parallel_run data/uniform/d2/s8000/r$k 2 8000 50 $i 20 >> result/rad_result_2d_8k/r$i/uni_$k
    ./disc_parallel_run data/clustered/d2/s8000/r$k 2 8000 50 $i 20 >> result/rad_result_2d_8k/r$i/cls_$k
    echo $i $k finished
  done
done