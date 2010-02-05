#include<iostream>
#include "process.h"
using namespace std;

int main( int argc, char *argv[] ){
  Process *p;
  p = new Process( 1 , 12, 123 , 1234); // testing the constructor
  cout << "Hello World" << endl;
}
