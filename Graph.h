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
    string getVtyprStr(uint a);
public:
    //constructors
    Graph() { } //empty constructor
    Graph(Graph&& other):graph(std::move(other.graph)){ } //move c'tor
    
    //move operator=
    Graph& operator=(const Graph&& rhs){ graph = std::move(rhs.graph);}
    void outbound(const string& src,uint sType);
    void uniExpress(const string& src,const string& dest,uint srcSType,uint destSType);
    void multiExpress(string src, string dest);
    bool containsVertex(const Vertex& v){return graph.find(v) != graph.end();}
    const Vertex& addVertex(string name,uint sType,uint vType);
    void addEdge(uint vType,const Vertex& _src,const Vertex& _dest, uint _weight);
    void removeEdge(uint vType,const Vertex& _src, const Vertex& _dest, uint _weight);
    void removeVertex(const string& name, uint sType, uint vType);
    ostream& print(ostream& out);
};

#endif 