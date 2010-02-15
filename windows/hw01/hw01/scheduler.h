#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include <string>
#include "process.h"


bool DEBUG(true);

enum Parameter { ProcessFile, IOdelay, ContextSwitchDelay, AgingRatio, AlgorithmChoice, Debug, Invalid };

enum Algorithm { FCFS, SRTN };

class Scheduler{
public:
   //Scheduler();
   Process top();
   Process pop();
   void push(Process newProcess);
   int size();
   bool empty();
	
   Parameter getPara(std::string param);

   /* may take advantage of inline, since we will be calling it
    * often enough, it its worth inline'ing the function to 
    * gen rand ints
    */
   int nextrandInt( std::string randNumfile="" )  ;

   void readProcess(std::string filename); // adds new process to the queue from the file
   /*Arrival Time: The time that the request is initially made to run the process. Obviously, it is not possible for the process to start running before this time.
    * Total CPU: The total time that the process will need to use the CPU.
    * Average CPU Burst:
    o We can't really know in advance how long a cpu burst will be. For the purpose of this simulation, I am giving you a average length for each process's cpu burst.
    o At each clock tick, you will query the process as to whether it is finished with its burst. The process will respond true/false, based on a probabilty distribution. We will use an even distribution, that is there will be an equal likelihood that any of the three burst values {average-1, average, average+1} will terminate the process's burst.
    + A file of random numbers has been provided for computing the bursts.
    + Write a function random() that each time it is called returns the next number in the file. If you run out of numbers, then start from the beginning.
    o Preemptive algorithms, such as SRTN, may interrupt a process before the current burst is complete. Such an interruption does not terminate the burst. When the process is resumed, it will be continuing with whatever is left of its last burst.
   */
   void setValue(Parameter param, std::string value);
   void readResource(std::string filename);

   /*
     ProcessFile=Processes.txt
     IOdelay=2
     ContextSwitchDelay=1
     AgingRatio=.5
     Debug=true
   */
   int avgBurst(Process process);


   /*    *   FCFS. Schedule the processes in the order in which they become ready.
	 o Non-preemptive
	 o Allow each process to run for its complete burst
	 o When the burst ends, move the process to the wait queue.*/
   void FCFS();
    
   /* Shortest Remaining Time Next with Aging.
      o Premptive.
      o Predict the next burst based on the last burst and the history, using the formula:
      prediction = (AgingRatio * lastBurst) + ((1 - AgingRatio) * history)
      o AgingRatio is provided in the resource file.
      o The current prediction becomes the history, next time around.
      o Note that the prediction is used for the process's relative priority.
      o If the aging algorithm predicts that a process will have a CPU burst of initialPrediction, then after the process has run for one unit of time, the prediction for the remaining time to the burst will be initialPrediction - 1. It is the prediction for how much time remains before a process finishes its burst that is used to determine its place in the ready queue and whether or not a ready process should preempt the running process.
   */
   void SRTN();
   //The scheduling algorithms are not aware of how long a process's burst will actually be. They only become aware when a process's burst ends. By keeping all times as integers (except for the predicted burst of the aging algorithm), this is easy to manage.
private:
   /*A process can only run as long as its CPU burst, then it has to stop while it's next I/O request is being serviced.
    * While the process is waiting for the I/O to complete, it is blocked and will be placed on a "Wait Queue".
    * For your convience, all I/O requests for this simulator will take the same amount of time, which is specified in the resource file.
    * When the I/O is complete, the process will be placed back on the appropriate "Ready Queue".
    */
   std::priority_queue<Process> waiting;
   std::priority_queue<Process> ready;
   int ioDelay, contextSwitchDelay;
   double agingRatio;
   Algorithm algorithm;

   std::deque<int> rand; // why a deque?
   int lineNumrand;
};





#endif
