// Programmer : Faa'iz Haikal Hilmi            Date: 20th September 2023
// NRP        : 5025221219                     Class: Teori Graf E
// Lecturer   : Victor Hariadi, S. Si, M. Kom
// Description: This program is used to find the minimum spanning tree of a graph using Kruskal's, Boruvka's and Prim's algorithm

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
    std::string alg;
    int total_edge;
    int question;

  public:
    Graph(int num){
      question = num;
      initGraph();
      runAlgorithms();
    }

    void initGraph(){
      if (question == 1) {
        V = 7;
        adj.resize(V);
        mst.resize(V);
        addEdge(adj, 0, 1, 7);addEdge(adj, 0, 2, 6);addEdge(adj, 0, 3, 2);addEdge(adj, 0, 4, 3);addEdge(adj, 0, 5, 4);addEdge(adj, 0, 6, 3);
        addEdge(adj, 1, 2, 6);addEdge(adj, 2, 3, 6);addEdge(adj, 3, 4, 2);addEdge(adj, 4, 5, 3);addEdge(adj, 5, 6, 1);addEdge(adj, 6, 1, 8);
      } else if (question == 3) {
        V = 10;
        adj.resize(V);
        mst.resize(V);
        addEdge(adj, 0, 1, 1);addEdge(adj, 0, 2, 7);addEdge(adj, 0, 3, 6);
        addEdge(adj, 1, 5, 2);addEdge(adj, 1, 8, 3);
        addEdge(adj, 2, 5, 11);addEdge(adj, 2, 4, 12);
        addEdge(adj, 3, 4, 8);addEdge(adj, 3, 9, 5);
        addEdge(adj, 4, 7, 13);
        addEdge(adj, 5, 6, 15);
        addEdge(adj, 6, 7, 14);addEdge(adj, 6, 8, 10);
        addEdge(adj, 7, 9, 9);
        addEdge(adj, 8, 9, 4);
        total_edge = 1+7+6+2+3+11+12+8+5+13+15+14+10+9+4;
      } else {
        throw std::invalid_argument("Invalid question number");
      }

      reset();
    }

    void runAlgorithms(){
      kruskal();
      boruvka();
      prim(0);
    }

    void addEdge(std::vector <std::vector<std::pair<int, int>>> &Graph, int u, int v, int w){
      Graph[u].push_back({v, w});
      Graph[v].push_back({u, w});
    }

    void reset(){
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
    void kruskal(){
      alg = "Kruskal";

      std::vector <std::pair<int, std::pair<int, int>>> edges;
      std::vector <int> parent(V);
      initSet(parent);
      int cost = 0;

      for(int i = 0; i < V; i++){
        for(auto j: adj[i]){
          int u = i;
          int v = j.first;
          int w = j.second;
          edges.push_back({w, {u, v}});
        }
      }
      std::sort(edges.begin(), edges.end());
      for(auto i: edges){
        int u = i.second.first;
        int v = i.second.second;
        int w = i.first;
        int x = findSet(parent, u);
        int y = findSet(parent, v);
        if(x == y) continue;
        unionSet(parent, u, v);
        addEdge(mst, u, v, w);
        cost += w;
      }
      printMST(cost, alg);
      reset();
    }

    void boruvka(){
      alg = "Boruvka";

      std::vector <int> parent(V);
      std::vector <int> rank(V, 0);
      initSet(parent);
      int cost = 0;

      while(true){
        std::vector <std::pair<int, std::pair<int, int>>> cheapest(V, {-1, {-1, -1}});
        for(int i = 0; i < V; i++){
          for(auto j: adj[i]){
            int u = i;
            int v = j.first;
            int w = j.second;
            int x = findSet(parent, u);
            int y = findSet(parent, v);
            if(x == y) continue;
            if(cheapest[x].first == -1 || cheapest[x].first > w){
              cheapest[x] = {w, {u, v}};
            }
            if(cheapest[y].first == -1 || cheapest[y].first > w){
              cheapest[y] = {w, {u, v}};
            }
          }
        }
        bool done = true;
        for(int i = 0; i < V; i++){
          if(cheapest[i].first == -1) continue;
          int u = cheapest[i].second.first;
          int v = cheapest[i].second.second;
          int w = cheapest[i].first;
          int x = findSet(parent, u);
          int y = findSet(parent, v);
          if(x == y) continue;
          unionSetByRank(parent, rank, u, v);
          addEdge(mst, u, v, w);
          cost += w;
          done = false;
        }
        if(done) break;
      }
      printMST(cost, alg);
      reset();
    }

    void prim(int source){
      alg = "Prim";

      std::vector <std::pair<int, std::pair<int, int>>> edges;
      std::vector <bool> added(V, false);

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

      printMST(cost, alg);
      reset();
    }

    void printMST(int cost, std::string &alg){
      std::cout << "---" << alg << "---" << "\n";
      std::cout << "Minimum spanning tree cost: " << cost << "\n";
      if (question == 3) {
        std::cout << "Need to remove " << total_edge - cost << " edge costs\n";
      }
      for(int i = 0; i < V; i++){
        std::cout << "Vertex " << oneIndexedVertex(i) << " is connected to: ";
        for(auto j: mst[i]){
          std::cout << oneIndexedVertex(j.first) << " ";
        }
        std::cout << "\n";
      }
    }

    int oneIndexedVertex(int vertex){
      return vertex + 1;
    }
};

int main(){
  int question;
  std::cout << "Which question? 1 or 3?\n";
  std::cin >> question;
  Graph myGraph(question);
  return 0;
}