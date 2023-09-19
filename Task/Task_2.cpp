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
      addEdge(adj, 0, 1, 7);addEdge(adj, 0, 2, 6);addEdge(adj, 0, 3, 2);addEdge(adj, 0, 4, 3);addEdge(adj, 0, 5, 4);addEdge(adj, 0, 6, 3);
      addEdge(adj, 1, 2, 6);addEdge(adj, 2, 3, 6);addEdge(adj, 3, 4, 2);addEdge(adj, 4, 5, 3);addEdge(adj, 5, 6, 1);addEdge(adj, 6, 1, 8);
      reset();
    }

    void addEdge(std::vector <std::vector<std::pair<int, int>>> &Graph, int u, int v, int w){
      Graph[u].push_back({v, w});
      Graph[v].push_back({u, w});
    }

    void reset(){
      added.clear();
      added.resize(V, false);
      mst.clear();
      mst.resize(V);
    }

    void initSet(std::vector<int> &parent){
      for(int i = 0; i < V; i++){
        parent[i] = i;
      }
    }

    int findSet(std::vector<int> &parent, int u){
      if(parent[u] == u) return u;
      return parent[u] = findSet(parent, parent[u]);
    }

    void unionSet(std::vector<int> &parent, int u, int v){
      int x = findSet(parent, u);
      int y = findSet(parent, v);
      parent[x] = y;
    }
    
    void unionSetByRank(std::vector<int> &parent, std::vector<int> &rank, int u, int v){
      int x = findSet(parent, u);
      int y = findSet(parent, v);
      if(rank[x] < rank[y]){
        parent[x] = y;
      } else {
        parent[y] = x;
        if(rank[x] == rank[y]){
          rank[x]++;
        }
      }
    }

    // Boruvka's algorithm
    void boruvka(){
      std::vector<int> parent(V), rank(V, 0);
      initSet(parent);

      std::vector<std::pair<int, std::pair<int, int>>> cheapest(3, {-1, {-1, -1}});
      int numTrees = V;
      int cost = 0;

      while(numTrees > 1){
        for(int i = 0; i < V; i++){
          cheapest[i] = {-1, {-1, -1}};
        }
        for(int i = 0; i < V; i++){
          for(auto j: adj[i]){
            int set1 = findSet(parent, i);
            int set2 = findSet(parent, j.first);
            if(set1 == set2) continue;
            if(cheapest[set1].first == -1 || cheapest[set1].first > j.second){
              cheapest[set1] = {j.second, {i, j.first}};
            }
            if(cheapest[set2].first == -1 || cheapest[set2].first > j.second){
              cheapest[set2] = {j.second, {i, j.first}};
            }
          }
        }
        for(int i = 0; i < V; i++){
          if(cheapest[i].first == -1) continue;
          int set1 = findSet(parent, cheapest[i].second.first);
          int set2 = findSet(parent, cheapest[i].second.second);
          if(set1 == set2) continue;
          cost += cheapest[i].first;
          unionSetByRank(parent, rank, set1, set2);
          numTrees--;
        }
      }
      
      printMST(cost);
    }

    // Prim's algorithm
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
  myGraph.boruvka();
  return 0;
}