#include "Vertex.h"


//unordered_map<uint,uint> Vertex::transitConfig;

bool Vertex::operator<(const Vertex& rhs) const {
    return name+vehicleType < rhs.name+rhs.vehicleType;
}
