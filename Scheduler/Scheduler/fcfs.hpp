#ifndef FCFS_H
#define FCFS_H

#include <queue>
#include <vector>
#include <string>
#include "functors.hpp"
#include "process.hpp"
#include "scheduler.hpp"

class FCFS : public Scheduler{
public:
	FCFS(const std::string& resourceFile);
	void run();

private:
	inline void printSchedulerInfo() const;

	/* moves processes from waitingQueue to readyQueue when ioDelay is done */
	inline void waitingQueueTask();

	/* moves processes from arrivalQueue to readyQueue when the arrival time of
		the top process in arrivalQueue matches now */
	inline void arrivalQueueTask();

	void readyQueueTask();
	inline void resetBurstNdelay(Process* const);

	std::vector<Process*> ready, waiting;
	Process* running;
};

#endif
