#include <iostream>
#include <sstream>
#include "MainApp.h"
using std::cout;
using std::cerr;
int main(int argc, char** argv){
    if(argc < 3){
        cerr << "ERROR: at least one input file required\n";
        exit(1); 
    }
    MainApp ma;
    vector<string> x(argv+1,argv+argc) ;
    ma.init(argc-1,x);
    ma.start();
    
    return 0;
}