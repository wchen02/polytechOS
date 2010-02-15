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
  
    bool isReady( ) const;        //determines wheather or not this
    //process can run, note once the process
  
    int getId( ) const;            //returns the process ID
  
    int getTotalcpu( ) const;      //returns the maximun CPU time allowed for
    //this process
  
    void decreasecpuTotal( const int d ); //decreases the cpu burst time
    
    int getcpuBurst( )const;
  
    int getarrivalTime( ) const;          //returns when the process arrived
    //for different scheduler algorithms
    void setProcess(int, int, int, int);

private:

    int pid;              
    int cpuMax;           
    int cpuBurst;
    int arrivalTime;
    bool run;
};

#endif
