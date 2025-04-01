#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#define edge pair<int, int>

class Graph {
private:
    vector<pair<int, edge>> G; // Graph
    vector<pair<int, edge>> T; // Minimum Spanning Tree (MST)
    int *parent;
    int V; // Number of vertices

public:
    Graph(int V);
    void add_edge(int u, int v, int w);
    int find(int i);
    void uni(int u, int v);
    void kruskal();
    void print();
};

Graph::Graph(int V) {
    parent = new int[V];
    this->V = V;
    for (int i = 0; i < V; i++)
        parent[i] = i;
}

void Graph::add_edge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}

int Graph::find(int i) {
    if (i == parent[i])
        return i;
    else
        return find(parent[i]);
}

void Graph::uni(int u, int v) {
    parent[u] = v;
}

void Graph::kruskal() {
    sort(G.begin(), G.end()); // Sort edges by weight
    for (int i = 0; i < G.size(); i++) {
        int u = find(G[i].second.first);
        int v = find(G[i].second.second);
        if (u != v) {
            T.push_back(G[i]);
            uni(u, v);
        }
    }
}

void Graph::print() {
    cout << "Edge : Weight" << endl;
    for (int i = 0; i < T.size(); i++) {
        cout << T[i].second.first << " - " << T[i].second.second << " : " << T[i].first << endl;
    }
}

// Prim's Algorithm
void primMST(int V, int cost[100][100]) {
    vector<bool> inMST(V, false);
    inMST[0] = true;
    int edge_count = 0, mincost = 0;

    while (edge_count < V - 1) {
        int min = INT_MAX, a = -1, b = -1;
        for (int i = 0; i < V; i++) {
            if (inMST[i]) {
                for (int j = 0; j < V; j++) {
                    if (!inMST[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }
        if (a != -1 && b != -1) {
            cout << "Edge " << edge_count++ << ":(" << a << ", " << b << ") cost: " << min << endl;
            mincost += min;
            inMST[b] = true;
        }
    }
    cout << "\nMinimum cost= " << mincost << endl;
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;
    
    Graph g(V);
    int cost[100][100];
    
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cost[i][j] = INT_MAX;
    
    cout << "Enter edges (u, v, w):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
        cost[u][v] = cost[v][u] = w;
    }
    
    int choice;
    cout << "Choose Algorithm:\n1. Kruskal's Algorithm\n2. Prim's Algorithm" << endl;
    cin >> choice;
    
    if (choice == 1) {
        g.kruskal();
        g.print();
    } else if (choice == 2) {
        primMST(V, cost);
    } else {
        cout << "Invalid choice!" << endl;
    }
    
    return 0;
}
