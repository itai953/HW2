#ifndef FILEREADER_H
#define FILEREADER_H
#include <iostream>
#include <fstream>
#include "Graph.h"
using std::ifstream;
class FileReader {
public:
    void readFile(ifstream& f);
};
#endif