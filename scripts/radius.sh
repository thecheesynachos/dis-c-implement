#!/bin/bash

for i in $(seq 0.1 0.1 1.0)
do
  mkdir -p rad_result_2d/r$i
  mkdir -p rad_result_5d/r$i
  for k in 0 1 2
  do
    # run on 2d, 10k points
    ./disc_parallel_run data/uniform/d2/s10000/r$k 2 10000 100 $i 20 >> result/rad_result_2d/r$i/uni_$k
    ./disc_parallel_run data/clustered/d2/s10000/r$k 2 10000 100 $i 20 >> result/rad_result_2d/r$i/cls_$k
    # run on 5d, 20k points
    ./disc_parallel_run data/uniform/d5/s20000/r$k 5 20000 100 $i 20 >> result/ad_result_5d/r$i/uni_$k
    ./disc_parallel_run data/clustered/d5/s20000/r$k 5 20000 100 $i 20 >> result/rad_result_5d/r$i/cls_$k
  done
  echo $i finished
done