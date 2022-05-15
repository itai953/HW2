#include "FileReader.h"

//void FileReader::readConfigFile(string &configFile) {
//
//    }

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
    return -1;
}





void FileReader::parseInputLine(string line, uint vType) {
    char tab;
    string src;
    string dest;
    uint weight;
    stringstream ss(line);
    ss>>src;
    ss>>tab;
    ss>>dest;
    ss>>tab;
    ss>>weight;
    if (weight<0){
        throw FileReaderException("negative weight in inputFile"); }
    Vertex Vsrc = graph.addVertex(src, getSType(src),vType);
    Vertex Vdest = graph.addVertex(dest, getSType(dest),vType);
    graph.addEdge(vType,Vsrc, Vdest, weight);
}



void FileReader::readInputFile(string &inputSt) {
    ifstream inputFile(inputSt);
    if (!inputFile){
        throw FileReaderException("input file couldn't open"); }
    uint vType = getSType(inputSt);

    string line;
    while(getline(inputFile, line)){
        parseInputLine(line, vType);
    }
}

//void FileReader::readOutputFile(string &outputSt) {
//    ofstream outputFile(outputSt);
//    if (!outputFile){
//
//    }
//
//}

void FileReader::readConfigFile(string &configSt) {
    ifstream configFile(configSt);
    if (!configFile){
        if (!configFile){
            throw FileReaderException("config file couldn't open"); }
    }
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
        if (type!=-1){
            Edge::updateStopTimes(type,weight);
        }
        else{
            type = getSType(token);
            Edge::updateTransitTimes(type,weight);
        }
    }
}

