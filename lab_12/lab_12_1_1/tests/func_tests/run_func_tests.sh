#!/bin/sh

for i in {01..10}; do
	echo "TEST $i START"
	touch results.txt
	< in_$i.txt ./app.exe > results.txt
	if cmp -s "out_$i.txt" "results.txt"; then
		echo "Test $i COMPLETED"
	else
		echo "Test $i FAILED"
	fi
	rm results.txt
	echo
done
