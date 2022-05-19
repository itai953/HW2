#include "Graph.h"

const Vertex& Graph::addVertex(string name,uint sType,uint vType){
    Vertex v(name,sType,vType);
    GraphMap::iterator it = graph.find(v);
    if(it != graph.end()){
        return it->first;
    }else{
        graph[v] = EdgeSet();
    }
    for(const auto& item: graph){
        if(item.first.getName() == v.getName() && !(v == item.first)){
            addEdge(Vertex::TRANSIT,item.first,graph.find(v)->first,0);
            addEdge(Vertex::TRANSIT,graph.find(v)->first,item.first,0);
            break;
        }
    }
    return graph.find(v)->first;
}


void Graph::addEdge(uint vType,const Vertex& _src,const Vertex& _dest, uint _weight){
    Edge e(vType,_src,_dest,_weight);
    //todo insert check _src and _dest exist in map
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


void Graph::outbound(const string& src, uint sType){
    for(uint i =0; i<4; i++){
        Vertex v(src,sType,i);
        outbound(v);
    }
}

string Graph::getVtyprStr(uint a){
    switch (a){
        case Vertex::BUS:
            return "bus";
            break;
        case Vertex::TRAM:
            return "tram";
            break;
        case Vertex::SPRINTER:
            return "sprinter";
            break;
        case Vertex::RAIL:
            return "rail";
            break;
        default:
            return "-1";
    }
}

void Graph::outbound(const Vertex& src){
    string&& type = getVtyprStr(src.getVType());
    cout << type << ": ";
    if(graph.find(src)!= graph.end()){
        std::map<string,bool> visited;
        queue<Vertex> q;
        q.push(src);
        bool first = true;
        while(!q.empty()){
            Vertex& u = q.front();
            if(!first){
                cout<< " " << u.getName();
            }
            first = false;
            visited[u.getName()] = true;
            for(auto & e: graph[u]){
                if(e.getVType() == Vertex::TRANSIT)
                    continue;
                if(!visited[e.getDst().getName()]){
                    q.push(e.getDst());
                }
            }
            q.pop();
        }
    }else{
        cout << "no available routes\n";
    }
}


void Graph::uniExpress(const string& src,const string& dest,uint srcSType,uint destSType){
    for(uint i =0; i<4; i++){
        Vertex v(src,srcSType,i);
        Vertex u(dest,destSType,i);
        uniExpress(v,u);
    }
}


void Graph::uniExpress(const Vertex& src,const Vertex& dest){
    using pair = std::pair<Vertex,uint>;
    string&& type = getVtyprStr(src.getVType());
    cout <<"\n" << type << ":";
    if(graph.find(src)!= graph.end()){
        auto comp = [](std::pair<Vertex,uint>& p1,std::pair<Vertex,uint>& p2){
            return p1.second > p2.second;
        };
        priority_queue<pair,
                vector<pair>,
                decltype(comp)> q(comp);
        std::map<Vertex,std::pair<uint,bool>> dist;
        for(const auto& item :graph){
            if(item.first.getVType() == src.getVType()){
                dist[item.first] = std::make_pair(INT_MAX,false);
            }
        }
        uint stop = Edge::getStopTime(src.getVType());
        q.push(std::make_pair(src,0));
        dist[src].first = 0;
        dist[src].second = false;
        while(!q.empty()){
            Vertex u = q.top().first;

            if(dist[u].second){
                q.pop();
                continue;
            }else{
                dist[u].second = true;
            }
            for(auto &e : graph[u]){
                uint weight;
                weight = e.getWeight();
                if(e.getVType() == Vertex::TRANSIT){
                    continue;
                }
                if(dist[e.getDst()].first > dist[u].first + weight){
                    dist[e.getDst()].first = dist[u].first + weight;
                    q.push(pair(e.getDst(),dist[e.getDst()].first));
                }
            }
            q.pop();
        }
        if(!dist[dest].second){cout<<" route unavailable\n";}
        else{cout<< dist[dest].first - stop<<"\n";}
    }
    else{cout<<" route unavailable\n";}
}




void Graph::removeVertex(const Vertex& v){
    auto it = graph.find(v);
    if(it != graph.end()){
        graph.erase(it);
    }
    for(auto& item: graph){
        auto& es = item.second;
        for(auto& e : es){
            if(e.getDst() == v){
                es.erase(e);
            }
        }
    }
}


void Graph::removeEdge(uint vType,const Vertex& _src, const Vertex& _dest, uint _weight){
    auto it = graph.find(_src);
    if(it != graph.end()){
        auto es = it->second;
        for(const auto& e: es){
            if(e.getDst() == _dest){
                es.erase(e);
                return;
            }
        }
    }
}


void Graph::multiExpress(const string& src,const string& dest){
    const Vertex& srcVertex = addVertex("src",Vertex::TRANSIT, Vertex::TRANSIT);
    const Vertex& dstVertex = addVertex("trg",Vertex::TRANSIT, Vertex::TRANSIT);
    bool found_src = false;
    bool found_dst = false;
    for(auto& ver: graph){
        if(ver.first.getName() == src){
            addEdge(Vertex::TRANSIT,srcVertex,ver.first,0);
            found_src = true;
        }
        if(ver.first.getName() == dest){
            addEdge(Vertex::TRANSIT,ver.first,dstVertex,0);
            found_dst = true;
        }
    }
    if(!found_src || !found_dst){
        cerr << "\nERROR: unrecognized source or destination name\n";
        return;
    }
    multiExpress(srcVertex,dstVertex);
    removeVertex(srcVertex);
    removeVertex(dstVertex);
}


void Graph::multiExpress(const Vertex& src, const Vertex& dest){
    map<Vertex,uint> distance;
    for(auto& item : graph){
        distance[item.first] = INT_MAX;
    }
    distance[src] = 0;

    bool relaxation = true;
    for(int i=0; i < graph.size() - 1 && relaxation; i++){
        relaxation = false;
        for(auto& item : graph){
            if(distance[item.first] == INT_MAX)
                continue;
            auto& es = item.second;
            for(auto &e: es){
                if(distance[e.getDst()] > distance[item.first] + e.getWeight()){
                    distance[e.getDst()] = distance[item.first] + e.getWeight();
                    relaxation = true;
                }
            }
        }
    }
    if(distance[dest] == INT_MAX){
        cout << "no available routes\n";
    }else {
        cout << "shortest route duration: " << distance[dest] << "\n";
    }
}

ostream &Graph::print(ostream &out) {
    out << "Neverland Public Transpot Network\n";
    out << "\n-------------------Bus-------------------------\n";
    string n;
    for (auto &item: graph) {
        if (item.first.getVType() == Vertex::BUS) {
            out <<n<< "station name : "<< item.first.getName() << "\nLinked stations >> ";
            n="\n\n";
            for (auto &edge: item.second) {
                if (edge.getVType()!=Vertex::TRANSIT)
                out << edge.getDst().getName() << " ";
            }
        }
    }
    out << "\n\n-------------------Rail-------------------------\n";
    n="";
    for (auto &item: graph) {
        if (item.first.getVType() == Vertex::RAIL) {
            out <<n<< "station name : "<< item.first.getName()<< "\nLinked stations >> ";
            n="\n\n";
            for (auto &edge: item.second) {
                if (edge.getVType()!=Vertex::TRANSIT)
                    out << edge.getDst().getName() << " ";
            }
        }
    }
    out << "\n\n-------------------Tram-------------------------\n";
    n="";
    for (auto &item: graph) {
        if (item.first.getVType() == Vertex::TRAM) {
            out <<n<< "station name : "<< item.first.getName() << "\nLinked stations >> ";
            n="\n\n";
            for (auto &edge: item.second) {
                if (edge.getVType()!=Vertex::TRANSIT)
                    out << edge.getDst().getName() << " ";
            }
        }
    }
    out << "\n-------------------Sprinter-------------------------\n";
    n="";
    for (auto &item: graph) {
        if (item.first.getVType() == Vertex::SPRINTER) {
            out <<n<< "station name : "<< item.first.getName()<< "\nLinked stations >> ";
            n="\n\n";
            for (auto &edge: item.second) {
                if (edge.getVType()!=Vertex::TRANSIT)
                    out << edge.getDst().getName() << " ";
            }
        }
    }
    return out;
}


