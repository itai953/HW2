#include "FileReader.h"

uint FileReader::getSType(string &name) {
    if(name.rfind("IC",0) ==0 || name.rfind("intercity",0) ==0){return INTERCITY;}
    if(name.rfind("CS",0) ==0 || name.rfind("central",0) ==0){return CENTRAL;}
    return STAD;
}



uint FileReader::getVtype(string& inputSt) {
    if(inputSt.rfind("bus",0) ==0){ return BUS;}
    if(inputSt.rfind("tram",0) ==0){ return TRAM;}
    if(inputSt.rfind("sprinter",0) ==0){ return SPRINTER;}
    if(inputSt.rfind("rail",0) ==0){ return RAIL;}
    return 5;
}





void FileReader::parseInputLine(string line, uint vType) {
    string src;
    string dest;
    uint weight;
    stringstream ss(line);
    ss>>src;
    ss>>dest;
    ss>>weight;
    if (weight<0){
        throw FileReaderException("negative weight in input file"); }
    const Vertex& Vsrc = graph.addVertex(src, getSType(src),vType);
    const Vertex& Vdest = graph.addVertex(dest, getSType(dest),vType);
    graph.addEdge(vType,Vsrc, Vdest, weight);


   //add to the transpose graph
    const Vertex& Vsrc1 = gT.addVertex(src, getSType(src),vType);
    const Vertex& Vdest1 = gT.addVertex(dest, getSType(dest),vType);
    gT.addEdge(vType,Vdest1,Vsrc1, weight);   
}



void FileReader::readInputFile(string &inputSt) {
    ifstream inputFile(inputSt);
    if (!inputFile){
        throw FileReaderException("ERROR opening the specified file\n");
    }
    uint vType = getVtype(inputSt);

    string line;
    while(getline(inputFile, line)){
        parseInputLine(line, vType);
    }
}


void FileReader::readConfigFile(string &configSt) {
    ifstream configFile(configSt);
    if (!configFile){
            throw FileReaderException("ERROR opening the specified file\n"); }

    uint type;
    string token;
    string line;
    uint weight =0;
    while(getline(configFile, line)){
        stringstream ss(line);
        ss>>token;
        type = getVtype(token);
        ss>>weight;
        if (weight<0){
            throw FileReaderException("negative weight in config file"); }
        if (type!=5){
            Edge::updateStopTimes(type,weight);
        }
        else{
            type = getSType(token);
            Edge::updateTransitTimes(type,weight);
        }
    }
}

