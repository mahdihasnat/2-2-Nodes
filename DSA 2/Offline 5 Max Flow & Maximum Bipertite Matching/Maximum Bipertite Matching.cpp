
#include<bits/stdc++.h>
using namespace std;

#include "Edmonds-Karp.h"
#include "Bipertite Checking.h"


int main()
{
    freopen("input2.txt" , "r+" , stdin );
    freopen("output2.txt" , "w+" , stdout );

    int n,m;
    cin>>n>>m;
    Graph input_graph(n);

    while(m--)
    {
        int u,v;
        cin>>u>>v;
        input_graph.AddEdge(u,v);
    }
    if(input_graph.isBipertite())
    {

        vector<int > new_numbering(n) , old_numbering(n);

        int new_node = 0;
        for(int i=0;i<n;i++) if(input_graph.color[i] == 0) old_numbering[new_node] = i  , new_numbering[i] = new_node ++  ;
        for(int i=0;i<n;i++) if(input_graph.color[i] == 1) old_numbering[new_node] = i  , new_numbering[i] = new_node ++;
        int source = new_node++;
        int sink = new_node ++;

        assert(new_node == n+2);

        FlowGraph g(n+2);



        for(int i=0;i<n;i++)
            if(input_graph.color[i] == 0)
                g.AddEdge(source , new_numbering[i] , 1);
            else
                g.AddEdge(new_numbering[i] , sink , 1);
        for(int i=0;i<n;i++)
            if(input_graph.color[i] == 0)
            {
                for(int j: input_graph.adjlist[i])
                {
                    int u = new_numbering[i];
                    int v = new_numbering[j];
                    g.AddEdge(u,v,1);
                }
            }
        cout<<g.EdmondsKarp(source , sink)<<"\n";
        for(int i =0; i<(int)g.edges.size(); i+=2)
        {
            int u = g.edges[i+1].v;
            int v = g.edges[i].v;
            if(g.edges[i].flow == 0) continue ;
            if(u == source or v == sink) continue ;
            cout<<old_numbering[u]<<" "<<old_numbering[v]<<"\n";
        }


    }
    else cout<<"The graph is not bipartite\n";
}
