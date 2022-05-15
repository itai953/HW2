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
    UI userInterface;    
public:
    MainApp(): userInterface() { }
    void init(int argc, vector<string>&& argv);
    void start();

};


#endif