machine: main.o
	g++ -o machine main.o
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm *.o machine