#ifndef FILEREADER_H
#define FILEREADER_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "Graph.h"

using namespace  std;
/* 
 * class FileReader a functional class to read files and parse into graph
 * used by class MainApp
 * data members:
 * graph: a refrence to the MainApp graph that can be updated from FileReader
 * gT: the Transposed Graph for inbound querie
 */
class FileReader {
    enum {BUS=0, TRAM=1, SPRINTER=2, RAIL=3,INTERCITY=4, CENTRAL=5,STAD=6,TRANSIT=7};
    Graph& graph;
    Graph& gT;
    /* private functions for internal use*/
    uint getVtype(string& inputSt);
    void parseInputLine(string line, uint vType);

public:
    //exception class
    class FileReaderException{
            string _error;
        public:
            FileReaderException(const string& error):_error(error){}
            string& getError(){return _error;}
    };
    //get station type from the name of a station
    uint getSType(string& name);
    //constructor
    FileReader(Graph& graph,Graph &_gT): graph(graph),gT(_gT){}
    //big 5 default imps
    FileReader(const FileReader&) = default;
    FileReader(FileReader&&)=default;
    FileReader& operator=(const FileReader&)=default;
    FileReader& operator=(FileReader&&)=default;
    
    //reads input file at path input, throws FileReaderException in case of
    //invalid input or unable to open file
    void readInputFile(string& input);
    //read a config file at path configFile, throws FileReaderException in case of
    //invalid input or unable to open file
    void readConfigFile(string& configFile);
};
#endif