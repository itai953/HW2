#ifndef EDGE_H
#define EDGE_H
#include <memory>
#include "Vertex.h"
class Edge{
private:
    using WVPtr = std::weak_ptr<Vertex>;
    static unordered_map<uint,uint> stopTimes;
    uint vehicleType;
    WVPtr src;
    WVPtr dest;
    uint weight;
public:
    Edge(uint vType,WVPtr _src, WVPtr _dest, uint _weight);
    void updateStopTimes(uint vType, uint stopTime);
    void setWeight(uint w);
};

#endif