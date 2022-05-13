#ifndef UI_H
#define UI_H
#include <iostream>
#include <sstream>
using std::string;
using std::cout;
using std::cin;
class UI{
private:
    string filepath;
    string srcNode;
    string destNode;
    int parseCommand(const string& cmd);
public:
    UI():filepath(),srcNode(),destNode() { }
    enum {LOAD=0, OUTBOUND=1, INBOUND=2, UNIEXPRESS=3, MULTIEXPRESS=4, PRINT=5,EXIT=6};
    int getCommand();
    string getFilePath(){ return filepath; }
    string getSrcNode() { return srcNode; }
    string getDestNode() { return destNode; }
};
#endif