#ifndef FCFS_H
#define FCFS_H
#include <vector>
#include "../base/process.h"

class Fcfs{
public:
  Fcfs(const vector<Process*> p): processes(p){}
  Fcfs(){
    processes = new vector<Process*>();
  }
  
  void readprocessFile(string file){
    ifstream ifl(file);
    while(!ifl){
      cerr << "Could Not open the file: " << file << "\n enter file path name: ";
      cin >> file;
      ifl.clear(); // clears the fail state
      ifl.open(file);
    }
    int tmp[4]={0};
    while( ifl >> tmp[0] >> tmp[1] >> tmp[2] >> tmp [3]){
      processes[i]->setProcess( tmp[0], tmp[1], tmp[2], tmp [3] );
    }
    
  }
  
  
  

private:
  vector<Process*> processes;
  
};


#endif
