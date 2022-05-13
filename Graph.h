#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <unordered_set>
#include "Edge.h"
using std::ostream;
class Graph {
private:
    using SVPtr = std::shared_ptr<Vertex>;
    using EdgeSet = std::unordered_set<Edge>;
    using GraphMap = std::unordered_map<SVPtr, EdgeSet>;

public:
    void outbound(string src);
    void inbound(string dest);
    void uniExpress(string src, string dest);
    void multiExpress(string src, string dest);
    ostream& print(ostream& out);
};

#endif 