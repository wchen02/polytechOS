#include "process.h"
#include <iostream>

using namespace std;

Process::Process( int id,             //Process ID for the scheduler
				 int arrivedTime,    //Arrival Time for FCFS algo
				 int totalCPU,       //Maximun CPU this process can use
				 int averageBurst)   //Average CPU power this process can use
				 :pid( id ), arrivalTime( arrivedTime ), cpuMax( totalCPU ),  
				 cpuBurst( averageBurst )
{
	ioDelay = 0;
	run = false; 
}

bool Process::isReady() const{ return run; }

int Process::getPId() const{ return pid; }

int Process::getCpuTotal() const{ return cpuMax; }

//void Process::decreasecpuTotal( int d ){
//	cpuMax -= d;
void Process::decrementCpuTotal(){
	cpuMax--;
	if( cpuMax < 0) {     //check to see if the burst becomes
		cpuMax = 0;          //negative, if so disable future    
		run = false;  //runs of the process
	}
}
/*
 You did not allow me to make the var public, but this doesn't protect against anything, 
 other programmers can still pass in negative value and values other than 1. 
 setters are used to limit what others can modify!
 */
//void Process::decreasecpuBurst( int d ){
	//cpuBurst -= d;	
void Process::decrementCpuBurst(){
	cpuBurst--;
	if( cpuBurst < 0) {     //check to see if the burst becomes
		cpuBurst = 0;          //negative, if so disable future    
	}
}
int Process::getArrivalTime( ) const { return arrivalTime; }

int Process::getCpuBurst( ) const { return cpuBurst; }

std::ostream & operator<<( std::ostream & out, const Process & p){
	out << "Process ID : "<< p.pid << endl;
	out << "Arrival Time : "<< p.arrivalTime << endl;
	out << "Max CPU : "<< p.cpuMax << endl;
	out << "CPU Burst : "<< p.cpuBurst << endl;

	return out;
}

/* what's the point of encapsulation if you can do this? */
//void Process::setProcess(int processid, int cputotal, int cpuburst, int arrivaltime){
//	pid = processid;
//	cpuMax = cputotal;
//	cpuBurst = cpuburst;
//	arrivalTime = arrivalTime;
//}

int Process::getIOdelay() const{
	return ioDelay;
}
void Process::setIOdelay(int newDelay){ // note to self, bad setter
	ioDelay = newDelay;
}

void Process::resetCpuBurst( ){ // needs random probability
	cpuBurst = originalBurst;
}

void Process::setCpuBurst(int newBurst){ // temporary
	cpuBurst = newBurst;
}