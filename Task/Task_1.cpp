#include <iostream>
#include <vector>
#include <climits>
#include <queue>

class Graph {
  private:
    int V;
    std::vector <std::vector<std::pair<int, int>>> adj;
    std::vector <int> path;
    std::vector <int> dist;
    std::vector <int> prev;
  public:
    Graph(){
      V = 11;
      adj.resize(V);
      addEdge(0, 1, 2);addEdge(0, 2, 8);addEdge(0, 3, 1);
      addEdge(2, 1, 6);addEdge(2, 3, 7);addEdge(2, 4, 5);addEdge(2, 5, 1);addEdge(2, 6, 2);
      addEdge(4, 1, 1);addEdge(4, 7, 2);
      addEdge(5, 4, 3);addEdge(5, 6, 4);
      addEdge(6, 3, 9);addEdge(6, 9, 1);
      addEdge(8, 4, 9);addEdge(8, 5, 6);addEdge(8, 6, 3);addEdge(8, 7, 7);addEdge(8, 9, 1);
      addEdge(10, 7, 9);addEdge(10, 8, 2);addEdge(10, 9, 4);
      dist.resize(V, INT_MAX);
      prev.resize(V, -1);
    }
    void addEdge(int u, int v, int w){
      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
    }
    void dijkstra(int start, int target){
      dist[start] = 0;
      std::priority_queue <std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
      pq.push({0, start});
      while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        for(auto i: adj[u]){
          int v = i.first;
          int w = i.second;
          if(dist[v] > dist[u] + w){
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
          }
        }
      }
    }
};

int main(){
  Graph myGraph;
  myGraph.dijkstra(0, 10);
  return 0;
}