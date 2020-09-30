#include <iostream>
#include "GraphAdjListWeighted.h"

using namespace std;

int main()
{
    freopen("input.txt" , "r+", stdin);
    //freopen("output.txt" , "w+", stdout);
    int n,m;
    cin>>n>>m;
    Graph g(1);
    g.setnVertices(n);
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        g.addEdge(u,v,-w);
    }
    g.floydWarshall();
    while(1)
    {
        int s;
        cin>>s;
        if(s==-1) break ;
//        DBG(g.getShortestPathWeight(s,s));
        bool incycle = 0;
        for(int i=1;i<=n;i++)
            incycle = incycle or (g.getShortestPathWeight(s,i)<1e8 and  g.getShortestPathWeight(i,i) < 0 );
//        for(int i=1;i<=n;i++)
//        {
//            DBG(i);
//            DBG(g.getShortestPathWeight(s,i));
//            DBG(g.getShortestPathWeight(i,i)  );
//
//        }
        cout<<s<<" : "<<(incycle ?  "yes" : "no")<<"\n";
    }
}
