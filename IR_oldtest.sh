#!/usr/bin/env bash

if [ -d "./oldtest_out" ]; then
    echo "directory \"./oldtest_out\" exists"
else 
    mkdir oldtest_out
fi

for i in $(ls oldtest -1)
do
    echo $i
    # cat oldtest/$i > oldtest_out/$i.out
    # echo -e >> oldtest_out/$i.out
    ./check.out < oldtest/$i > oldtest_out/$i.out
done