#!/bin/bash

for i in {2..2..20}
do
  mkdir -p result/core_result_2d/c$i
  mkdir -p result/core_result_5d/c$i
  for k in 0 1 2
  do
    # run on 2d, 10k points
    ./disc_parallel_run data/uniform/d2/s10000/r$k 2 10000 100 0.2 $i >> result/core_result_2d/c$i/unif_$k
    ./disc_parallel_run data/clustered/d2/s10000/r$k 2 10000 100 0.2 $i >> result/core_result_2d/c$i/clus_$k
    # run on 5d, 20k points
    ./disc_parallel_run data/uniform/d5/s20000/r$k 5 20000 100 0.2 $i >> result/core_result_5d/c$i/unif_$k
    ./disc_parallel_run data/clustered/d5/s20000/r$k 5 20000 100 0.2 $i >> result/core_result_5d/c$i/clus_$k
  done
  echo $i finished
done