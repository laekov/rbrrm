cc = g++ -g -Isrc/include
headers = $(wildcard src/include/*.hh)
objects = $(headers:src/include/%.hh=obj/%.o)
sources = $(headers:src/include/%.hh=src/%.cc)

default : mkdir $(objects) bin/main

bin/main : src/main.cc $(objects)
	$(cc) src/main.cc $(objects) -o $@

obj/%.o : src/%.cc src/include/%.hh 
	$(cc) -c $< -o $@

mkdir :
	@if [ ! -d obj ]; then mkdir obj; fi
	@if [ ! -d bin ]; then mkdir bin; fi
clean : 
	rm -rf obj bin
