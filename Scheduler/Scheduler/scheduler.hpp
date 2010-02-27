#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include <string>
#include <vector>
#include "functors.hpp"
#include "process.hpp"
#define DEBUG true

enum Parameter { ProcessFile, IOdelay, ContextSwitchDelay, AgingRatio, Debug, Invalid };

class Scheduler{
public:

	Scheduler(const std::string& resourceFile);
	
	int random(const std::string& randomFile="random-numbers");

	virtual void run() = 0;

protected:

	double getAgingRatio();

	/* returns prob from reading random value */
	double getProbability( ); 

	/* contextSwitchDelay = ctxDelayOld */
	void resetCtxDelay(); 

	std::vector<Process*> arrivalQueue;
	std::deque<int> rand;

	int ioDelay, 
		contextSwitchDelay, // changing contextSwitchDelay
		now, // current clock periods 
		num2skip4rand, // num of lines to skip to read random
		randIndex, // num of rands read
		contextSwitchDelay_Old; // contextSwitchDelay read from the resource file
	double agingRatio; 

private:

	/* reads and set the value of each Parameter in the resource file */
	inline void readResource(const std::string& filename);

	/* sets the value of a given Parameter */
	inline void setValue(const Parameter& param, const std::string& value);

	/* reads processes into the arrivalQueue */
	inline void readProcess(const std::string& filename);

	/* converts a string to Parameter */
	inline Parameter getPara(const std::string& param);
};

#endif
