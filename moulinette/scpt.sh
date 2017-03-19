#!/bin/bash

BINARY=42sh
REF=`which tcsh`
TESTDIR=tests

RED="\e[31m"
GREEN="\e[32m"
NORMAL="\e[0m"

function	fatal()
{
    echo -e "$RED[ERROR]$NORMAL" $1
    exit 1
}

function	print_ko()
{
    echo -e "${RED}$1${NORMAL}"
}

function	print_ok()
{
    echo -e "${GREEN}$1${NORMAL}"
}

function	perform_test()
{
    CONTENT=$(cat $1)
    echo -ne "[TESTING] ${GREEN}"
    echo -n "$CONTENT" | grep --color=never "NAME=" | sed s/'NAME='//
    echo -ne "$NORMAL"
    TEST=$(echo "$CONTENT" | grep --color=never "CMD=" | sed s/'CMD='//)
    echo "$TEST" | ./$BINARY > "/tmp/${1}_test"
    echo "$TEST" | $REF > "/tmp/${1}_ref"
    ([ -n "$(diff -q "/tmp/${1}_test" "/tmp/${1}_ref")" ] && print_ko "KO" ) || (print_ok "OK" && rm "/tmp/${1}_test" "/tmp/${1}_ref")
}


[ ! -f $BINARY ] && fatal "Binary not found !"
[ $# -eq 1 ] && TESTDIR=$1
mkdir -p /tmp/$TESTDIR

for i in `ls $TESTDIR`
do
    perform_test "$TESTDIR/$i"
done
