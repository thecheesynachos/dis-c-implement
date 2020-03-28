#!/usr/bin/env bash

SIZE=100
RADIUS=0.2
THREAD=20

rm -r ./result/*

for disC in disc_bulkinsert_run disc_parallel_run disc_singleinsert_run; do
	mkdir result/$disC
	for data in clustered uniform; do
		for dimension in 1 2 3 4 5; do
			for pts in 2000 4000 6000 8000 10000 12000 14000 16000 18000 20000; do
				mkdir -p ./result/$disC/data/$data/d$dimension/s$pts
				for fName in r0 r1 r2; do
					./$disC ./data/$data/d$dimension/s$pts/$fName $dimension $pts $SIZE $RADIUS $THREAD >> ./result/$disC/data/$data/d$dimension/s$pts/$fName
					echo "$disC $data/d$dimension/s$pts/$fName done"
				done
			done
		done
	done
done