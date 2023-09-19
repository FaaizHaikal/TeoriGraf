#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>

class Graph {
  private:
    int V;
    std::vector <std::vector<std::pair<int, int>>> adj;
    std::vector <int> path;
    std::vector <int> dist;
    std::vector <bool> visited;
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
      visited.resize(V, false);
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
        if(visited[u]) continue;
        for(auto i: adj[u]){
          int v = i.first;
          int w = i.second;
          if (visited[v]) continue;
          if(dist[v] > dist[u] + w){
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
            prev[v] = u;
          }
          visited[u] = true;
        }
      }
      printPath(start, target);
      for(int i=0;i<V;i++) std::cout << "Distance from " << oneIndexedVertex(start) << " to " << oneIndexedVertex(i) << " is " << dist[i] << std::endl;
    }

    void printPath(int start, int target){
      if(dist[target] == INT_MAX){
        std::cout << "No path found" << std::endl;
        return;
      }

      std::stack <int> s;
      int u = target;
      while(u != -1){
        s.push(u);
        u = prev[u];
      }
      std::cout << "Path: ";
      while(!s.empty()){
        std::cout << oneIndexedVertex(s.top()) << " ";
        s.pop();
      }
      std::cout << "\n";
    }

    int oneIndexedVertex(int vertex){
      return vertex + 1;
    }
};

int main(){
  Graph myGraph;
  myGraph.dijkstra(0, 10);
  return 0;
}