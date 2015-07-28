CC = g++

all: main.o huffman.o
	$(CC) main.o huffman.o -o main

main.o: main.cpp
	$(CC) main.cpp -c -o main.o

huffman.o: huffman.cpp
	$(CC) huffman.cpp -c -o huffman.o

clean:
	rm -f *.o main.exe
