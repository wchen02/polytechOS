#include <iostream>
#include <fstream>
#include <string>
#include "scheduler.hpp"
#include "fcfs.hpp"
#include "srtn.hpp"
//#include "p_queue.hpp"
#include "process.hpp"
#include "functors.hpp"

#define RESOURCE_FILE "scheduling.txt"

//using namespace std;

//void menu(){
//	int command;
//	Scheduler* task;
//	string output("");
//	output += "Scheduler\n";
//	output += "\t1.First Come, First Served (FCFS)\n";
//	output += "\t2.Shortest Remaining Time Next with Aging (SRTN)\n";
//	output += "\t3.Quit this program\n";
//	output += "Please enter the number of Algorithm you want to use for the scheduler\n>>";
//	cout << output;
//
//	cin >> command; // this doesn't protect against invalid entries!
//	while(command < 1 || 3 < command){//this does
//		cout << "WRONG ENTRY! \n"+output<<endl;
//		cin >> command;
//	}
//	while(true){
//		switch(command){
//			case 1:
//				task = new FCFS(RESOURCE_FILE.c_str());
//				task->run();
//				break;
//			case 2:
//				//task = new SRTN(RESOURCE_FILE.c_str());
//				break;
//			case 3:
//				exit(0);
//				break;
//			default:
//				cout << "INVALID ENTRY TRY AGAIN\n";
//				break;
//		}
//		system("pause");
//		system("cls");
//		cout << output;
//		cin >> command; // this doesn't protect against invalid entries!
//	}
//
//}

int main(int argc, char * argv[]){
	//menu();
	Srtn *sn = new Srtn(RESOURCE_FILE);
	sn->run();

	system("pause");


}

//}