/*
 Write a program to represent input graph using adjacency matrix. 
 * Implement Depth First and breadth first traversal algorithms. 
 * Check if graph is connected, if not find how many connected components it has.
*/
#include "bits/stdc++.h"
#define MAX 10
using namespace std;


void make_set(int v, vector<int> &parent){
    parent[v] = v;
}
int find_set(int v, vector<int> &parent){
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v], parent);
}
void union_set(int a, int b, vector<int> &parent){
    a = find_set(a,parent);
    b = find_set(b,parent);
    if (a != b)
        parent[b] = a;
}

class Graph{
    int n, connected;
    int** adjMatrix;
    int** weight;
    bool* visited;
    public :
        Graph (int size = 10){
            n = size;
            connected = 0;
            adjMatrix = new int *[n];
            weight = new int*[n];
            visited = new bool[n];
            for (int i = 0; i < n; i++){
                adjMatrix[i] = new int[n];
                weight[i] = new int[n];
                visited[i] = false;
                for (int j = 0; j < n; j++)
                    adjMatrix[i][j] = 0, weight[i][j] = INT_MAX;
            }
        }
        ~Graph () {
            for (int i = 0; i < n; i++)
                delete[] adjMatrix[i];
            delete[] adjMatrix;
        }

        void addEdge(int u, int v, int wt = 0);
        void removeEdge(int u, int v);
        void display();
        void dfs(int vertex);
        void clear_visited();
        void bfs(int vertex);
        bool is_connected();
        void prims();
        void kruskals();
};


void Graph :: addEdge(int u, int v, int wt){
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
    weight[u][v] = wt;
    weight[v][u] = wt;
}
void Graph :: removeEdge(int u, int v){
    adjMatrix[u][v] = 0;
    adjMatrix[v][u] = 0;
    weight[u][v] = INT_MAX;
    weight[v][u] = INT_MAX;
}
void Graph :: display(){
    cout << "----------------------------------------------------------\n";
    cout << "                    ADJACENCY MATRIX\n";
    cout << "    ";
    for (int i = 0; i < n; i++)
        cout << i << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << i << " : ";
        for (int j = 0; j < n; j++)
            cout << adjMatrix[i][j] << " ";
        cout << "\n";
    }
    cout << "                    Weight MATRIX\n";
    cout << "    ";
    for (int i = 0; i < n; i++)
        cout << i << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << i << " : ";
        for (int j = 0; j < n; j++){
            if (weight[i][j] == INT_MAX)
                {cout << -1 << " ";continue;} 
            cout << weight[i][j] << " ";
        }
        cout << "\n";
    }
}

void Graph :: clear_visited(){
    for (int i = 0; i < n; i++)
        visited[i] = false;
    return;
}

void Graph :: dfs(int vertex){
    visited[vertex] = true;
    connected++;
    cout << vertex << " ";
    for (int i = 0; i < n; i++)
        if (adjMatrix[vertex][i] == 1 and visited[i] == false)
            dfs(i);
    return ;
}

void Graph :: bfs(int vertex){
    queue <int> q;
    q.push(vertex);
    visited[vertex] = true;

    while (!q.empty()){
        int curr_vertex = q.front();
        q.pop();
        cout << curr_vertex << " ";
        for (int i = 0; i < n; i++)
            if (adjMatrix[curr_vertex][i] == 1 and visited[i] == false)
                visited[i] = true, q.push(i);
    }
    return;
}

bool Graph :: is_connected(){
    clear_visited();
    connected = 0;dfs(0);
    if (connected == n)
        return true;
    int count = 1;
    for (int i = 1; i < n; i++)
        if (visited[i] == false)
            dfs(i), count++;
    cout << "Total Connected components : " << count << "\n";
    return  false;
}




