#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

#define INF INT_MAX

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> dijkstra(int src) {
        vector<int> dist(V, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        pq.push({0, src});
        dist[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            for (auto neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
};

int main() {
    int V, E;
    cout << "Enter number of cities (vertices): ";
    cin >> V;
    cout << "Enter number of routes (edges): ";
    cin >> E;

    Graph g(V);
    cout << "Enter routes (city1 city2 distance):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int S, F;
    cout << "Enter starting city (S) and destination city (F): ";
    cin >> S >> F;

    vector<int> shortestDist = g.dijkstra(S);
    int shortestPath = shortestDist[F];

    cout << "Shortest distance from " << S << " to " << F << " is: " << shortestPath << endl;
    cout << "Now selecting an alternative route that is longer than the minimal distance..." << endl;
    
    int alternatePath = INF;
    for (int i = 0; i < V; i++) {
        for (auto neighbor : g.adj[i]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            if (shortestDist[i] + weight > shortestPath && shortestDist[i] + weight < alternatePath)
                alternatePath = shortestDist[i] + weight;
        }
    }
    
    if (alternatePath == INF)
        cout << "No alternate route found meeting the criteria." << endl;
    else
        cout << "Alternative route found with distance: " << alternatePath << endl;

    return 0;
}
