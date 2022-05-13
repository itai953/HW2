#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
#include <unordered_map>
using std::unordered_map;
using std::string;
typedef unsigned int  uint;
class Vertex{
private:
    static unordered_map<uint, uint> transitConfig;
    string name;
    uint stationType;
    uint vehicleType;
public:
    enum {BUS=0, TRAM=1, SPRINTER=2, RAIL=3,INTERCITY=4, CENTRAL=5,STAD=6,TRANSIT=7};
    Vertex(string name,uint vType);
    void updateConfig( uint stType, uint transitTime);
    bool operator==(const Vertex& rhs);
};

#endif