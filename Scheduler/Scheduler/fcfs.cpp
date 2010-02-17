#include <iostream>
#include <queue>
#include <cstdlib>
#include "process.h"
#include "scheduler.h"
#include "fcfs.h"

using namespace std;

FCFS::FCFS(const std::string& resourceFile) : Scheduler(resourceFile){
	nothingToRun = false;
	while(!nothingToRun){
		if(DEBUG){
			cout << "===============\nTime " << now << endl << 
				"Running: ";
			if(running.getPId()== -1)
				cout << "none";	
			else
				cout << running.getPId();
			cout << "\nArrival:";
			if(arrival.size())
				for(int i=0; i < arrival.size(); i++)
					cout << " " << arrival[i].getPId();
			else
				cout << " none";
			cout << "\nNext Ready: ";
			if(ready.size())
				cout << ready.top().getPId();
			else cout << "none";
			cout << "\nWaiting: ";
			if(waiting.size())
				for(int i=0; i < waiting.size(); i++)
					cout << " " << waiting[i].getPId();
			else
				cout << " none";
			cout << endl;
		}
		if(DEBUG) cout << "===============\n";
		readinQueueTask();
		waitingQueueTask();
		readyQueueTask();
		now++;

		if(!arrival.size() && !waiting.size() && !ready.size() && running.getPId() == -1){
			nothingToRun = true;
			if(DEBUG) cout << "No more processes to run\n";
		} // theres no more processes in the queue, quit.
	}
}

void FCFS::waitingQueueTask(){
	for(size_t i=0; i < waiting.size(); ++i){
		if( waiting[i].ioDelay ){
			waiting[i].ioDelay--;
			if(!waiting[i].ioDelay){
				resetBurstNdelay(waiting[i]);
				ready.push(waiting[i]);
				if(DEBUG) cout << "Moving process pid:" << waiting[i].getPId() << " from waiting to ready\n";
				waiting.erase(waiting.begin()+i);
			}
		}
	}
}

void FCFS::readinQueueTask(){
	if(arrival.size()){
		if(arrival.front().getarrivalTime() == now){
			resetBurstNdelay(arrival.front());
			ready.push(arrival.front());
			if(DEBUG) cout << "Moving process pid:" << arrival.front().getPId() << " from arrival to ready\n";
			arrival.erase(arrival.begin());
		}
	}
}

void FCFS::readyQueueTask(){
	if(running.cpuBurst == -9999 && ready.size()){
		running = ready.top();
		ready.pop();
		cout << "Moving process pid:" << running.getPId() << " from ready to running. Remaining Time: " << running.cpuMax << ".\n";
		return;
	}
	if(running.cpuBurst > 0 && running.cpuBurst != -9999){
		running.cpuBurst--;
		running.cpuMax--;
		if(DEBUG) cout << "Process pid:" << running.getPId() << " ending burst(" << running.cpuBurst << "). Remaining Time: " << running.cpuMax << ".\n";

		if(!running.cpuMax){
			if(DEBUG) cout << "Finish with process pid:" << running.getPId() << endl;
			running = Process();
		}else if(!running.cpuBurst){
			waiting.push_back(running);
			if(DEBUG) cout << "Moving process pid:" << running.getPId() << " from ready to waiting\n";
			running = Process();
		}
	}
}

void FCFS::resetBurstNdelay(Process& p){
	p.ioDelay = this->ioDelay;
	p.cpuBurst = 2; // needs to be computed by the random file
}
