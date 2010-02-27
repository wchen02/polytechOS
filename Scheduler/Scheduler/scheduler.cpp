#include <deque>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "process.hpp"
#include "scheduler.hpp"

using namespace std;

inline string lowerCase(string str){
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
	else if (param == "DEBUG")
		return Debug;
	else return Invalid;
}

double Scheduler::getProbability( ){ 
	long long int31(1);
	int31 <<= 31;
	long long rand = random( );
	assert(rand >= 0);

	double prob = static_cast<double>( rand ) / int31;
	if(DEBUG)
		cout <<"[Random Number (" << randIndex 
		<<"): "<< rand << endl
		<< "Probability: " << prob << endl;
	return prob;
}

Scheduler::Scheduler(const string& resourceFile) : 
now(0), num2skip4rand( 0 ), randIndex( 0 ), contextSwitchDelay( 0 ) {
	readResource(resourceFile);
}

void Scheduler::readProcess(const string& filename){
	ifstream ifs(filename.c_str());
	assert( ifs );

	int id, arrivalTime, totalCPU, avgBurst;

	if(DEBUG) cout << "Reading in Processes\n\tID:\tArrival Time\tTotal CPU\tAvgBurst\n";
	while(ifs >> id >> arrivalTime >> totalCPU >> avgBurst){
		if(DEBUG) cout << "\t" << id << "\t" << arrivalTime << "\t" << totalCPU << "\t" << avgBurst << "\n";
		arrivalQueue.push_back(new Process(id, arrivalTime, totalCPU, avgBurst));
	}
}

void Scheduler::resetCtxDelay(){ contextSwitchDelay = contextSwitchDelay_Old; }

int Scheduler::random(const std::string& randomFile){ 
	/* keeps the maximum size of the rand dequeue 100 at anytime */

	int front;

	if( rand.size() ) {
		front = rand.front();
		rand.pop_front();
		randIndex++;
		return front;
	}

	int tmp(0), 
		max(100), // max elements to read
		skip = num2skip4rand; // lines to skip

	ifstream ifs( randomFile.c_str( ) );
	assert( ifs );

	/*  skips the number of lines already read */
	while( ifs >> tmp && 0 < max){
		if( skip <= 0  ){
			rand.push_back( tmp );
			num2skip4rand++;
			max--;
		}
		skip--;
	}

	// restart if eof is flagged
	if( ifs.eof( ) ){
		num2skip4rand = 0;
		ifs.clear();
	}

	return random();
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
		   stream >> contextSwitchDelay_Old;
		   break;
	   case AgingRatio: 
		   stream << value;
		   stream >> agingRatio;
		   break;
	   case Debug: 
		   tmp = lowerCase(value);
		   if(tmp == "false"){
#undef DEBUG
#define DEBUG false
		   }
		   break;
	}
}


void Scheduler::readResource(const string& filename){
	ifstream ifs(filename.c_str());
	if(!ifs) exit(1);

	string tmp, parameter, value, debugMsg;
	size_t pos;
	Parameter param;

	while(ifs >> tmp){
		pos = tmp.find("=");
		assert (pos >= 0);

		parameter = lowerCase( tmp.substr(0, pos) );
		param = getPara(parameter);
		if(param == Invalid) return;

		value = lowerCase( tmp.substr(pos+1, tmp.size()) );
		if(DEBUG) cout << "\tvalue: " << value << endl;
		setValue(param, value);

		if(DEBUG) 
			debugMsg += "Read in: " + tmp
					 +  "\nPosition of =: " + pos;/*
					 +  "\nparameter: " + parameter
					 +  "\nParameter: " + param
					 +	"\nvalue: " + value + "\n";*/
	}
}

double Scheduler::getAgingRatio(){
	return agingRatio;
}