#ifndef EDGE_H
#define EDGE_H
#include <memory>
#include "Vertex.h"
using std::ostream;
/* 
 * class Edge represents a direct route between two vertices in transport system
 * static data members:
 * transitTimes: a map associating station type with its transit time
 * stopTimes: a map associating vehicle type with its stop time
 * static functions in functions can acces these data members
 * 
 * non-static data members:
 * vehicleType: represents the vehicle going between the two vertices - in general must match the src and dest node
 * unless its a TRANSIT edge
 * src: the Source Node
 * dest: the dest Node
 * weight: length of drive in minutes
 */
class Edge{
private:
    //static data members
    static unordered_map<uint,uint> transitTimes;
    static unordered_map<uint,uint> stopTimes;
    
    //non-static data members
    uint vehicleType;
    const Vertex& src;
    const Vertex& dest;
    uint weight;
    
public:
    //constructor
    Edge(uint vType, const Vertex& _src, const Vertex& _dest, uint _weight):vehicleType(vType),
                                                                            src(_src),dest(_dest),weight(_weight){ }
    
    //big 5 default imps sfficient for class
    Edge(const Edge&) = default;
    Edge(Edge&&) = default;
    Edge& operator=(const Edge&)= default;
    Edge& operator=(Edge&&) = default;
    ~Edge() = default;
    
    //static member getters
    static uint getStopTime(uint vType){return stopTimes[vType];}
    static uint getTransitTime(uint sType){return transitTimes[sType];}
    //static member setters
    static void updateStopTimes(uint vType, uint stopTime){stopTimes[vType] = stopTime;}
    static void updateTransitTimes(uint sType, uint transitTime){transitTimes[sType] = transitTime;}
    
    //getters
    uint getVType() const{return vehicleType;}
    uint getWeight() const;
    const Vertex& getSrc() const{return src;}
    const Vertex& getDst() const{return dest;}
    
    //operator< for use of std::set
    bool operator<(const Edge& rhs) const {
        return dest < rhs.dest;
    }
    
    //weight setter
    void setWeight(uint _weight){weight = _weight;}
    //insertor operator for ostream prints the destination name
};

#endif