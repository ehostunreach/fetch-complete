#!/bin/sh

mkdir -p m4

AUTORECONF=`which autoreconf`
if test -z $AUTORECONF; then
    echo "*** No autoreconf found, please intall it ***"
    exit 1
fi

autoreconf --force --install --verbose
