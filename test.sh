#!/bin/bash

set -u

Green='\033[0;32m'
Yellow='\033[0;33m'
Blue='\033[0;34m'
Red='\033[0;31m'

function err {
    [[ $# -eq 1 ]] && printf "error: $1\n"
    exit 1
}

function usage {
    cat <<EOF
Usage: $0 <testcases-dir> [-g] [-t]
<testcases-dir> contains source files to be tested
    -g: complie with clang/gcc to get the right answers
    -t: test our compiler"
EOF
    err
}

function show_status {
    local src=$1
    progress="[$current_file_count/$file_num]"
    printf "$progress $src ... "
}

function report_result {
    local color=$1
    local msg=$2
    printf "$1$2\033[0m\n"
}

function run_test {
    local src=$1
    local input=$srcdir/${src%.*}.in
    local correct_out=$srcdir/${src%.*}.out
    local asm_out=$tmpdir/${src%.*}.s
    local bin_out=$tmpdir/${src%.*}
    local err_out=$tmpdir/${src%.*}.err
    local std_out=$tmpdir/${src%.*}.out

    show_status $src

    ${CC} $srcdir/$src -o $asm_out >/dev/null 2> $err_out
    [[ $? -ne 0 ]] && report_result $Red "compile error" && return

    gcc $asm_out -L. -lsysy_`uname -m` -o $bin_out 2>> $err_out
    [[ $? -ne 0 ]] && report_result $Red "assembler error" && return

    if [ -f $input ]
    then
        timeout 5 $bin_out < $input > $std_out 2>>$err_out
    else
        timeout 5 $bin_out > $std_out 2>>$err_out
    fi
    ec=$?
    echo $ec > $std_out
    [[ $ec -eq 124 ]] && report_result $Blue "timeout after 5 seconds" && return
    [[ $ec -eq 139 ]] && \
        report_result $Yellow "segfault" && return

    diff $std_out $correct_out >> $err_out
    [[ $? -ne 0 ]] && report_result $Yellow "wrong answer" && return
    
    report_result $Green passed

}

[[ $# -ne 2 ]] && usage

./build.sh || err "build failed"

srcdir=$1
tmpdir=sad
CC=gcc

mkdir -p $tmpdir

if [ $2 = "-g" ]
then 
    CC=gcc
elif [ $2 = "-t" ]
then
    CC=build/babel
fi

file_num=`ls $srcdir/*.sy | wc -l | tr -d '[:space:]'`
current_file_count=1

for file in `find $srcdir -name '*.sy' -exec basename {} \; | sort`
do
    run_test $file
    current_file_count=`expr $current_file_count + 1`
done

exit 0
