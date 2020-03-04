#include<iostream>
#include "GraphAdjListWeighted.h"
using namespace std;

int main()
{
    freopen("input.txt" , "r+" , stdin);
    freopen("output.txt" , "w+" , stdout);
    int n,m;
    cin>>n>>m;
    Graph g;
    g.setnVertices(n);
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        g.addEdge(u,v,w);
    }
    int source ,destination;
    cin>>source>>destination;
    cout<<"Bellman Ford Algorithm:\n";
    if(g.bellmenford(source))
    {
        cout<<g.getDist(destination)<<"\n";
        g.printPath(source , destination);
        cout<<"\n";
    }
    else cout<<"Negative Cycle Found\n";
    
    cout<<"Dijkstra Algorithm:\n";
    g.dijkstra(source);
    cout<<g.getDist(destination)<<"\n";
    g.printPath(source , destination);
    cout<<"\n";
    

}