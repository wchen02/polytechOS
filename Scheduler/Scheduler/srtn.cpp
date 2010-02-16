#include "srtn.h"
#include "scheduler.h"
#include "functors.hpp"
#include <iostream>
using namespace std;

double Srtn::predictNextBurst( ){ 
	return history = ( getAgingRatio( ) * lastBurst ) + ( ( 1 - getAgingRatio( ) ) * history );
}

/* Inheritance methods */
//the following methods are for the ready queue only.
Process Srtn::top( ) const { 
	return Srtn::top_readyQueue( ); 
}          
void    Srtn::pop( ){ 
	Srtn::pop_readyQueue( );
}
void    Srtn::push( const Process & newProcess ) const {
	Srtn::push_readyQueue( const Process & newProcess );
}
int     Srtn::size( )const {
	return Srtn::size_readyQueue( ); 
}
bool    Srtn::empty( ) const {
	return Srtn::empty_readyQueue( ); 
}

Srtn::Srtn(){}
/* for consistency, they will be the actual implementations
* of the functions mentioned above, meaning, pop will return
* void pop_readyQueue ( )
*/
void   Srtn::push_readyQueue( const Process & newProcess ){
	newProcess.setiodelay( Scheduler::getIoDelay( ) );
	ready.push( newProcess );
}
void   Srtn::pop_readyQueue( ){
	ready.pop( );
}
Process   Srtn::top_readyQueue( ){
	ready.top( );
}
int   Srtn::size_readyQueue( ){
	return ready.size( );
}
bool Srtn::empty_readyQueue( ){
	ready.empty( );
}


void   Srtn::push_waitingQueue( const Process & newProcess ){
	newProcess.setiodelay( Scheduler::getIoDelay( ) );
	blocking.push( newProcess );
}
void   Srtn::pop_waitingQueue( ){
	blocking.pop( );
}
Process   Srtn::top_waitingQueue( ){
	blocking.top( );
}
int   Srtn::size_waitingQueue( ){
	return ready.size( );
}
bool Srtn::empty_waitingQueue( ){
	blocking.empty( );
}



void Srtn::updateLastBurst( int burst){
	lastBurst = burst;
}