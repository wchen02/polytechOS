#include <iostream>
#include <string>
#include <fstream>
#include "scheduler.h"
#include "fcfs.h"
//#include "srtn.h"

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

	while(true){
		switch(command){
			case 1:
				task = new FCFS(RESOURCE_FILE.c_str());
				break;
			case 2:
				//task = new SRTN(RESOURCE_FILE.c_str());
				break;
			case 3:
				exit(0);
				break;
			default:
				cout << "INVALID ENTRY TRY AGAIN\n";
				system("pause");
				system("cls");
				cout << output;
				cin >> command; // this doesn't protect against invalid entries!
				break;
		}
	}

}

int main(int argc, char * argv[]){
	menu();
}
