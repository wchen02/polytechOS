CC=g++
OUT=-o output

result: process.o scheduler.o test.o
	$(CC) process.o scheduler.o test.o $(OUT)

test.o:
	$(CC) -c -Wall test.cpp

process.o: 
	$(CC) -c -Wall process.h process.cpp

scheduler.o: 
	$(CC) -c -Wall scheduler.h scheduler.cpp

clean:
	rm *.o *.gch 
