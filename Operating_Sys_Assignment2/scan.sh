#!/bin/sh
suffix=$1
num=$2
if [ "$#" -ne 2 ] ; then
echo "Invalid parameters" >&2
exit 1
else
find . -type f -name '*'$suffix -printf '%s\t%p\n' | sort -n -r | head -$num |awk '{ x += $1 ; print $2 "\t"$1 } END { print "total bytes: " x }'
fi
