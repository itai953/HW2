#include "Edge.h"
unordered_map<uint,uint> Edge::stopTimes;
unordered_map<uint,uint> Edge::transitTimes;

uint Edge::getWeight() const{
    if(vehicleType == Vertex::TRANSIT){
        if(src.getVType() == Vertex::TRANSIT) return 0;
        return getTransitTime(dest.getSType()) - getStopTime(src.getVType());
    }
    else {
        return weight + getStopTime(dest.getVType());
    }
}