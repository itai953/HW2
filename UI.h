#ifndef UI_H
#define UI_H
#include <iostream>
#include <sstream>
using std::string;
using std::cout;
using std::cin;
class UI{
private:
    //Temporary information fields
    string filepath;
    string srcNode;
    string destNode;
    //parser for a line get return the int associate with a command
    //and store the additional information in the upper fields
    int parseCommand(const string& cmd);
public:
    UI():filepath(),srcNode(),destNode() { }
    enum {LOAD=0, OUTBOUND=1, INBOUND=2, UNIEXPRESS=3, MULTIEXPRESS=4, PRINT=5,EXIT=6};

    //ask the user to enter a command and call parseCommand to parse it
    int getCommand();

    //after a command was parse by parseCommand
    //those functions return the relevant information which parsed as well
    string& getFilePath(){ return filepath; }
    string& getSrcNode() { return srcNode; }
    string& getDestNode() { return destNode; }
};
#endif