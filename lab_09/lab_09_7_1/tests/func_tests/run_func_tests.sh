#!/bin/bash

clear
for i in {01..12}; do
	echo "TEST $i START"
	< in_$i.txt ./func_testing.exe > out_$i.txt
	if cmp -s "expected_out_$i.txt" "out_$i.txt"; then
		echo "Test $i COMPLETED"
		read -p "Press any key to continue"
	else
		echo "Test $i FAILED"
		read -p "Press any key to continue"
	fi
	echo
done