void Graph :: prims(){
    vector<int>  mst(n);

    int i = 0;
    priority_queue<pair<int, pair <int, int> > , vector<pair<int,pair <int, int> > >, greater<pair<int,pair <int, int> > > > pq;
    clear_visited();
    
    for (int i = 0; i < n; i++)
        if (adjMatrix[0][i] == 1)
            pq.push(make_pair(weight[0][i], make_pair(0,i)));
    mst[i] = 0;
    visited[i] = 1;
    i++;
    while (i < n){
        pair<int, pair <int, int> > temp = pq.top();
        pq.pop();
        
        if (visited[temp.second.second] != 1){
            cout << temp.first << " : "<< temp.second.first << "," << temp.second.second<< "\n";
            mst[i] = temp.second.second,visited[temp.second.second] = 1,i++;

        }
        for (int i = 0; i < n; i++)
            if (adjMatrix[temp.second.second][i] == 1 and visited[i] == false)
                pq.push(make_pair(weight[temp.second.second][i],make_pair(temp.second.second,i)));
    }

    for (int i = 0; i < n; i++)
        cout << mst[i] << " ";
    cout << "\n";
}

void Graph :: kruskals(){
    vector<int> parent(n);
    for (int i = 0; i < n; i++)
        parent[i] = i;
    vector<pair<int, pair<int,int> > > vertex;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            vertex.push_back(make_pair(weight[i][j], make_pair(i,j)));
    sort(vertex.begin(),vertex.end());
    int counter = 0, i = 0;
    while (counter < n-1){
        int u = vertex[i].second.first;
        int v = vertex[i].second.second;
        if (find_set(u, parent) != find_set(v, parent)){
            union_set(u,v,parent);
            cout << vertex[i].first << " : " << u << "," << v << "\n";
            counter++;
        }
        i++;
    }

}


int main(){

    int n; cout << "Enter the number of nodes : "; cin >> n;
    Graph graph(n);

    while (true){
        int choice;
        cout << "----------------------------------------------------------\n";
        cout << "                       MAIN MENU\n";
        cout << "\n     1. Add Edge\n     2. Delete Edge\n" << 
                "     3. Display Graph\n     4. Add all edges for a particular node\n     5. DFS\n     6. BFS\n     7. Check if the Graph is Connected\n     8. Enter the Edges\n     9. Prim's Algorithm\n     10. Kruskal's Algorithm\n     11. Exit\n";
        cout << "Enter your choice : "; cin >> choice;

        switch (choice){
            case 1 : {
                int u, v;
                cout << "     Enter first node : "; cin >> u;
                cout << "     Enter second node : "; cin >> v;
                graph.addEdge(u, v);
                break;
            }
            case 2 : {
                int u, v;
                cout << "     Enter first node : "; cin >> u;
                cout << "     Enter second node : "; cin >> v;
                graph.removeEdge(u, v);
                break;
            }
            case 3 : {
                graph.display();
                break;
            }
            case 4 : {
                int u;
                cout << "   Enter node : "; cin >> u;
                for (int i = 0; i < n; i++)
                    graph.addEdge(u, i);
                break;
            }
            case 5 : {
                int vertex; 
                cout << "Enter the root vertex : "; cin >> vertex;
                graph.clear_visited();
                graph.dfs(vertex);
                cout << "\n";
                break;
            }
            case 6 : {
                int vertex; 
                cout << "Enter the root vertex : "; cin >> vertex;
                graph.clear_visited();
                graph.bfs(vertex);
                cout << "\n";
                break;
            }
            case 7 : {
                if (graph.is_connected())
                    cout << "The graph is Connected!\n";
                else
                    cout << "The graph is NOT Connected!\n";
                break;
            }
            case 8 : {
                int k ;cout << "Number of Edges : ";cin >> k;
                while (k--){
                    int u,v,wt;
                    cin >> u >> v >> wt;
                    graph.addEdge(u,v,wt);
                }
                break;
            }
            case 9 : {
                graph.prims();
                break;
            }
            case 10 : {
                graph.kruskals();
                break;
            }
            case 11 : {
                return 0;
            }
        }
    }
    
}























