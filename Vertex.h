#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
#include <unordered_map>
#include <utility>
#include <sstream>

using std::unordered_map;
using std::string;

/* 
 * class Vertex represents a public transport station in Neverland
 * data members:
 * name: string - the name of the station
 * stationType: unsigned int - station type (central, intercity...)
 * vehicleType: unsigned int - what type vehicle goes thorugh this vertex
 */


typedef unsigned int uint;
class Vertex{

private:
    string name;
    uint stationType;
    char vehicleType;
public:
    enum {BUS=0, TRAM=1, SPRINTER=2, RAIL=3,INTERCITY=4, CENTRAL=5,STAD=6,TRANSIT=7};
    
    //constructors
    Vertex(const string& name,uint sType,uint vType):name(std::move(name)),stationType(sType),vehicleType(vType)
    { }
    //big 5 default imp sufficient
    Vertex(const Vertex& other) = default;
    Vertex(Vertex&& other) = default;
    Vertex& operator=(const Vertex& rhs) = default;
    Vertex& operator=(Vertex&& rhs) = default;
    ~Vertex() = default;
    
    //operator== imp compares all data members
    bool operator==(const Vertex& rhs) const {return this->stationType == rhs.stationType
                                                && this->name == rhs.name
                                                && this->vehicleType == rhs.vehicleType;}
    //getters
    uint getVType() const {return vehicleType;};
    uint getSType() const{return  stationType;};
    const string& getName()const {return name;};
    //operator< for use of std::map compares by name and vehicleType
    bool operator<(const Vertex& rhs) const{return name+vehicleType < rhs.name+rhs.vehicleType;}
};

#endif