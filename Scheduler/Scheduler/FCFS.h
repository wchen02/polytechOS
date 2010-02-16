#ifndef FCFS_H
#define FCFS_H

#include <queue>
#include <vector>
#include <string>
#include "functors.hpp"
#include "process.h"
#include "scheduler.h"

class FCFS : public Scheduler{
public:
	FCFS(std::string resourceFile);

	Process top() const;
	void pop();
	void push(Process newProcess);
	int size() const;
	bool empty() const;

	/* FCFS. Schedule the processes in the order in which they become ready.
	o Non-preemptive
	o Allow each process to run for its complete burst
	o When the burst ends, move the process to the wait queue.*/
	//void FCFS();

	/* Shortest Remaining Time Next with Aging.
	o Premptive.
	o Predict the next burst based on the last burst and the history, using the formula:
	prediction = (AgingRatio * lastBurst) + ((1 - AgingRatio) * history)
	o AgingRatio is provided in the resource file.
	o The current prediction becomes the history, next time around.
	o Note that the prediction is used for the process's relative priority.
	o If the aging algorithm predicts that a process will have a CPU burst of initialPrediction, then after the process has run for one unit of time, the prediction for the remaining time to the burst will be initialPrediction - 1. It is the prediction for how much time remains before a process finishes its burst that is used to determine its place in the ready queue and whether or not a ready process should preempt the running process.
	*/
	//void SRTN();
	//The scheduling algorithms are not aware of how long a process's burst will actually be. They only become aware when a process's burst ends. By keeping all times as integers (except for the predicted burst of the aging algorithm), this is easy to manage.
private:
	/*A process can only run as long as its CPU burst, then it has to stop while it's next I/O request is being serviced.
	* While the process is waiting for the I/O to complete, it is blocked and will be placed on a "Wait Queue".
	* For your convience, all I/O requests for this simulator will take the same amount of time, which is specified in the resource file.
	* When the I/O is complete, the process will be placed back on the appropriate "Ready Queue".
	*/
	std::priority_queue<Process, std::vector<Process>, CompareFCFS> waiting, ready;
};

#endif
