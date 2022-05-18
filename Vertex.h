#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
#include <unordered_map>
#include <utility>
#include <sstream>

using std::unordered_map;
using std::string;
typedef unsigned int uint;
class Vertex{

private:
//    static unordered_map<uint, uint> transitConfig;
    string name;
    string absName;
    uint stationType;
    char vehicleType;
public:
    enum {BUS=0, TRAM=1, SPRINTER=2, RAIL=3,INTERCITY=4, CENTRAL=5,STAD=6,TRANSIT=7};
    Vertex(string name,uint sType,uint vType):name(std::move(name)),stationType(sType),vehicleType(vType){
        absName = name+vehicleType;
    }
//    void updateConfig( uint stType, uint transitTime);
   bool operator==(const Vertex& rhs){return this->stationType == rhs.stationType
                                                && this->name == rhs.name
                                                && this->vehicleType == rhs.vehicleType;}
    uint getVType() const {return vehicleType;};
    uint getSType() const{return  stationType;};
    const string& getName()const {return name;};
    bool operator<(const Vertex& rhs) const;
};

#endif