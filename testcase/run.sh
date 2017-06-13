#! /bin/bash
./main -n $1 --out-ppm out.ppm
pnmtopng out.ppm >$1\.png
rm out.ppm
