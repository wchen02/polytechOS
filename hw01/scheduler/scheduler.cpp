#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "process.h"
#include "scheduler.h"

using namespace std;

string lowerCase(string str){
   for(size_t i = 0; i < str.size(); ++i)
      str[i] = static_cast<char>( tolower(str[i]) );
   return str;
}

Parameter Scheduler::getPara(string param){
   if(param == "processfile")
      return ProcessFile;
   else if (param == "iodelay")
      return IOdelay;
   else if (param == "contextswitchdelay")
      return ContextSwitchDelay;
   else if (param == "agingratio")
      return AgingRatio;
   else if (param == "algorithmchoice")
      return AlgorithmChoice;
   else if (param == "debug")
      return Debug;
   else return Invalid;
}

//Scheduler::Scheduler(){}
Process Scheduler::top(){
   return ready.top();
}

/*Process Scheduler::pop(){
  return ready.pop( );
  }*/

void Scheduler::push(Process newProcess){
   ready.push(newProcess); // need to decide the algorithm choice before this
}

int Scheduler::size(){
   return ready.size();
}

bool Scheduler::empty(){
   return ready.empty();
}	

void Scheduler::readProcess(string filename){
   ifstream ifs(filename.c_str());
   if(!ifs) exit(1);

   int id, arrivalTime, totalCPU, avgBurst;

   if(DEBUG) cout << "Reading in Processes\n\tID:\tArrival Time\tTotal CPU\tAvgBurst\n";
   while(ifs >> id >> arrivalTime >> totalCPU >> avgBurst){
      if(DEBUG) cout << "\t" << id << "\t" << arrivalTime << "\t" << totalCPU << "\t" << avgBurst << endl;
      push(Process(id, arrivalTime, totalCPU, avgBurst));
      // continue from here
      // not finish =.=, next step add to queue
   }
}

int Scheduler::nextrandInt( std::string randNumfile )  { 
   /* keep the size of the rand dequeue reasonable, 100 elements max,
    * but only read if the queue is about half the size
    */
    int tmpFront;
    if( !rand.empty( ) ) {
	// return rand.pop_front( ); // pop_front returns void
	tmpFront = rand.front();
	rand.pop_front();
	return tmpFront;
    }

   if( randNumfile.length() == 0 )/*default file if none input*/
      randNumfile = "../misc/random-numbers";
   
   ifstream ifl( randNumfile.c_str( ) );
   
   if(!ifl){
      exit(1);

      if(DEBUG)
	 cerr << "\nERROR: The file given for the random numbers,"
	    " does not exist or is currently locked by other process " << endl;
   }
   
   int tmp = 0, tmp1 = 100;
   /* since the size is less than what we want, add some more from file, 
    */


   /* if its the end of file, start from the top
    */
   if( ifl.eof( ) )
      lineNumrand = 0;
   
   /* skip the number of lines already read
    */
   int skipLines = lineNumrand;

   while( ifl >> tmp && 0 < tmp1){
      
      if( skipLines < 0  ){
	 rand.push_back( tmp );
	 lineNumrand++;
	 tmp1--;
      }
      skipLines--;
      
   }
      
   rand.pop_front( );

   
   
}


void Scheduler::setValue(Parameter param, string value){
   stringstream stream;
   string tmp;

   switch(param){
      
   case ProcessFile: 
      readProcess(value);
      break;
   case IOdelay: 
      stream >> value;
      stream << ioDelay;
      break;
   case ContextSwitchDelay: 
      stream >> value;
      stream << contextSwitchDelay;
      break;
   case AgingRatio: 
      stream >> value;
      stream << agingRatio;
      break;
   case AlgorithmChoice:
      tmp = lowerCase(value);
      if(tmp == "fcfs")
	 cout << "FIX ENUM" << endl;
      //Algorithm = FCFS;
      else if (tmp == "srtn")
	 cout << "FIX ENUM" << endl;
      //Algorithm = SRTN;
      break;
   case Debug: 
      tmp = lowerCase(value);
      DEBUG = (tmp == "true") ? true : false;
      break;
   default:
      break;
   }
   if(DEBUG) cout << "\t\tValue: " << value << endl;
}


void Scheduler::readResource(string filename){
   ifstream ifs(filename.c_str());
   if(!ifs) exit(1);

   string tmp, parameter, value;
   size_t pos;
   Parameter param;

   while(ifs >> tmp){
      if(DEBUG) cout << "Read in: " << tmp << endl;

      pos = tmp.find("=");
      if(DEBUG) cout << "\tpos: " << pos << endl;

      parameter = lowerCase( tmp.substr(0, pos-1) );
      if(DEBUG) cout << "\tparameter: " << parameter << endl;

      param = getPara(parameter);
      if(DEBUG) cout << "\tparam: " << param << endl;

      if(param == Invalid) return;

      value = lowerCase( tmp.substr(pos+1, tmp.size()) );
      if(DEBUG) cout << "\tvalue: " << value << endl;
      setValue(param, value);
   }
}

//int Scheduler::avgBurst(Process process){}
void Scheduler::FCFS(){}
void Scheduler::SRTN(){}
