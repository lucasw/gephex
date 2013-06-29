#!/bin/bash

for name in *.jpg; do
    i=${name%.jpg}
    jpegtopnm $i.jpg > $i.pnm;
    pnmtops -noturn -imagewidth 4  $i.pnm > $i.eps;
done
