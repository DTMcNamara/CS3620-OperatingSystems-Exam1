#!/bin/bash

files=$(find "$1" -type f -name "*cs3620*")

for f in $files
do
	tar -zxvf $f
done
