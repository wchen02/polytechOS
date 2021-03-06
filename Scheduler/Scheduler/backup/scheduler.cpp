#include <deque>
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

Parameter Scheduler::getPara(const string& param){
	if(param == "processfile")
		return ProcessFile;
	else if (param == "iodelay")
		return IOdelay;
	else if (param == "contextswitchdelay")
		return ContextSwitchDelay;
	else if (param == "agingratio")
		return AgingRatio;
	else if (param == "debug")
		return Debug;
	else return Invalid;
}


Scheduler::Scheduler(const string& resourceFile) : now(0) {
	readResource(resourceFile);
}

void Scheduler::readProcess(const string& filename){
	ifstream ifs(filename.c_str());
	if(!ifs) exit(1);

	int id, arrivalTime, totalCPU, avgBurst;

	if(DEBUG) cout << "Reading in Processes\n\tID:\tArrival Time\tTotal CPU\tAvgBurst\n";
	while(ifs >> id >> arrivalTime >> totalCPU >> avgBurst){
		if(DEBUG) cout << "\t" << id << "\t" << arrivalTime << "\t" << totalCPU << "\t" << avgBurst << endl;
		arrival.push_back(Process(id, arrivalTime, totalCPU, avgBurst));
	}
}

int Scheduler::random(const std::string& randNumfile){ 
	/* keep the size of the rand dequeue reasonable, 100 elements max,
	* but only read if the queue is about half the size
	*/
	int tmpFront, tmp(0), tmp1(100), skipLines;
	if( !rand.empty( ) ) {
		tmpFront = rand.front();
		rand.pop_front();
		return tmpFront;
	}

	ifstream ifl( randNumfile.c_str( ) );

	if(!ifl){
		if(DEBUG) cerr << "\nERROR: The file given for the random numbers, does not exist or is currently locked by other process\n";
		exit(1);
	}

	/* since the size is less than what we want, add some more from file, 
	*/


	/* if its the end of file, start from the top
	*/
	if( ifl.eof( ) )
		lineNumrand = 0;

	/* skip the number of lines already read
	*/
	skipLines = lineNumrand;

	while( ifl >> tmp && 0 < tmp1){

		if( skipLines < 0  ){
			rand.push_back( tmp );
			lineNumrand++;
			tmp1--;
		}
		skipLines--;

	}

	tmpFront = rand.front( );
	rand.pop_front( );
	return tmpFront;
}


void Scheduler::setValue(const Parameter& param, const string& value){
	stringstream stream;
	string tmp;

	switch(param){

   case ProcessFile: 
	   readProcess(value);
	   break;
   case IOdelay: 
	   stream << value;
	   stream >> ioDelay;
	   break;
   case ContextSwitchDelay: 
	   stream << value;
	   stream >> contextSwitchDelay;
	   break;
   case AgingRatio: 
	   stream << value;
	   stream >> agingRatio;
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


void Scheduler::readResource(const string& filename){
	ifstream ifs(filename.c_str());
	if(!ifs) exit(1);

	string tmp, parameter, value;
	size_t pos;
	Parameter param;

	while(ifs >> tmp){
		if(DEBUG) cout << "Read in: " << tmp << endl;

		pos = tmp.find("=");
		if(DEBUG) cout << "\tpos: " << pos << endl;

		parameter = lowerCase( tmp.substr(0, pos) );
		if(DEBUG) cout << "\tparameter: " << parameter << endl;

		param = getPara(parameter);
		if(DEBUG) cout << "\tparam: " << param << endl;

		if(param == Invalid) return;

		value = lowerCase( tmp.substr(pos+1, tmp.size()) );
		if(DEBUG) cout << "\tvalue: " << value << endl;
		setValue(param, value);
	}
}

int Scheduler::avgBurst(const Process& process){
	return 0;
}

double Scheduler::getAgingRatio(){
	return agingRatio;
}