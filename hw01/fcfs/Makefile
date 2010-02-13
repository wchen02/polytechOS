CC=g++ #compiler
OUT= -o scheduler

scheduler: process.o scheduler.o
	$(CC) $(OUT) process.o scheduler.o

scheduler.o: 
	$(CC) -c scheduler.cpp 

process.o:
	$(CC) -c process.h process.cpp 

clean:
	rm *.o 
	
