#!/bin/bash

mkdir result

echo "CHECKING CORES"
./scripts/cores.sh
echo "DONE CORES"

echo "CHECKING NODES"
./scripts/nodes.sh
echo "DONE NODES"

echo "CHECKING RADIUS"
./scripts/radius.sh
echo "DONE RADIUS"

echo "CHECKING AWESOME"
./scripts/awesome.sh
echo "DONE AWESOME"