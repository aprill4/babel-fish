#!/bin/bash

set -u

Green='\033[0;32m'
Yellow='\033[0;33m'
Blue='\033[0;34m'
Red='\033[0;31m'
Normal='\033[0m'

SRCDIR=functional
TMPDIR=sad
CC=build/babel
ASSEMBLER=gcc
QEMU=
ARCH=`uname -m`

function err {
    [[ $# -eq 1 ]] && printf "${Red}error:${Normal} $1\n"
    exit 1
}

function usage {
    cat <<EOF
Usage: $0 [ -d SOURCES ] [-g/-t]  [-q]
    -d: specify the sources files directory (default: functional)
    -g: complie with clang/gcc to get the right answers
    -t: test our compiler (default)
    -q: use QEMU (default: disabled)
EOF
    err
}

function parse_opts {
    while getopts "d:gtc" options; do
        case ${options} in
            d)
                SRCDIR=${OPTARG}
                ;;
            g)
                CC=gcc
                ;;
            t)
                CC=build/babel
                ;;
            c) 
                ASSEMBLER="zig cc -target arm-linux-musleabi"
                ARCH="armv7l"
                QEMU="qemu-arm-static"
                ;;
            :) 
                err "-${OPTARG} requries an argument."
                usage
                ;;
            *)
                usage
                ;;
        esac
    done
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
    local input=$SRCDIR/${src%.*}.in
    local correct_out=$SRCDIR/${src%.*}.out
    local asm_out=$TMPDIR/${src%.*}.s
    local bin_out=$TMPDIR/${src%.*}
    local err_out=$TMPDIR/${src%.*}.err
    local std_out=$TMPDIR/${src%.*}.out

    show_status $src

    ${CC} $SRCDIR/$src -o $asm_out >/dev/null 2> $err_out
    [[ $? -ne 0 ]] && report_result $Red "compile error" && return

    ${ASSEMBLER} $asm_out libsysy_${ARCH}.a -o $bin_out 2>> $err_out
    [[ $? -ne 0 ]] && report_result $Red "assembler error" && return

    if [ -f $input ]
    then
        timeout 5 $QEMU $bin_out < $input > $std_out 2>>$err_out
    else
        timeout 5 $QEMU $bin_out > $std_out 2>>$err_out
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

function run_all_tests {
    file_num=`ls $SRCDIR/*.sy | wc -l | tr -d '[:space:]'`
    current_file_count=1

    for file in `find $SRCDIR -name '*.sy' -exec basename {} \; | sort`
    do
        run_test $file
        current_file_count=`expr $current_file_count + 1`
    done
}

function main {
    parse_opts $@

    cat <<EOF
environments
    SRCDIR=${SRCDIR}
    CC=${CC}
    ASSEMBLER=${ASSEMBLER}
    ARCH=${ARCH}
    QEMU=${QEMU}

EOF

    mkdir -p $TMPDIR
    ./build.sh || err "build failed"

    run_all_tests
}

# TODO: returns non-zero if any test failed
main $@

exit 0