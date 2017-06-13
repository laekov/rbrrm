cc = g++ -g -Isrc/include
headers = $(wildcard src/include/*.hh)
objects = $(headers:src/include/%.hh=obj/%.o)
sources = $(headers:src/include/%.hh=src/%.cc)
testsrc = $(wildcard test/*.cc)
tests = $(testsrc:test/%.cc=bin/%)

default : mkdir $(objects) bin/main

bin/% : src/%.cc $(objects)
	$(cc) $< $(objects) -o $@

obj/%.o : src/%.cc src/include/%.hh  $(headers)
	$(cc) -c $< -o $@

mkdir :
	@if [ ! -d obj ]; then mkdir obj; fi
	@if [ ! -d bin ]; then mkdir bin; fi
clean : 
	rm -rf obj bin
