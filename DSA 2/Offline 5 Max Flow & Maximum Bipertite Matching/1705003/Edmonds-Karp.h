#ifndef EDMONDS_KARP_ADDED
#define EDMONDS_KARP_ADDED

#include "Queue.h"
#include "Pair.h"

#define FlowType int
const FlowType flow_inf = 1e9;
struct FlowEdge
{
    int v;
    FlowType flow , cap ;
    FlowEdge(int v,FlowType flow , FlowType cap) : v(v) , flow(flow) , cap(cap) {}
};

struct FlowGraph /// 0-indexed graph
{
    vector< FlowEdge > edges;
    vector< vector<int> > adjlist;
    vector<int > parentedge;
    FlowGraph(int n) :  edges() , adjlist(n) ,  parentedge(n) {}

    int AddEdge(int u,int v,FlowType cap)
    {
        adjlist[u].push_back(edges.size());
        edges.emplace_back(v,0,cap);
        adjlist[v].push_back(edges.size());
        edges.emplace_back(u,0,0);
        return edges.size() - 2;
    }

    FlowType bfs(int s,int t)
    {
        for(int & u: parentedge ) u= -1;
        parentedge[s] = -2;

        Queue< Pair<int ,FlowType>  > q;
        q.enqueue( Pair<int , FlowType > ( s , flow_inf) );

        while(!q.empty())
        {
            int u = q.front().first;
            FlowType flow = q.front().second;
            q.dequeue();


            for(int i: adjlist[u])
            {
                FlowEdge &e = edges[i];

                int v = e.v;
                int newflow =   min(flow , e.cap - e.flow );

                if(parentedge[v] != - 1 or newflow <= 0 ) continue ;

                parentedge[v] =  i;

                if(v== t) return newflow;

                q.enqueue( Pair < int , FlowType > ( v, newflow ) );

            }

        }

        return 0;

    }

    FlowType EdmondsKarp(int s,int t)
    {
        FlowType flow = 0 , newflow;

        while((newflow = bfs(s,t)) > 0 )
        {

            flow+=newflow;
            int u = t;
            while(parentedge[u] !=-2)
            {
                edges[parentedge[u]].flow+=newflow;
                edges[parentedge[u]^1].flow-=newflow;
                u=edges[parentedge[u]^1].v;
            }
        }
        return flow;
    }

};

#endif // EDMONDS_KARP_ADDED
