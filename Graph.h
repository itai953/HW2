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
using std::cerr;
using std::queue;
using std::vector;
using std::map;
using std::endl;

/* 
 * class Graph represents a public transport System
 * data members:
 * graph: a map associating a Vertex with a set of edges (adjacency list)
 */

class Graph {
private:
    using EdgeSet = std::set<Edge>;
    using GraphMap = std::map<Vertex, EdgeSet>;
    GraphMap graph;
    
    /* private functions for internal use*/
    void outbound(const Vertex& src); 
    void uniExpress(const Vertex& src,const Vertex& dest);
    void multiExpress(const Vertex& src, const Vertex& dest);
    string getVtyprStr(uint a);
public:
    //constructors
    Graph() { } //empty constructor
    Graph(Graph&& other):graph(std::move(other.graph)){ } //move c'tor
    
    //assignment op and copy c'tor default imps sufficient
    Graph(const Graph&) = default;
    Graph& operator=(const Graph&)=default;
    Graph& operator=(Graph&&)=default;
    
    //move assignment operator=
    Graph& operator=(const Graph&& rhs){ graph = std::move(rhs.graph); return *this;}
    
    /*graph queries*/
    //find and print to standard output all stations gettable from vertex with name src
    void outbound(const string& src,uint sType);
    //finds and prints to standard output the shortest duration of route from src to dest with no vehicle changes
    void uniExpress(const string& src,const string& dest,uint srcSType,uint destSType);
    //finds and prints to standard output the shortest duration of route from src to dest with vehicle changes
    void multiExpress(const string& src,const string& dest);
    //return true if graph contains vertex v
    bool containsVertex(const Vertex& v){return graph.find(v) != graph.end();}
    //add vertex to graph (constructs and adds to graph with no neighbors)
    const Vertex& addVertex(string name,uint sType,uint vType);
    //add edge to graph from _src to _dst
    void addEdge(uint vType,const Vertex& _src,const Vertex& _dest, uint _weight);
    //remove edge from _src to _dest from graph
    void removeEdge(uint vType,const Vertex& _src, const Vertex& _dest, uint _weight);
    //remove v and all associated edges from graph
    void removeVertex(const Vertex& v);
    //print graph to ostream out
    ostream& print(ostream& out);
};

#endif 