#!/usr/bin/env bash

SIZE=100
RADIUS=0.05
THREAD=20

for pts in 2000 4000 6000 8000 10000 12000 14000 16000 18000 20000; do
  for disC in disc_bulkinsert_run disc_parallel_run disc_singleinsert_run; do
    for data in clustered uniform; do
      for dimension in 1 2 3 4; do
          mkdir -p ./result/all/$disC/data/$data/d$dimension/s$pts
          for fName in r0 r1 r2; do
					./$disC ./data/$data/d$dimension/s$pts/$fName $dimension $pts $SIZE $RADIUS $THREAD >> ./result/all/$disC/data/$data/d$dimension/s$pts/$fName
					echo "$disC $data/d$dimension/s$pts/$fName done"
				done
			done
		done
	done
done