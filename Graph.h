#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <set>
#include "Edge.h"
using std::ostream;

//todo check about == and comperators for edge and vertex
class Graph {
private:
//    using SVPtr = std::shared_ptr<Vertex>;
    using EdgeSet = std::set<Edge>;
    using GraphMap = std::map<Vertex, EdgeSet>;


    GraphMap graph;
    void outbound(const Vertex& src);
    void inbound(const Vertex& dest);

public:
    Graph() { }
    void outbound(string src,uint vType);
    void inbound(string dest,uint vType);
    void uniExpress(string src, string dest,uint vType);
    void multiExpress(string src, string dest);
    const Vertex& addVertex(string name,uint sType,uint vType);
    void addEdge(uint vType,const Vertex& _src,const Vertex& _dest, uint _weight);
    ostream& print(ostream& out);
};

#endif 