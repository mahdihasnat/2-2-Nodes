#include <iostream>
#include "GraphAdjListWeighted.h"

using namespace std;

int main()
{
    freopen("input.txt", "r+", stdin);
    freopen("output.txt", "w+", stdout);
    int n, m;
    cin >> n >> m;
    Graph g(1);
    g.setnVertices(n);
    while (m--)
    {
        int u, v;
        double w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    cout << "Graph Created.\n"
         << endl;
    int c;
    while (cin >> c)
    {
        if (c == 1)
        {
            g.cleanSPInfo();
            cout << "APSP matrices cleared\n"
                 << endl;
        }
        else if (c == 2)
        {
            g.floydWarshall();
            cout << "Floyd-Warshall algorithm implemented" << endl;
        }
        else if (c == 3)
        {
            g.johnsonsAlgo();
            cout << "Johnson’s algorithm implemented" << endl;
        }
        else if (c == 4)
        {
            int u, v;
            cin >> u >> v;
            cout << "Shortest Path Weight: " << g.getShortestPathWeight(u, v) << endl;
            cout << "Path: ";
            g.printShortestPath(u, v);
            cout << endl;
            cout << endl;
        }
        else if (c == 5)
            g.printGraph();
        else if (c == 6)
            g.printDistanceMatrix();
        else if (c == 7)
            g.printPredecessorMatrix();
        else
            break;
    }
}