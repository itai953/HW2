#include "Graph.h"

const Vertex& Graph::addVertex(string name,uint sType,uint vType){
    Vertex v(name,sType,vType); //construct Vertex
    GraphMap::iterator it = graph.find(v); //if already in graph return reference
    if(it != graph.end()){
        return it->first;
    }else{ //else insert to graph with empty EdgeSet
        graph[v] = EdgeSet();
    }
    for(const auto& item: graph){ //add transit Edges
        if(item.first.getName() == v.getName() && !(v == item.first)){
            addEdge(Vertex::TRANSIT,item.first,graph.find(v)->first,0);
            addEdge(Vertex::TRANSIT,graph.find(v)->first,item.first,0);
            break;
        }
    }
    return graph.find(v)->first; //return reference to newly constructed v in graph
}


void Graph::addEdge(uint vType,const Vertex& _src,const Vertex& _dest, uint _weight){
    Edge e(vType,_src,_dest,_weight);
    GraphMap::iterator it = graph.find(_src); //find iterator to _src
    EdgeSet& es = it->second; //es is _src's neighbor list
    EdgeSet::iterator sIter = std::find(es.begin(),es.end(),e); //sIter points to e if e in es
    if(sIter == es.end()){ //if not in es insert new edge
        es.insert(es.begin(),e);
    }else if(sIter->getWeight() > _weight) { //if new edge has lighter weight, swap
        es.erase(sIter);
        es.insert(es.begin(),e);
    }
}


