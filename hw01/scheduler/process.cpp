#include "process.h"
#include <iostream>

Process::Process( int id,             //Process ID for the scheduler
		  int arrivedTime,    //Arrival Time for FCFS algo
		  int totalCPU,       //Maximun CPU this process can use
		  int averageBurst)   //Average CPU power this process can use
  :pid( id ), arrivalTime( arrivedTime ), cpuMax( totalCPU ),  
   cpuBurst( averageBurst ){ run = false; }

bool Process::isReady() const{ return run; }

int Process::getId() const{ return pid; }

int Process::getTotalcpu() const{ return cpuMax; }

void Process::decreaseCpuBurst( int d ){
  cpuBurst -= d;
  if( d < 0) {     //check to see if the burst becomes
    d = 0;          //negative, if so disable future    
    run = false;  //runs of the process
  }
}

int Process::getarrivalTime() const{ return arrivalTime; }

std::ostream & operator<<( std::ostream & out, const Process & p){
  out << "Process ID : "<< p.pid << endl;
  out << "Arrival Time : "<< p.arrivalTime << endl;
  out << "Max CPU : "<< p.cpuMax << endl;
  out << "CPU Burst : "<< p.cpuBurst << endl;
  
  return out;
}

void Process::setProcess(int processid, int cputotal, int cpuburst, int arrivaltime){
  pid = processid;
  cpuMax = cputotal;
  cpuBurst = cpuburst;
  arrivalTime = arrivalTime;
}


