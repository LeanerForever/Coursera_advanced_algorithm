#include <iostream>
#include <vector>
#include<queue>
using namespace std;
/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
};

FlowGraph read_data() {
    int vertex_count, edge_count;
    cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

int bfs(FlowGraph& graph,int from,int to){
    vector<bool> flag(to+1,false); flag[from] = true;
    queue<int> q; q.push(from);
    vector<int> augment_edges(to+1,-1);
    while(!q.empty()){
        int x = q.front();q.pop();
        if(x == to) break;
        for(auto idx : graph.get_ids(x)){
            FlowGraph::Edge edge = graph.get_edge(idx);
            int child = edge.to;
            if(!flag[child]){
                if(edge.capacity - edge.flow>0){
                    flag[child] = true;
                    q.push(child);
                    augment_edges[child] = idx; 
                }
            }
        }
    }

    if(augment_edges.back()==-1) return 0;

    int child = to;
    int mini_flow = INT32_MAX;
    while(augment_edges[child]!=-1){
        int idx = augment_edges[child];
        FlowGraph::Edge edge = graph.get_edge(idx);
        mini_flow = min(mini_flow,edge.capacity - edge.flow);
        child = edge.from;
    }
    child = to;
    while (augment_edges[child] != -1)
    {
        graph.add_flow(augment_edges[child],mini_flow);
        child = (graph.get_edge(augment_edges[child])).from;
    }
    return mini_flow;
}

int max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;
    /* your code goes here */
    int mini_flow = bfs(graph,from,to);
    while(mini_flow>0){
        flow += mini_flow;
        mini_flow = bfs(graph,from,to);
    }
    return flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
