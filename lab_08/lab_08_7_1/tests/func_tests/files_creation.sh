#!/bin/bash

for i in {1..8}; do
	touch in_$i.txt
	touch out_$i.txt
	touch expected_out_$i.txt
done
