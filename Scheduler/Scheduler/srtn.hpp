#ifndef SRTN_H
#define SRTN_H
#include <vector>
#include <queue>
#include "scheduler.h"
#include "functors.hpp"

using namespace std;
class Srtn : public Scheduler{
public:


	Srtn(const std::string& resourceFile): Scheduler(resourceFile), running(NULL){ }

	void run( ){
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

private:
	double predictNextBurst(Process * p ){
		//history = (int)p->getPrediction( );
		double tmp;
		tmp = ( getAgingRatio( ) * p->getLastBurst( ) ) + ( ( 1 - getAgingRatio( ) ) * p->getHistory( ) );
		p->setPrediction(tmp);
		return tmp;
	}

	void arrivalQueueTask(){
		while(arrivalQueue.size() && arrivalQueue.front()->getArrival() == now){
			resetBurstNdelay(arrivalQueue.front());
			ready.push(arrivalQueue.front());
			cout << "Time " << now << ": Moving process " 
				<< arrivalQueue.front()->getPid() 
				<< " from arrival to ready. Prediction "
				<< arrivalQueue.front()->getPrediction() << endl;;
			arrivalQueue.erase(arrivalQueue.begin());
		}

	}

	void  waitingQueueTask(){
		for(size_t i=0; i < waiting.size(); ++i){
			if( waiting[i]->getIoDelay() ){
				waiting[i]->decrementIoDelay();
				if( !waiting[i]->getIoDelay() ){
					resetBurstNdelay(waiting[i]);
					ready.push(waiting[i]);
					cout << "Time " << now << ": Moving process " 
						<< waiting[i]->getPid() << " from waiting to ready. Prediction "
						<< waiting[i]->getPrediction() << endl;;
					waiting.erase(waiting.begin()+i);
					resetCtxDelay();
					if(contextSwitchDelay) contextSwitchDelay--;
				}
			}
		}
	}


	void  readyQueueTask(){

		if(ready.size()){
			if(!running || !running->getCpuTotal( )){
				running = ready.top();
				ready.pop();
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

			/* preempt Part 1*/
			//calculate the nextBurst

			predictNextBurst(running);

			if(ready.size( )){
				running->incrementLastBurst( ); // not sure
				if(running->getPrediction( ) < ready.top( )->getPrediction( )){
					cout<<"Process: "<< running->getPid( )
						<<" preempted by process " << ready.top( )->getPid( ) << endl;
					running->resetLastBurst( );
					Process * tmpProc = running;
					running = ready.top();
					ready.pop();
					ready.push(tmpProc);
					return;
				}
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
				running->resetLastBurst();
				waiting.push_back(running);
				running = NULL;
				resetCtxDelay();
				if(contextSwitchDelay) contextSwitchDelay--;
			}
		}

	}
	void printSchedulerInfo(){
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
		if(ready.size()){
			vector<Process* > tmpPrint;
			size_t i;												/*modify for eficiency can't think of how to get iterator*/
			for(i=0; i < ready.size(); i++){			
				tmpPrint.push_back(ready.top());
				ready.pop();

			}
			for(i=0; i < tmpPrint.size(); i++){
				cout << " "<< tmpPrint[i]->getPid()
					<<"( "<< tmpPrint[i]->getPrediction( ) << " ) ";
				ready.push(tmpPrint[i]);
			}

		}

		else cout << "none";

		cout << "\nWaiting: ";
		if(waiting.size())
			for(size_t i=0; i < waiting.size(); i++)
				cout << " " << waiting[i]->getPid() 
					 << "( " << waiting[i]->getPrediction( )<<" )";
		else cout << " none";
		cout << "\n===============\n";

	}

	void resetBurstNdelay(Process* const p){
		p->setIoDelay(this->ioDelay);
		p->resetElapsed(); // needs to be computed by the random file
	}


	/**********************/
	/* private attributes */

	priority_queue<Process*, vector<Process*>, LeastRemainingTime> ready;
	vector<Process*> waiting;
	int history;
	Process* running;
};

#endif 