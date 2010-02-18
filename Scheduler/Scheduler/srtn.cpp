#include "srtn.h"
#include "scheduler.h"
#include "functors.hpp"
#include <iostream>

using namespace std;

double Srtn::predictNextBurst( ){ 
	return history = ( getAgingRatio( ) * lastBurst ) + ( ( 1 - getAgingRatio( ) ) * history );
}

Srtn::Srtn(const std::string& resourceFile) : Scheduler(resourceFile){ 
	lastBurst = 0;	
	history = 0;
}

void Srtn::updateLastBurst( int burst){
	lastBurst = burst;
}

void Srtn::waitingQueueTask(){

}
void Srtn::readinQueueTask(){

}
void Srtn::readyQueueTask(){

}

void Srtn::run(){
	for(int clock_tick, i = 0; i < arrival.size(); ++i ) {
		clock_tick = i;
		Process* running = NULL;
		//check for first runs until first element is moved
		if( arrival[ i ].getarrivalTime( ) == clock_tick )
			ready.push_back( arrival[ i ] );

		if(running == NULL){
			running = & ready.pop_front( );
			//Sleep(contextSwitchDelay);
		}
		
		if(running != NULL ){
			/*run for 1 time slot*/
			clock_tick = i += 1;
			if( running->getTotalcpu( ) ){
				/*if there is something to run*/
				running->decreasecpuTotal( 1 );

				if( 0 < running->getcpuBurst( ) )
					running->decreasecpuBurst( 1 );
				
				else if( 0 == running->getcpuBurst( ) ){
					//wait(contextSwitchDelay);------------------------>> need to write context switch function to do i+= contextSwithcDelay then loop through the availabel array and make sure that all the processes that were not pushed to ready queue are pushed
					running->resetcpuBurst( );
					blocking.push_back( *running );
					running = NULL;
				}

			}
			else if(running->getTotalcpu( ) == 0 ){
				//Sleep(contextSwitchDelay);
				running = NULL;
			}


			if( arrival[ i ].getarrivalTime( ) == clock_tick )
				ready.push_back( arrival[ i ] );
		}

		for(int j = 0; j < blocking.size( ); ++j ){
			//decrease ioDelay
			blocking[j].setIOdelay( blocking[j].getIOdelay( ) - 1);
			//if io delay is = 0, move back to ready queue
			if( blocking[ j ].getIOdelay( ) == 0 ){
				ready.push_back( blocking[ i ] );
				blocking.removeIndex( i );
			}
		}
		
	}

}