#!/bin/bash

echo "hello world" | tee orig | ./fsplit one 6 two
cat one two > comb
if [ -n "$(diff orig comb)" ]; then
	echo "FAIL test 1"
else
	echo "PASS test 1"
fi

rm orig comb one two

dd if=/dev/urandom bs=1k count=1 of=orig &> /dev/null
./fsplit one 512 two < orig
cat one two > comb
md5sum < orig > orig.md5
md5sum < comb > comb.md5
if [ -n "$(diff orig.md5 comb.md5)" ]; then
	cat orig.md5 comb.md5
	echo "FAIL test 2"
else
	echo "PASS test 2"
fi

rm orig* comb* one two
