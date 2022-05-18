#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <set>
#include <queue>
#include <vector>
#include "Edge.h"
using std::priority_queue;
using std::ostream;
using std::cout;
using std::queue;
using std::vector;

//todo check about == and comperators for edge and vertex
class Graph {
private:
//    using SVPtr = std::shared_ptr<Vertex>;
    using EdgeSet = std::set<Edge>;
    using GraphMap = std::map<Vertex, EdgeSet>;


    GraphMap graph;
    void outbound(const Vertex& src); 
    void uniExpress(const Vertex& src,const Vertex& dest);
public:
    Graph() { }
    void outbound(const string& src,uint sType);
    void uniExpress(const string& src,const string& dest,uint srcSType,uint destSType);
    void multiExpress(string src, string dest);
    const Vertex& addVertex(string name,uint sType,uint vType);
    void addEdge(uint vType,const Vertex& _src,const Vertex& _dest, uint _weight);
    ostream& print(ostream& out);
};

#endif 