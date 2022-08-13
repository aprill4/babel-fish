#!/bin/bash
list=$(ls ./functional/*.sy)
for file in $list:
do
	./build/babel file -o t.s
	sleep 1
	clang t.s -l
