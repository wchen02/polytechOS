#include <iostream>
#include <queue>
#include <cstdlib>
#include "process.h"
#include "scheduler.h"
#include "fcfs.h"

using namespace std;

FCFS::FCFS(const std::string& resourceFile) : Scheduler(resourceFile){
	cout << "meows";
	nothingToRun = false;
	while(!nothingToRun){
		readinQueueTask();
		waitingQueueTask();
		readyQueueTask();
		now++;
	}
}

void FCFS::waitingQueueTask(){
	Process tmp;

	for(size_t i=0; i < waiting.size(); ++i){
		tmp = waiting[i];
		if( tmp.ioDelay )
			waiting[i].ioDelay--;
		else{
			tmp.ioDelay = this->ioDelay;
			ready.push(tmp);
			waiting.erase(waiting.begin()+i);
			if(DEBUG) cout << "Moving process from waiting to ready";
		}
	}
}

void FCFS::readinQueueTask(){
	Process tmp = readin.front();
	if(tmp.getarrivalTime() == now){
		tmp.ioDelay = this->ioDelay;
		ready.push(tmp);
		readin.pop();
		if(DEBUG) cout << "Moving process from readin to ready\n";
	}
}

void FCFS::readyQueueTask(){
	if(running.cpuBurst = -9999 && ready.size()){
		running = ready.top();
		ready.pop();
		if(DEBUG) cout << "Running process pid" << running.getPId() << endl ;
	} else {
		if(!readin.size() && !waiting.size()){
			nothingToRun = true;
			if(DEBUG) cout << "No more processes to run\n";
		}
		return;
	} // theres no more processes in the queue, quit.
	if(!running.cpuMax){
		running.cpuBurst = -9999;
		if(DEBUG) cout << "Finish with process pid" << running.getPId() << endl;
		return;
	}
	if(running.cpuBurst){
		running.cpuBurst--;
		running.cpuMax--;
		if(DEBUG) cout << "Still running process pid" << running.getPId() << endl;
	}else{
		waiting.push_back(running);
		running.cpuBurst = -9999;
		if(DEBUG) cout << "Moving process from ready to waiting\n";
	}
}
