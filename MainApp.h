#ifndef MAINAPP_H
#define MAINAPP_H
#include "UI.h"
#include "FileReader.h"

class MainApp {
private:
    ofstream output;
    UI userInterface;
    Graph g,gT;
    FileReader fr;    
public:
    MainApp():output(), userInterface(),g(),gT(),fr(g,gT) { }
    void init(int argc, vector<string>& argv);
    //use userInterface to parse users commands and calls relevant functions from g or gT
    void start();
    void updateConfigData();


    //big 5
    MainApp(const MainApp& other) = delete;
    MainApp(MainApp&& other) = delete;
    MainApp& operator=(const MainApp& rhs) = delete;
    MainApp& operator=(MainApp&& rhs) = delete;
    ~MainApp() = default;
};


#endif