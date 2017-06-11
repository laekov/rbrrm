#! /bin/bash
./main --test-grid $1
pnmtopng gridout.ppm >gridout.png
