#ifndef SRTN_H
#define SRTN_H
#include <vector>
#include <queue>
#include "scheduler.h"
#include "functors.hpp"

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

class Srtn : public Scheduler{
public:
	/* Inheritance methods */
	//the following methods are for the ready queue only.
	Process top( ) const;          
	void    pop( );
	void    push(const Process & newProcess);
	int     size( ) const;
	bool    empty( ) const;

	Srtn();	
	/* for consistency, they will be the actual implementations
	* of the functions mentioned above, meaning, pop will return
	* void pop_readyQueue ( )
	*/
	void	push_readyQueue( const Process & newProcess );
	void	pop_readyQueue( );
	Process top_readyQueue( );
	int		size_readyQueue( );
	bool	empty_readyQueue( );

	void	push_waitingQueue( const Process & newProcess );
	void    pop_waitingQueue( );
	Process top_waitingQueue( );
	int		size_waitingQueue( );
	bool	empty_waitingQueue( );


	double predictNextBurst( );
	void updateLastBurst( int );

private:
	std::priority_queue<Process, std::vector<Process>, LeastRemainingTime > ready;
	std::priority_queue<Process, std::vector<Process>, LeastRemainingTime > blocking;
	int lastBurst;
	double history;
};



#endif 