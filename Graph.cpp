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


void Graph::outbound(const string& src, uint sType){
    for(uint i =0; i<4; i++){
        Vertex v(src,sType,i);
        outbound(v);
    }
} 

string getVtyprStr(uint a){
    switch (a){
        case 0:
            return "bus";
            break;
        case 1:
            return "tram";
            break;
        case 2:
            return "sprinter";
            break;
        case 3:
            return "rail";
            break;
        default:
            return "-1";
    }
}

void Graph::outbound(const Vertex& src){
    string&& type = getVtyprStr(src.getVType());
    cout <<"\n" << type << ":"; 
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
                if(dist[e.getDst()].first > dist[u].first + weight + stop){
                    dist[e.getDst()].first = dist[u].first + weight + stop;
                    q.push(pair(e.getDst(),dist[e.getDst()].first));
                }
            }
            q.pop();
        }
        if(!dist[dest].second){
            cout<<" route unavailable\n";
        }
        else{
            cout<< dist[dest].first - stop<<"\n";
        }
    }
    else{cout<<" route unavailable\n";}
}