void Graph::outbound(const string& src, uint sType,const string& outorin){
    if(!containsVertex(src)){
        cout << src <<" does not exist in the current network\n";
        return;
    } //check available routes for each type vehicle
    for(uint i =0; i<4; i++){
        Vertex v(src,sType,i);
        outbound(v,outorin);
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

void Graph::outbound(const Vertex& src,const string& outorin){
    string&& type = getVtyprStr(src.getVType());
    cout << type << ": ";
    //start BFS
    if(graph.find(src)!= graph.end()){
        std::map<string,bool> visited;
        queue<Vertex> q;
        q.push(src);
        bool first = true;
        visited[src.getName()] = true;
        while(!q.empty()){
            Vertex& u = q.front();
            if(!first){
                cout<< " " << u.getName();
            }
            first = false;
            for(auto & e: graph[u]){
                if(e.getVType() == Vertex::TRANSIT)
                    continue;
                if(!visited[e.getDst().getName()]){
                    q.push(e.getDst());
                    visited[e.getDst().getName()] = true;
                }
            }
            q.pop();
        }
        cout << "\n";
    }else{
        cout << "no "<< outorin << " travel\n" ;
    }
}


void Graph::uniExpress(const string& src,const string& dest,uint srcSType,uint destSType){
    /* check src and dest in graph if not output error message and return */
    if(!containsVertex(src)){
        cout << src << " does not exist in the current network\n";
        return;
    }if(!containsVertex(dest)){
        cout << dest <<" does not exist in the current network\n";
        return;
    }
    //Dijkstra for each type vehicle
    for(uint i =0; i<4; i++){
        Vertex v(src,srcSType,i);
        Vertex u(dest,destSType,i);
        uniExpress(v,u);
    }
}


void Graph::uniExpress(const Vertex& src,const Vertex& dest){
    using pair = std::pair<Vertex,uint>; //typedef for pair
    string&& type = getVtyprStr(src.getVType());
    cout << type << ":"; 
    //start Dijkstra
    if(graph.find(src)!= graph.end()){
        //comparator lambda
        auto comp = [](std::pair<Vertex,uint>& p1,std::pair<Vertex,uint>& p2){
            return p1.second > p2.second;
        };
        //init priority queue
        priority_queue<pair,
                vector<pair>,
                decltype(comp)> q(comp);
        /*init distance map, associates vertex with distance from src and boolean
        changed to true when vertex extracted from q (final distance value)*/
        std::map<Vertex,std::pair<uint,bool>> dist;
        for(const auto& item :graph){
            if(item.first.getVType() == src.getVType()){
                dist[item.first] = std::make_pair(INT_MAX,false); //init all distances of same type vehicle vertices to INT_MAX
            }
        }
        //push src to q with distance 0
        uint stop = Edge::getStopTime(src.getVType());
        q.push(std::make_pair(src,0));
        dist[src].first = 0;
        dist[src].second = false;
        while(!q.empty()){
            Vertex u = q.top().first;

            if(dist[u].second){//if true then u's lightest route already found, skip it
                q.pop();
                continue;
            }else{ //else set it to true
                dist[u].second = true;
            }
            //iterate over neighbors and search for relaxations
            for(auto &e : graph[u]){
                uint weight;
                weight = e.getWeight();
                if(e.getVType() == Vertex::TRANSIT){
                    continue;
                }
                if(dist[e.getDst()].first > dist[u].first + weight){
                    dist[e.getDst()].first = dist[u].first + weight; //relaxation
                    q.push(pair(e.getDst(),dist[e.getDst()].first)); //push to q again
                }
            }
            q.pop(); //finished with u, remove it from q;
        }
        if(!dist[dest].second){cout<<" route unavailable\n";} //if condition is false, dest never reached
        else{cout<< dist[dest].first - stop<<"\n";} //subtract stop added in destination
    }
    else{cout<<" route unavailable\n";}
}




void Graph::removeVertex(const Vertex& v){
    //it points to v if found
    auto it = graph.find(v);
    vector<Edge> rmEdges; //collect edges to remove that go into v
    //loop to find all edges going into v and removes then
    for(auto& item: graph){
        auto& es = item.second;
        for(auto& e : es){
            if(e.getDst() == v){
                rmEdges.push_back(e);
            }
        }
        for(auto& e: rmEdges){es.remove(e);}
        rmEdges.clear();
    }
    //if v found in graph, remove it and associated edges going out of v
    if(it != graph.end()){
        graph.erase(it);
    }
}


void Graph::removeEdge(uint vType,const Vertex& _src, const Vertex& _dest, uint _weight){
    Edge e(vType,_src,_dest,_weight);
    auto it = graph.find(_src);
    if(it != graph.end()){
        auto es = it->second;
        auto esIter = es.begin();
        while(esIter != es.end()){
            if(esIter->getDst() == _dest ){
                es.remove(*esIter);
                return;
            }
            else esIter++;
        }
    }
}


void Graph::multiExpress(const string& src,const string& dest){
    /* check if src and dest in graph, if not output error message and return */
    if(!containsVertex(src)){
        cout << src <<" does not exist in the current network\n";
        return;
    }if(!containsVertex(dest)){
        cout << dest <<" does not exist in the current network\n";
        return;
    }
    //add source and target Vertices run Bellman Ford from source to target
    const Vertex& srcVertex = addVertex("src",Vertex::TRANSIT, Vertex::TRANSIT);
    const Vertex& dstVertex = addVertex("trg",Vertex::TRANSIT, Vertex::TRANSIT);
    for(auto& ver: graph){
        //add edges from source Vertex to src Vertices of all types
        if(ver.first.getName() == src){
            addEdge(Vertex::TRANSIT,srcVertex,ver.first,0);
        }
        //add edges from all type vertices dest to target
        if(ver.first.getName() == dest){
            addEdge(Vertex::TRANSIT,ver.first,dstVertex,0);
        }
    }
    //if not found than error
    //start Bellman Ford
    multiExpress(srcVertex,dstVertex);
    //remove source and target from graph
    removeVertex(srcVertex);
    removeVertex(dstVertex);
}


void Graph::multiExpress(const Vertex& src, const Vertex& dest){
    map<Vertex,uint> distance; //map associates vertex with distance
    for(auto& item : graph){ //init all distances to INT_MAX
        distance[item.first] = INT_MAX;
    }
    distance[src] = 0; //src distance 0

    bool relaxation = true; //if iterated over all edges and no relaxation found, finished
    //|V|-1 iterations over all edges
    for(int i=0; i < graph.size() - 1 && relaxation; i++){
        relaxation = false;
        for(auto& item : graph){ //iterate over vertices
            if(distance[item.first] == INT_MAX) //if distance INT_MAX no relaxation possible to neighbors, skip
                continue;
            auto& es = item.second;
            for(auto &e: es){ //check all neighbors, if relaxation possible than update distance
                if(distance[e.getDst()] > distance[item.first] + e.getWeight()){
                    distance[e.getDst()] = distance[item.first] + e.getWeight();
                    relaxation = true;
                }
            }
        }
    }
    if(distance[dest] == INT_MAX){ //if true then dest not reachable from src
        cout << "route unavailable\n";
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


bool Graph::containsVertex(const string& v){
    auto it = std::find_if(graph.begin(),graph.end(),[v](std::pair<Vertex,EdgeSet>item){
        return item.first.getName() == v;
    });
    if(it != graph.end()){
        return true;
    }
    return false;
}

