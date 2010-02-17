#include "srtn.h"
#include "scheduler.h"
#include "functors.hpp"
#include <iostream>
using namespace std;

double Srtn::predictNextBurst( ){ 
	return history = ( getAgingRatio( ) * lastBurst ) + ( ( 1 - getAgingRatio( ) ) * history );
}

Srtn::Srtn(const std::string& resourceFile) : Scheduler(resourceFile){}

void Srtn::updateLastBurst( int burst){
	lastBurst = burst;
}