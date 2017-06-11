#! /bin/bash
./main -n $1 -m $2
pnmtopng out.ppm >out$1$2\.png
rm out.ppm
