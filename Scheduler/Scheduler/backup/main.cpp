#include <iostream>
#include <string>
#include <fstream>
#include "scheduler.h"
#include "fcfs.h"
//#include "srtn.h"
//#include "p_queue.h"
#include "process.h"
#include "functors.hpp"


using namespace std;

const string RESOURCE_FILE("scheduling.txt");



void menu(){
	int command;
	Scheduler* task;
	string output("");
	output += "Scheduler\n";
	output += "\t1.First Come, First Served (FCFS)\n";
	output += "\t2.Shortest Remaining Time Next with Aging (SRTN)\n";
	output += "\t3.Quit this program\n";
	output += "Please enter the number of Algorithm you want to use for the scheduler\n>>";
	cout << output;

	cin >> command; // this doesn't protect against invalid entries!
	while(command < 1 || 3 < command){//this does
		cout << "WRONG ENTRY! \n"+output<<endl;
		cin >> command;
	}
	while(true){
		switch(command){
			case 1:
				task = new FCFS(RESOURCE_FILE.c_str());
				break;
			case 2:
//				task = new Srtn(RESOURCE_FILE.c_str());
				break;
			case 3:
				exit(0);
				break;
		}
	}

}

int main(int argc, char * argv[]){
	menu();
	

	system("pause");


}
