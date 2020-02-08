#!/bin/sh

clear
for i in {01..15}; do
	echo "TEST $i START"
	touch results.txt
	./func_testing.exe < in_$i.txt
	if cmp -s "out_$i.txt" "results.txt"; then
		echo "Test $i COMPLETED"
		read -p "Press any key to continue"
	else
		echo "Test $i FAILED"
		read -p "Press any key to continue"
	fi
	rm results.txt
	echo
done
