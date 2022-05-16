#!/bin/bash
# set -v
for i in $(ls test_2021 -1)
do
    # echo $i
    cat test_2021/$i > test_2021_out/$i.out
    echo -e >> test_2021_out/$i.out
    ./test test_2021/$i >> test_2021_out/$i.out
done