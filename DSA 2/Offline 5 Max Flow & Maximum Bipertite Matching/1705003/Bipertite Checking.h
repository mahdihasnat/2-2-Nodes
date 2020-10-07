
#ifndef BIPERTITE_CHECKING_ADDED
#define BIPERTITE_CHECKING_ADDED

#include "Queue.h"

class Graph ///Unweighted Undirected 0-indexed
{
public :

    vector< vector<int > > adjlist;
    vector<int > color;

    Graph(int n) : adjlist(n) , color(n) {}

    void AddEdge(int u,int v)
    {
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }

    bool isBipertite()
    {
        for(int &c : color) c = -1;
        for(int u = 0 ; u <(int) color.size() ; u++)
        {
            if(color[u] == -1)
            {
                Queue<int > q;

                color[u]= 0;
                q.enqueue(u);

                while(!q.empty())
                {
                    int uu = q.front();
                    q.dequeue();

                    for(int vv: adjlist[uu])
                    {
                        if(color[vv] == -1)
                        {
                            color[vv] = !color[uu];
                            q.enqueue(vv);
                        }
                        if(color[vv]  == color[uu]) return 0;
                    }

                }
            }

        }
        return 1;
    }

};


#endif // BIPERTITE_CHECKING_ADDED
