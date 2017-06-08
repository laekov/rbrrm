#! /bin/bash
./main -n $1
pnmtopng out.ppm >out.png
