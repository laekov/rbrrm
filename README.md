Rule-Based Regular Routing Method
===
Big homework for OOP course by Dr.Yao.

## Installation
Run the following command

	make 

And it will automatically be built. An executable binary can be found at `bin/`.

## Usgae
	./main -n <n> [-m <m>] [--detail] [--out-coor <coor.out>] [--out-detail <detail.pnm>] [--out-brief <brief.pnm>]

Without `--detail` option, only the width between interal nodes will be calculated.

With `--out-coor` option, coordinates of lines will be output in text format to a specificed file.

With `--out-detail` option, detailed routing method will be outputed in `pnm` format, which could be transformed into other formats using `netpbm` or other software.

With `--out-brief` option, a brief routing method picture will be generated as above. For the detail picture will be very large in scale, which cannot be stored as picture file, this option is desinged to make demostrative pictures in large data scale. 
