#ifndef FILEREADER_H
#define FILEREADER_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "Graph.h"

// typedef unsigned int uint;
using namespace  std;
class FileReader {


    enum {BUS=0, TRAM=1, SPRINTER=2, RAIL=3,INTERCITY=4, CENTRAL=5,STAD=6,TRANSIT=7};
    Graph& graph;
    uint getSType(string& name);

    uint getVtype(string& inputSt);
    void parseInputLine(string line, uint vType);

public:
    class FileReaderException{
            string error;
        public:
            FileReaderException(string error):error(error){}
            string& getError(){return error;}
    };
    FileReader(Graph& graph): graph(graph){}
    void readInputFile(string& input);
    void readOutputFile(string& outputFile);
    void readConfigFile(string& configFile);
};
#endif