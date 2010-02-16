#ifndef FUNCTORS_H
#define FUNCTORS_H
#include <iostream>
#include "process.h"

/* Will be able to hand it to the priority queue for comparing
* which Process has the least remaining time
* for the SRTN scheduling algorithm
*/
class LeastRemainingTime{
public:
  
   bool operator( )( const Process & lhs, const Process & rhs ){
	   return lhs.getTotalcpu() < rhs.getTotalcpu();
      }
};

// well, since we are using priority queue for both of our algorithms, we need to order them in FCFS fashion.
class CompareFCFS { // not needed for fcfs read specs
public:
	bool operator()(const Process& rhs, const Process& lhs) const{
		return rhs.getId() < lhs.getId();	
	} 
};

#endif
