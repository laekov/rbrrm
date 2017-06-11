#! /bin/bash
./main -n $1
pnmtopng out.ppm >out$1\.png
rm out.ppm
