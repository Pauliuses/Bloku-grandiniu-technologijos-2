prog: func.o
	g++ -o prog main.cpp func.o
funkc:
	g++ -c func.cpp
clean:
	rm *.o prog.exe