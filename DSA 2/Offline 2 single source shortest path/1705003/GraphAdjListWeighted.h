#ifndef ADDED_GRAPHADJLIST
#define ADDED_GRAPHADJLIST 1
#include "myarraylist.h"
#include <queue>
#include <iostream>
#define NULL_VALUE -1
#define INFINITY 1000000000
#define WHITE 1
#define GRAY 2
#define BLACK 3

#define DBG(x) cout<<(#x)<<" --> "<<(x)<<endl;

using namespace std;

template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p)
{
    os << "{" << p.first << "," << p.second << "}";
    return os;
}

class Graph
{
    int nVertices, nEdges;
    const bool directed = 1;
    ArrayList<pair<int, int>> *adjList;
    int *color, *parent, *dist;
    void dfs_visit(int source); //will run dfs in the graph
    void initializeSingleSource(int source);

public:
    Graph();
    ~Graph();
    void setnVertices(int n);
    bool addEdge(int u, int v, int w);
    void removeEdge(int u, int v, int w);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void dfs(int source);         //will run dfs in the graph
    void dijkstra(int source);    //will run dijkstra in the graph
    bool bellmenford(int source); //will run bellmenford in the graph
    void printPath(int source,int dest) ;
    int getDist(int u);
};

Graph::Graph()
{
    nVertices = 0;
    nEdges = 0;
    adjList = 0;
    color = 0;
    parent = 0;
    dist = 0;
}

int Graph::getDist(int u)
{
    return dist[u];
}

void Graph::setnVertices(int n)
{
    this->nVertices = n;
    this->nEdges = 0;
    if (adjList != 0)
        delete[] adjList; //delete previous list
    if (color != 0)
        delete[] color; //delete previous color
    if (parent != 0)
        delete[] parent; //delete previous parent
    if (dist != 0)
        delete[] dist; //delete previous parent

    adjList = new ArrayList<pair<int, int>>[nVertices];

    color = new int[n];
    parent = new int[n];
    dist = new int[n];
}

bool Graph::addEdge(int u, int v, int w)
{
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return 0; //vertex out of range
    this->nEdges++;
    adjList[u].insertItem(make_pair(v, w));
    if (!directed)
        adjList[v].insertItem(make_pair(u, w));
    return 1;
}

void Graph::printAdjVertices(int u)
{
    if (u < 0 || u >= nVertices)
        return;
    cout << "Adjacent vertices of " << u << " : ";
    for (int i = 0; i < adjList[u].getLength(); i++)
        cout << adjList[u].getItem(i) << " ";
    cout << "\n";
    //prints all adjacent vertices of a vertex u
}

int Graph::getDist(int u, int v)
{
    if (u < 0 || u >= nVertices || v < 0 || v >= nVertices)
        return INFINITY;
    //returns the shortest path distance from u to v
    dijkstra(u);
    return dist[v];
}
void Graph::dfs_visit(int u)
{
    color[u] = GRAY;
    cout << u << " ";
    for (int i = 0; i < adjList[u].getLength(); i++)
    {
        int v = adjList[u].getItem(i).first;
        if (color[v] == WHITE)
        {
            parent[v] = u;
            dfs_visit(v);
        }
    }
    color[u] = BLACK;
}
void Graph::dfs(int source)
{
    if (source < 0 || source >= nVertices)
        return;
    cout << "dfs order : ";
    for (int i = 0; i < nVertices; i++)
        color[i] = WHITE, parent[i] = NULL_VALUE;
    dfs_visit(source);
    cout << endl;
}

void Graph::printGraph()
{
    cout << "Number of vertices: " << nVertices << ", Number of edges: " << nEdges << "\n";
    for (int i = 0; i < nVertices; i++)
    {
        cout << i << ":";
        for (int j = 0; j < adjList[i].getLength(); j++)
        {
            cout << " " << adjList[i].getItem(j);
        }
        cout << endl;
    }
}

void Graph::initializeSingleSource(int source)
{
    for (int i = 0; i < nVertices; i++)
    {
        dist[i] = INFINITY;
        parent[i] = NULL_VALUE;
        color[i] = WHITE;
    }
    dist[source] = 0;
}

void Graph::dijkstra(int source)
{
    //complete this function
    //initialize BFS variables for all n vertices first
    if (source < 0 || source >= nVertices)
        return;

    initializeSingleSource(source);

    priority_queue<pair<int, int>> pq;
    pq.push({dist[source], source});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if(color[u] !=WHITE) continue;

        // DBG(u);
        // DBG(color[u]);
        // DBG(dist[u]);
        // DBG(dist);
        // for(int i=0;i<nVertices;i++) cout<<dist[i]<<" ";
        // cout<<endl;
        // DBG(parent);
        // for(int i=0;i<nVertices;i++) cout<<parent[i]<<" ";
        // cout<<endl;

        color[u] = GRAY;
        for (int i = 0; i < adjList[u].getLength(); i++)
        {
            int v = adjList[u].getItem(i).first;
            if (color[v] != WHITE)
                continue;
            int w = adjList[u].getItem(i).second;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({-dist[v], v});
            }
        }
        color[u] = BLACK;
    }
}

bool Graph::bellmenford(int source)
{
    if (source < 0 || source >= nVertices)
        return 0;
    initializeSingleSource(source);
    for (int i = 1; i <= nVertices - 1; i++)
    {
        for (int u = 0; u < nVertices; u++)
        {
            for (int j = 0; j < adjList[u].getLength(); j++)
            {
                int v = adjList[u].getItem(j).first;
                int w = adjList[u].getItem(j).second;
                if (dist[v] > dist[u] + w)
                    dist[v] = dist[u] + w, parent[v] = u;
            }
        }
    }
    for (int u = 0; u < nVertices; u++)
    {
        for (int j = 0; j < adjList[u].getLength(); j++)
        {
            int v = adjList[u].getItem(j).first;
            int w = adjList[u].getItem(j).second;
            if (dist[v] > dist[u] + w)
            {
                return 0;
            }
        }
    }
    return 1;
}

 void Graph::printPath(int source,int dest)
 {
     if(source == dest ) 
     {
         cout<<source<<" ";
         return ;
     }
     else if(parent[dest]==NULL_VALUE)
     {
        cout<<"No Path Found\n";
     }
     else 
     {
         printPath(source , parent[dest]);
         cout<<"-> "<<dest;
     }
 }

Graph::~Graph()
{
    nVertices = nEdges = 0;
    if (color)
        delete[] color;
    if (dist)
        delete[] dist;
    if (parent)
        delete[] parent;
    if (adjList)
        delete[] adjList;
}

#endif
