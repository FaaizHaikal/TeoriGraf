#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>
#include <algorithm>

class Graph {
  private:
    int V;
    std::vector <std::vector<std::pair<int, int>>> adj;
    std::vector <std::vector<std::pair<int, int>>> mst;
    std::vector <bool> added;
  public:
    Graph(){
      V = 7;
      adj.resize(V);
      mst.resize(V);
      addEdge(0, 1, 7);addEdge(0, 2, 6);addEdge(0, 3, 2);addEdge(0, 4, 3);addEdge(0, 5, 4);addEdge(0, 6, 3);
      addEdge(1, 2, 6);addEdge(2, 3, 6);addEdge(3, 4, 2);addEdge(4, 5, 3);addEdge(5, 6, 1);addEdge(6, 1, 8);
      reset();
    }

    void addEdge(int u, int v, int w){
      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
    }

    void reset(){
      added.clear();
      added.resize(V, false);
    }

    void prim(int source){
      std::vector <std::pair<int, std::pair<int, int>>> edges;
      for(auto u : adj[source]){
        edges.push_back({u.second, {source, u.first}});
      }
      int cost = 0;
      added[source] = true;
      std::sort(edges.begin(), edges.end());
      while(!edges.empty()){
        auto edge = edges.front();
        edges.erase(edges.begin());
        int u = edge.second.first;
        int v = edge.second.second;
        int w = edge.first;
        if(added[u] && added[v]) continue;
        mst[u].push_back({v, w});
        mst[v].push_back({u, w});
        added[u] = true;
        added[v] = true;
        cost += w;
        for(auto i: adj[v]){
          if(!added[i.first]){
            edges.push_back({i.second, {v, i.first}});
          }
        }
        std::sort(edges.begin(), edges.end());
      }

      printMST(cost);
      reset();
    }

    void printMST(int cost){
      std::cout << "Minimum spanning tree cost: " << cost << std::endl;
      for(int i = 0; i < V; i++){
        std::cout << "Vertex " << oneIndexedVertex(i) << " is connected to: ";
        for(auto j: mst[i]){
          std::cout << oneIndexedVertex(j.first) << " ";
        }
        std::cout << std::endl;
      }
    }

    int oneIndexedVertex(int vertex){
      return vertex + 1;
    }
};

int main(){
  Graph myGraph;
  myGraph.prim(0);
  return 0;
}