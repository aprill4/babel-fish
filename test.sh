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
CASE=

function err {
    [[ $# -eq 1 ]] && printf "${Red}error:${Normal} $1\n"
    exit 1
}

function usage {
    cat <<EOF
Usage: $0 [ -d SOURCES_DIR | -s SOURCE ] [-g/-t]  [-q]
    -d: specify the sources files directory (default: functional)
    -s: test single case
    -g: complie with clang/gcc to get the right answers
    -t: test our compiler (default)
    -q: use QEMU (default: disabled)
EOF
    err
}

function parse_opts {
    while getopts "d:gtcs:" options; do
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
            s) 
                CASE=`basename ${OPTARG}`
                SRCDIR=`dirname ${OPTARG}`
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
    printf "$src ... "
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

    ${CC} $SRCDIR/$src -o $asm_out >/dev/null 2> $err_out
    [[ $? -ne 0 ]] && report_result $Red "compile error" && return 1

    ${ASSEMBLER} $asm_out libsysy_${ARCH}.a -o $bin_out 2>> $err_out
    [[ $? -ne 0 ]] && report_result $Red "assembler error" && return 1

    if [ -f $input ]
    then
        timeout 5 $QEMU $bin_out < $input > $std_out 2>>$err_out
    else
        timeout 5 $QEMU $bin_out > $std_out 2>>$err_out
    fi
    ec=$?
    echo $ec >> $std_out
    [[ $ec -eq 124 ]] && report_result $Blue "timeout after 5 seconds" && return 1
    [[ $ec -eq 139 ]] && \
        report_result $Yellow "segfault" && return 1

    diff $std_out $correct_out >> $err_out
    [[ $? -ne 0 ]] && report_result $Yellow "wrong answer" && return 1
    
    report_result $Green passed && return 0
}

function run_all_tests {
    file_num=`ls $SRCDIR/*.sy | wc -l | tr -d '[:space:]'`
    current_file_count=1
    current_failed=0

    for file in `find $SRCDIR -name '*.sy' -exec basename {} \; | sort`
    do
        progress="[$current_file_count/$file_num]"
        printf "$progress "
        show_status $file
        run_test $file
        failed=$?
        current_failed=`expr $current_failed + $failed`
        current_file_count=`expr $current_file_count + 1`
    done

    passed=`expr $current_file_count - 1 - $current_failed`

    printf "statistics\n"
    printf "    ${Green}$passed passed\n"
    printf "    ${Red}$current_failed failed${Normal}\n"
    return "$current_failed"
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
    #./build.sh || err "build failed"

    if [ "$CASE" = "" ]
    then
        run_all_tests
    else
        show_status "$CASE"
        run_test "$CASE"
    fi
}

# TODO: returns non-zero if any test failed
main $@
