#include "MainApp.h"
using std::cout;
using std::cerr;
int main(int argc, char** argv){
    if(argc < 3){
        cerr << "ERROR: at least one input file required\n";
        exit(1);
    }
    MainApp ma;
    vector<string> x(argv+1,argv+argc);
    try{
        ma.init(argc-1,x);
        ma.start();
    }catch (std::exception &e){
        cerr << " ERROR in main function: exception was caught: \n";
        cerr << e.what();
    }catch(...){
        cerr << "ERROR an unknown exception was thrown. exiting program.\n";
        exit(1);
    }
    return 0;
}