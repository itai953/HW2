#ifndef MAINAPP_H
#define MAINAPP_H
#include <iostream>
#include <vector>
#include "UI.h"
#include "FileReader.h"
using std::vector;
using std::string;

class MainApp {
private:
    ofstream output;
    UI userInterface;
    Graph g;
    FileReader fr;    
public:
    MainApp():output(), userInterface(),g(),fr(g) { }
    void init(int argc, vector<string>& argv);
    void start();

};


#endif