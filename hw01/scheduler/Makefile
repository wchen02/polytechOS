CC=g++
OUT= -o silly
result: process.o scheduler.o test.o
	$(CC) process.o scheduler.o test.o $(OUT)


test:
	$(CC) -c test.cpp

process.o:
	$(CC) -c process.h process.cpp

scheduler.o:
	$(CC) -c scheduler.h scheduler.cpp
