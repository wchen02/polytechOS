#ifndef _PROCESS_H_
#define _PROCESS_H_
#include <iostream>

class Process{

	friend std::ostream & operator<<( std::ostream & out, const Process & p );

public:

	Process( int id,             //Process ID for the scheduler
		int arrivedTime,    //Arrival Time for FCFS algo
		int totalCPU,       //Maximun CPU this process can use
		int averageBurst);   //Average CPU power this process can use

	Process ();

	bool isReady( ) const;        //determines wheather or not this
	//process can run, note once the process

	int getPId( ) const;            //returns the process ID

	int getCpuTotal( ) const;      //returns the maximun CPU time allowed for

	void decrementCpuTotal(); //decrements the cpu total time

	void decrementCpuBurst(); //decrements the cpu burst time

	int getCpuBurst( )const;

	void resetCpuBurst();
		
	void setCpuBurst(int newBurst); // temporary
	

	int getArrivalTime( ) const;          //returns when the process arrived
	
	//for different scheduler algorithms
	void setProcess(int, int, int, int);

	int getIOdelay() const;
	void setIOdelay(int);

	
private:
	int cpuMax, cpuBurst, ioDelay;
	int pid, arrivalTime;
	int originalBurst;
	bool run;
};

#endif
