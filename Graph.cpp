#include "Graph.h"
const Vertex& Graph::addVertex(string name,uint sType,uint vType){
    Vertex v(name,sType,vType);
    GraphMap::iterator it = graph.find(v);
    if(it != graph.end()){
        return it->first;
    }else{
        graph[v] = EdgeSet();
        return graph.find(v)->first;
    }
    
}


void Graph::addEdge(uint vType,const Vertex& _src,const Vertex& _dest, uint _weight){
    Edge e(vType,_src,_dest,_weight);
    //TODO insert check _src and _dest exist in map
    GraphMap::iterator it = graph.find(_src);
    EdgeSet& es = it->second;
    EdgeSet::iterator sIter = es.find(e);
    if(sIter == es.end()){
        es.insert(e);
    }else if(sIter->getWeight() > _weight) {
        es.erase(sIter);
        es.insert(e);
    }
}