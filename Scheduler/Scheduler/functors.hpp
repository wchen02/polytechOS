#ifndef FUNCTORS_H
#define FUNCTORS_H
#include <iostream>
#include "process.hpp"

/* Will be able to hand it to the priority queue for comparing
* which Process has the least remaining time
* for the SRTN scheduling algorithm
*/
class LeastRemainingTime{
public:

	bool operator( )( Process * lhs, Process * rhs )const {
		return lhs->getPrediction( ) < rhs->getPrediction( );
	}
};

//class LeastBurst{
//public:
//	bool operator( )( const Process & lhs, const Process & rhs ){
//		return lhs.getElapsed( ) < rhs.getElapsed( );
//	}
//
//};

#endif
