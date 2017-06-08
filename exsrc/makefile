cc = g++ -g -I../src/include
default : main slow
main : main.cc canvas.o
	$(cc) main.cc canvas.o -o main
slow : slow.cc canvas.o
	$(cc) slow.cc canvas.o -o slow
canvas.o : ../src/canvas.cpp
	$(cc) -c ../src/canvas.cpp -o canvas.o 
