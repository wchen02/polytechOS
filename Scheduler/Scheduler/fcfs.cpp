#include <iostream>
#include <queue>
#include <cstdlib>
#include "process.hpp"
#include "scheduler.hpp"
#include "fcfs.hpp"

using namespace std;

FCFS::FCFS(const std::string& resourceFile) : Scheduler(resourceFile), running(NULL){}

void FCFS::run(){
	cout << "===============\n"
		<< "      FCFS     \n"
		<< "===============\n";

	while(true){
		if(DEBUG) printSchedulerInfo(); 

		arrivalQueueTask();
		waitingQueueTask();
		readyQueueTask();
		now++;

		if(!arrivalQueue.size() && !waiting.size() && !ready.size() && !running)
			break; // theres no more processes in the queue, quit.
	}
}

void FCFS::printSchedulerInfo() const{
	cout << "===============\nTime " << now << endl << 
		"Running: ";
	if(!running) cout << "none";	
	else cout << running->getPid();
	
	cout << "\nArrival:";
	if(arrivalQueue.size())
		for(size_t i=0; i < arrivalQueue.size(); i++)
			cout << " " << arrivalQueue[i]->getPid();
	else cout << " none";
	
	cout << "\nReady: ";
	if(ready.size())
		for(size_t i=0; i < ready.size(); i++)
			cout << " " << ready[i]->getPid();
	else cout << "none";
	
	cout << "\nWaiting: ";
	if(waiting.size())
		for(int i=0; i < waiting.size(); i++)
			cout << " " << waiting[i]->getPid();
	else cout << " none";
	cout << "\n===============\n";
}

void FCFS::waitingQueueTask(){
	for(size_t i=0; i < waiting.size(); ++i){
		if( waiting[i]->getIoDelay() ){
			waiting[i]->decrementIoDelay();
			if( !waiting[i]->getIoDelay() ){
				resetBurstNdelay(waiting[i]);
				ready.push_back(waiting[i]);
				cout << "Time " << now << ": Moving process " 
					<< waiting[i]->getPid() << " from waiting to ready\n";
				waiting.erase(waiting.begin()+i);
				resetCtxDelay();
				if(contextSwitchDelay) contextSwitchDelay--;
			}
		}
	}
}

void FCFS::arrivalQueueTask(){
	while(arrivalQueue.size() && arrivalQueue.front()->getArrival() == now){
		resetBurstNdelay(arrivalQueue.front());
		ready.push_back(arrivalQueue.front());
		cout << "Time " << now << ": Moving process " 
			<< arrivalQueue.front()->getPid() 
			<< " from arrival to ready\n";
		arrivalQueue.erase(arrivalQueue.begin());
	}
}

void FCFS::readyQueueTask(){
	if(ready.size()){
		if(!running || !running->getCpuTotal( )){
			running = ready[0];
			ready.erase( ready.begin() );
			cout << "Time " << now << ": Moving process " << running->getPid() 
				<< " from ready to running. Remaining Time: " 
				<< running->getCpuTotal() << ".\n";
			resetCtxDelay();
		}
	}

	if(contextSwitchDelay){
		contextSwitchDelay--;
		return;
	}

	if(running){
		running->incrementElapsed( );
		running->decrementCpuTotal();

		double tmp;
		bool eob(false), bProb(false);

		if(!running->getCpuTotal()){
			eob = true;
			cout << "Time " << now << ": Process " << running->getPid() << " finished.\n";
			running = NULL;
			return;
		}

		if(running->getElapsed( ) < running->getAvgBurst( ) -1 ) eob = false;
		else if(running->getElapsed( ) == running->getAvgBurst( ) -1 ){
			tmp = getProbability();
			if(tmp <= 1.0 / 3 ) eob = true;
		}
		else if(running->getElapsed( ) == running->getAvgBurst( ) ){
			tmp = getProbability();
			if(tmp <= 1.0 / 2 ) eob = true;
		}
		else if(running->getElapsed( ) > running->getAvgBurst( ) ) eob = true;
	
		if(eob){
			cout << "Time " << now << ": Process " << running->getPid() 
				<< " ending burst(" << running->getElapsed() 
				<< "). Remaining Time: " << running->getCpuTotal() << ".\n";

			waiting.push_back(running);
			running = NULL;
			resetCtxDelay();
			if(contextSwitchDelay) contextSwitchDelay--;
		}
	}
}

void FCFS::resetBurstNdelay(Process* const p){
	p->setIoDelay(this->ioDelay);
	p->resetElapsed(); // needs to be computed by the random file
}
