#!/bin/sh

for i in `ls ../interfaces/*.if`
do
    python ../../nic.py nam . $i
done
