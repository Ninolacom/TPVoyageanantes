CC=g++
FLAGS= -std=C++0x -Wall

all : fourmis

fourmis : main.o
	$(CC) main.o -o fourmis.exe $(FLAGS)

main.o : main.cpp
	$(CC) main.cpp -o main.o $(FLAGS)