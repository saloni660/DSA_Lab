#include<bits/stdc++.h>
using namespace std;
# define edge pair<int,int>
class Graph{
private:
vector<pair<int,edge>> G;
vector<pair<int,edge>> T;
int v;
int cost[100][100];
int* parent;
public:
Graph(int v);
void add_edge(int u,int v,int w);
void kruskal();
void prim();
void uni(int u,int v);
int find(int i);
void print();
};

Graph::Graph(int v){
    // parent=new node(v);
    this->v=v;
    for(int i=0;i<v;i++){
        parent[i]=i;
    }
}

void Graph::add_edge(int u,int v,int w){
    G.push_back(make_pair(w,make_pair(u,v)));
}

void Graph:: uni(int u,int v){
    parent[u]=v;
}

int Graph::find(int i){
    if(i==parent[i]) return i;
    else return find(parent[i]);
}

void Graph::kruskal(){
    sort(G.begin(),G.end());
    for(int i=0;i<G.size();i++){
        int u=find(G[i].second.first);
        int v=find(G[i].second.second);
        if(u!=v){
            T.push_back(G[i]);
            uni(u,v);
        }
    }
    
}

void Graph::print(){
    cout<<"Edge-weight"<<endl;
    for(int i=0;i<T.size();i++){
        cout<<T[i].second.first<<":"<<T[i].second.second<<"-"<<T[i].first<<endl;
    }
}

void Graph::prim(){
    vector<bool> inmst(v,false);
    inmst[0]=true;
    int edge_count=0;
    int a=0;
    int b=0;
    int mincost=0;
    int min;
    while(edge_count<v-1){
        int min=INT_MAX;
        a=-1;
        b=-1;
        for(int i=0;i<v;i++){
            for(int j=0;j<v;j++){
                if(!inmst[j] && cost[i][j]<min){
                    min=cost[i][j];
                    a=i;
                    b=j;
                }
            }
        }
    }    
    if(a!=-1 && b!=-1){
        cout<<"Edge"<<edge_count++<<":("<<a<<","<<b<<")"<<cost;
    }
    inmst[b]=true;
    mincost+=min;
    cout<<"Minimum cost= "<<mincost<<endl;
}

int main(){
    int v;
    cout<<"Enter Number of vertices: "<<endl;
    cin>>v;
    int e;
    cout<<"Enter number of edges: "<<endl;
    cin>>e;
    Graph g(v);
    int cost[100][100];
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            cost[i][j]=INT_MAX;
        }
    }
    int u,ve,w;
    cout<<"Enter edges(u,v,w):"<<endl;
    for(int i=0;i<e;i++){
        cin>>u>>ve>>w;
        g.add_edge(u,ve,w);
        cost[u][v]=cost[v][u]=w;
    }
    
    cout<<"MENU\n1.Kruskal\n2.Prims"<<endl;
    cout<<"Enter your choice: ";
    int choice;
    cin>>choice;
    if(choice==1){
        g.add_edge(u,ve,w);
        g.kruskal();
    }
    else{
        cout<<"Invalid choice!!"<<endl;
    }
    
}


