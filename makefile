cc = g++ -g -Isrc/include
default : mkdir bin/main
routers = obj/costflow.o obj/dinic.o obj/flow.o obj/router.o
bin/main : src/main.cpp obj/canvas.o $(routers)
	$(cc) src/main.cpp obj/canvas.o $(routers) -o bin/main
obj/costflow.o : src/include/costflow.h src/costflow.cpp
	$(cc) -c src/costflow.cpp -o obj/costflow.o
obj/dinic.o : src/include/dinic.h src/dinic.cpp
	$(cc) -c src/dinic.cpp -o obj/dinic.o
obj/flow.o : src/include/flow.h src/flow.cpp
	$(cc) -c src/flow.cpp -o obj/flow.o
obj/router.o : src/include/router.h src/router.cpp
	$(cc) -c src/router.cpp -o obj/router.o
obj/canvas.o : src/canvas.cpp src/include/canvas.h
	$(cc) -c src/canvas.cpp -o obj/canvas.o
mkdir :
	@if [ ! -d obj ]; then mkdir obj; fi
	@if [ ! -d bin ]; then mkdir bin; fi
clean : 
	rm -rf obj bin
