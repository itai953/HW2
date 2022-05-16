#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <map>
#include <unordered_set>
#include "Edge.h"
using std::ostream;
class Graph {
private:
//    using SVPtr = std::shared_ptr<Vertex>;
    using EdgeSet = std::unordered_set<Edge>;
    using GraphMap = std::map<Vertex, EdgeSet>;


    GraphMap graph;
    void outbound(const Vertex& src);
    void inbound(const Vertex& dest);

public:
    void outbound(string src,uint vType);
    void inbound(string dest,uint vType);
    void uniExpress(string src, string dest,uint vType);
    void multiExpress(string src, string dest);
    Vertex& addVertex(string name,uint sType,uint vType);
    void addEdge(uint vType,Vertex& _src, Vertex& _dest, uint _weight);
    ostream& print(ostream& out);
};

#endif 