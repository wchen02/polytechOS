#include <iostream>
#include <queue>
#include <cstdlib>
#include "process.h"
#include "scheduler.h"
#include "fcfs.h"

using namespace std;

FCFS::FCFS(string resourceFile) : Scheduler(resourceFile){
	cout << "meows";
}

Process FCFS::top() const {
	return ready.top();
}

void FCFS::pop(){
	ready.pop( );
}

void FCFS::push(Process newProcess){
	ready.push(newProcess); // need to decide the algorithm choice before this
}

int FCFS::size() const {
	return ready.size();
}

bool FCFS::empty() const {
	return ready.empty();
}