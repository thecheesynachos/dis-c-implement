#!/bin/bash

for i in 2 4 6 8 10 12 14 16 18 20
do
  mkdir -p result/core_result_2d_4k/c$i
  mkdir -p result/core_result_2d_8k/c$i
#  mkdir -p result/core_result_4d_4k/c$i
  for k in 0 1 2
  do
    # run on 2d, 4k points
    ./disc_parallel_run data/uniform/d2/s4000/r$k 2 4000 50 0.05 $i >> result/core_result_2d_4k/c$i/unif_$k
    ./disc_parallel_run data/clustered/d2/s4000/r$k 2 4000 50 0.05 $i >> result/core_result_2d_4k/c$i/clus_$k
    # run on 2d, 8k points
    ./disc_parallel_run data/uniform/d2/s8000/r$k 2 8000 50 0.05 $i >> result/core_result_2d_8k/c$i/unif_$k
    ./disc_parallel_run data/clustered/d2/s8000/r$k 2 8000 50 0.05 $i >> result/core_result_2d_8k/c$i/clus_$k
    echo $i $k finished
  done
done