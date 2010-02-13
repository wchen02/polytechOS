#include <queue>
#include <fstream>
#include <sstream>
#include "Process.h"
#include "Scheduler.h"

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
	else if (param == "debug")
		return Debug;
	else return Invalid;
}

Scheduler::Scheduler(){}
//Process Scheduler::top(){}
//Process Scheduler::pop(){}
void Scheduler::push(Process newProcess){}
//int Scheduler::size(){}
//
	
void Scheduler::readProcess(string filename){
	ifstream ifs(filename);
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
		case Debug: 
			stream >> value;
			stream << tmp;
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
