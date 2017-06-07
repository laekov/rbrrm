cc = g++ -g -I../src/include
default : main slow
main : main.cc
	$(cc) main.cc -o main
slow : slow.cc canvas.o
	$(cc) slow.cc canvas.o -o slow
canvas.o : ../src/canvas.cpp
	$(cc) -c ../src/canvas.cpp -o canvas.o 
