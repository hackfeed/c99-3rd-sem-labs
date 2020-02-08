#!/bin/bash

for i in {1..12}; do
	touch in_$i.txt
	touch out_$i.txt
	touch expected_out_$i.txt
done
