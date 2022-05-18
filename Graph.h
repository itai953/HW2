#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <set>
#include <queue>
#include "Edge.h"
using std::ostream;
using std::cout;
using std::queue;

//todo check about == and comperators for edge and vertex
class Graph {
private:
//    using SVPtr = std::shared_ptr<Vertex>;
    using EdgeSet = std::set<Edge>;
    using GraphMap = std::map<Vertex, EdgeSet>;


    GraphMap graph;
    void outbound(const Vertex& src);

public:
    Graph() { }
    void outbound(const string& src,uint sType);
    void uniExpress(string src, string dest,uint vType);
    void multiExpress(string src, string dest);
    const Vertex& addVertex(string name,uint sType,uint vType);
    void addEdge(uint vType,const Vertex& _src,const Vertex& _dest, uint _weight);
    ostream& print(ostream& out);
};

#endif 