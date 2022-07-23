#!/usr/bin/env bash

for i in $(ls oldtest -1)
do
    echo $i
    cat oldtest/$i > oldtest_out/$i.out
    echo -e >> oldtest_out/$i.out
    ./check.out < oldtest/$i >> oldtest_out/$i.out
done