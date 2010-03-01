#ifndef _PROCESS_H_
#define _PROCESS_H_
#include <iostream>
#include <assert.h>

class Process{
public:
	Process( int pid, int arrivedTime, int cpuTotal, int avgBurst)
		:pid( pid ), arrival( arrivedTime ), cpuTotal( cpuTotal ),  
		avgBurst( avgBurst ),ioDelay( 0 ), elapsed( 0 ), lastBurst( 0 ),
		prediction( 0.0 ), history(0){
		assert( pid >= 0 );
		assert( arrivedTime >= 0 );
		assert( cpuTotal >= 0 );
		assert( avgBurst >= 0 );
	}

	// following methods should be self-explanatory

	inline int getPid() const{ return pid; }

	inline int getCpuTotal() const{ return cpuTotal; }

	inline int getAvgBurst( )	const { return avgBurst; }

	inline int getArrival( ) const { return arrival; }

	inline int getElapsed( ) const { return elapsed; }

	inline int getIoDelay() const{ return ioDelay; }

	inline double getPrediction( )const{ return prediction; }

	inline int getHistory( ) const{ return history; }

	inline int getLastBurst( )const{ return lastBurst; }

	inline void incrementLastBurst(){ lastBurst++; }
	
	inline void incrementElapsed( ){ elapsed++; }

	inline void resetElapsed(  ){ elapsed = 0; }

	inline void resetLastBurst(  ){ elapsed = 0; }
	
	
	
	inline void setIoDelay(unsigned newDelay){
		ioDelay = newDelay;
		assert(ioDelay >= 0);
	}

	inline void decrementCpuTotal( ){
		cpuTotal--;
		assert(cpuTotal >= 0);
	}

	inline void decrementIoDelay( ){
		ioDelay--;
		assert(ioDelay >= 0);
	}

	inline void setPrediction(double p){
		history = (int)prediction;
		prediction  = p;
	}

	

private:
	int cpuTotal, elapsed, ioDelay;
	const int pid, arrival, avgBurst;
	int lastBurst, history;
	double prediction;
};

#endif
