#include<bits/stdc++.h>

using namespace std;


#define DBG(x) cout<< #x <<"  -->>  "<<(x)<<"\n"
#include "Edmonds-Karp.h"

int main()
{
    freopen("input1.txt" , "r+" , stdin);
    freopen("output1.txt" , "w+" , stdout);


    int n,m;
    cin>>n>>m;

    FlowGraph g(n);

    while(m--)
    {
        int u,v;
        FlowType c;
        cin>>u>>v>>c;
        g.AddEdge(u,v,c);
    }

//    for(FlowEdge e : g.edges)
//    {
//        DBG(e.v);
//        DBG(e.cap);
//        DBG(e.flow);
//
//    }

    int s,t;
    cin>>s>>t;
    cout<<g.EdmondsKarp(s,t)<<"\n";
    for(int i=0;i<(int)g.edges.size() ; i+=2)
    {
        cout<<g.edges[i+1].v<<" "<<g.edges[i].v<<" "<<g.edges[i].flow<<"/"<<g.edges[i].cap<<"\n";
    }
}
