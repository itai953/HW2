#ifndef EDGE_H
#define EDGE_H
#include <memory>
#include "Vertex.h"
class Edge{
private:
//    using WVPtr = std::weak_ptr<Vertex>;
    static unordered_map<uint,uint> stopTimes;
    uint vehicleType;
    Vertex& src;
    Vertex& dest;
    uint weight;
public:
    uint getVType() const{return vehicleType;}
    uint getStopTime(){return stopTimes[vehicleType];}
    uint getWeight() const{return weight;}
    Vertex& getSrc() const{return src;}
    Vertex& getDst() const{return dest;}




    Edge(uint vType,Vertex& _src, Vertex& _dest, uint _weight):vehicleType(vType),src(_src),dest(_dest),weight(_weight){}
    void updateStopTimes(uint vType, uint stopTime){stopTimes[vType] = stopTime;}
    void setWeight(uint _weight){weight = _weight;}

};

#endif