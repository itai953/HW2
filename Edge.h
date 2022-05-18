#ifndef EDGE_H
#define EDGE_H
#include <memory>
#include "Vertex.h"
class Edge{
private:
    static unordered_map<uint,uint> transitTimes;
    static unordered_map<uint,uint> stopTimes;
    uint vehicleType;
    const Vertex& src;
    const Vertex& dest;
    uint weight;

public:
    Edge(uint vType, const Vertex& _src, const Vertex& _dest, uint _weight):vehicleType(vType),
                                                                            src(_src),dest(_dest),weight(_weight){ }
    uint getVType() const{return vehicleType;}
    static uint getStopTime(uint vType){return stopTimes[vType];}
    static uint getTransitTime(uint sType){return transitTimes[sType];}
    uint getWeight() const{return weight;}
    const Vertex& getSrc() const{return src;}
    const Vertex& getDst() const{return dest;}
    bool operator<(const Edge& rhs) const {
        return dest < rhs.dest;
    }
    static void updateStopTimes(uint vType, uint stopTime){stopTimes[vType] = stopTime;}
    static void updateTransitTimes(uint sType, uint transitTime){transitTimes[sType] = transitTime;}
    void setWeight(uint _weight){weight = _weight;}

};

#endif