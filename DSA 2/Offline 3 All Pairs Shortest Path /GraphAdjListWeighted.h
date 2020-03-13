#ifndef ADDED_GRAPHADJLIST
#define ADDED_GRAPHADJLIST 1
#include <queue>
#include <cstring>
#include <iostream>
#define NIL -1
#define INFINITY 1000000000
#define WHITE 1
#define GRAY 2
#define BLACK 3

#define DBG(x) cout << (#x) << " --> " << (x) << endl;

using namespace std;

template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p)
{
    os << "{" << p.first << "," << p.second << "}";
    return os;
}

template <class T>
class Edge
{
    int u, v;
    T w;

public:
    Edge(int u, int v, T w) : u(u), v(v), w(w) {}
    int getU() { return u; }
    int getV() { return v; }
    T getW() { return w; }
    void setW(T w) { this->w = w; }
    friend ostream &operator<<(ostream &os, const Edge &e)
    {
        return os << " ( " << e.u << " , " << e.v << " , " << e.w << " ) ";
    }
};

class Graph
{
    typedef double WeightType;
    int nVertices, nEdges;
    const bool directed = 1;
    const int startIndex;
    vector<Edge<WeightType>> *adjList;
    int *color, *parent;
    WeightType *dist;

    WeightType **distMatrix;
    int **parentMatrix;
    void initializeSingleSource(int source);
    void printShortestPathInternal(int u, int v);

public:
    Graph(int startIndex);
    ~Graph();
    void setnVertices(int n);

    bool addEdge(int u, int v, WeightType w);
    bool isEdge(int u, int v);
    void removeEdge(int u, int v);
    void reweightEdge(int u, int v, WeightType w);
    Edge<WeightType> *searchEdge(int u, int v);
    WeightType getWeight(int u, int v);
    WeightType getShortestPathWeight(int u, int v);

    void dijkstra(int source);    //single source shortest path with out negative cycle
    bool bellmenford(int source); // return true if negative exist , single source shortest path with negative cycle
    void floydWarshall();         // all pair shortest path with out negative cycle , O(V^3)
    void johnsonsAlgo();          /// usefull for sparse graph  , O(V^2 log V  + V * E )
    void cleanSPInfo();

    void printShortestPath(int u, int v);
    void printDistanceMatrix();
    void printPredecessorMatrix();
    void printGraph();
};

void Graph::printShortestPath(int u, int v)
{
    u -= startIndex;
    v -= startIndex;

    printShortestPathInternal(u, v);
}

void Graph::printShortestPathInternal(int u, int v)
{
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices || parentMatrix[u][v] == NIL)
    {
        cout << " No Path ";
    }
    else if (parentMatrix[u][v] == u)
    {
        cout << u + startIndex << " --> " << v + startIndex << "(" << distMatrix[u][v] << ")";
    }
    else
    {
        printShortestPathInternal(u, parentMatrix[u][v]);
        cout << " --> " << v + startIndex << "(" << distMatrix[u][v] - distMatrix[u][parentMatrix[u][v]] << ")";
    }
}

void Graph::printPredecessorMatrix()
{
    cout << "Predecessor Matrix:\n";
    for (int i = 0; i < nVertices; i++)
    {
        for (int j = 0; j < nVertices; j++)
            if (parentMatrix[i][j] == NIL)
                cout << "NIL ";
            else
                cout << parentMatrix[i][j] + startIndex << " ";
        cout << endl;
    }
    cout << endl;
}
void Graph::printDistanceMatrix()
{
    cout << "Distance Matrix:\n";
    for (int i = 0; i < nVertices; i++)
    {
        for (int j = 0; j < nVertices; j++)
            if (distMatrix[i][j] == INFINITY)
                cout << "INF ";
            else
                cout << distMatrix[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}
void Graph ::johnsonsAlgo()
{
    if (bellmenford(nVertices + startIndex))
    {
        cout << "There is a negative-weight cycle." << endl;
    }
    else
    {
        // DBG(dist);
        // for(int i=0;i<nVertices;i++)
        //     cout<<dist[i]<<" ";
        // cout<<endl;
        for (int i = 0; i < nVertices; i++)
        {
            for (int j = 0; j < adjList[i].size(); j++)
            {
                int u = i, v = adjList[i][j].getV() - startIndex;
                adjList[i][j].setW(adjList[i][j].getW() - dist[v] + dist[u]);
            }
        }
        for (int i = 0; i < nVertices; i++)
        {
            swap(distMatrix[i], dist);
            swap(parentMatrix[i], parent);

            dijkstra(i + startIndex);

            swap(distMatrix[i], dist);
            swap(parentMatrix[i], parent);

            for (int j = 0; j < nVertices; j++)
                distMatrix[i][j] += dist[j] - dist[i];
        }
        for (int i = 0; i < nVertices; i++)
        {
            for (int j = 0; j < adjList[i].size(); j++)
            {
                int u = i, v = adjList[i][j].getV() - startIndex;
                adjList[i][j].setW(adjList[i][j].getW() + dist[v] - dist[u]);
            }
        }
    }
}

Graph::WeightType Graph::getShortestPathWeight(int u, int v)
{
    u -= startIndex;
    v -= startIndex;
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return INFINITY;
    return distMatrix[u][v];
}

void Graph::cleanSPInfo()
{
    for (int i = 0; i < nVertices; i++)
        for (int j = 0; j < nVertices; j++)
            distMatrix[i][j] = INFINITY, parentMatrix[i][j] = NIL;
}
void Graph::floydWarshall()
{
    for (int i = 0; i < nVertices; i++)
    {
        for (int j = 0; j < nVertices; j++)
            distMatrix[i][j] = INFINITY, parentMatrix[i][j] = NIL;
        distMatrix[i][i] = 0;
        for (int j = 0; j < adjList[i].size(); j++)
        {
            int u = i, v = adjList[i][j].getV() - startIndex, w = adjList[i][j].getW();
            if (distMatrix[u][v] > w)
            {
                distMatrix[u][v] = w;
                parentMatrix[u][v] = u;
            }
        }
    }
    for (int k = 0; k < nVertices; k++)
    {
        for (int i = 0; i < nVertices; i++)
        {
            for (int j = 0; j < nVertices; j++)
                if (distMatrix[i][j] > distMatrix[i][k] + distMatrix[k][j])
                {
                    distMatrix[i][j] = distMatrix[i][k] + distMatrix[k][j];
                    parentMatrix[i][j] = parentMatrix[k][j];
                }
        }
    }
}

Graph::WeightType Graph::getWeight(int u, int v)
{
    u -= startIndex;
    v -= startIndex;
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return INFINITY;
    for (int i = 0; i < adjList[u].size(); i++)
    {
        if (adjList[u][i].getV() == v + startIndex)
            return adjList[u][i].getW();
    }
    return INFINITY;
}

Graph::Graph(int startIndex) : startIndex(startIndex)
{
    nVertices = 0;
    nEdges = 0;
    adjList = 0;
    color = 0;
    parent = 0;
    dist = 0;
    distMatrix = 0;
    parentMatrix = 0;
}

void Graph::setnVertices(int n)
{

    if (adjList != 0)
        delete[] adjList; //delete previous list
    if (color != 0)
        delete[] color; //delete previous color
    if (parent != 0)
        delete[] parent; //delete previous parent
    if (dist != 0)
        delete[] dist; //delete previous parent
    if (distMatrix)
    {
        for (int i = 0; i < nVertices; i++)
            delete[] distMatrix[i];
        delete[] distMatrix;
    }
    if (parentMatrix)
    {
        for (int i = 0; i < nVertices; i++)
            delete[] parentMatrix[i];
        delete[] parentMatrix;
    }

    adjList = new vector<Edge<WeightType>>[n];

    distMatrix = new WeightType *[n];
    for (int i = 0; i < n; i++)
        distMatrix[i] = new WeightType[n];

    parentMatrix = new int *[n];
    for (int i = 0; i < n; i++)
        parentMatrix[i] = new int[n];

    color = new int[n];
    parent = new int[n];
    dist = new WeightType[n];

    this->nVertices = n;
    this->nEdges = 0;
}

Edge<Graph::WeightType> *Graph::searchEdge(int u, int v)
{
    u -= startIndex;
    v -= startIndex;
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return 0;
    for (int i = 0; i < adjList[u].size(); i++)
    {
        if (adjList[u][i].getV() == v + startIndex)
            return &adjList[u][i];
    }
    return 0;
}

void Graph ::reweightEdge(int u, int v, WeightType w)
{
    u -= startIndex;
    v -= startIndex;
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return;
    for (int i = 0; i < adjList[u].size(); i++)
    {
        if (adjList[u][i].getV() == v + startIndex)
            adjList[u][i].setW(w);
    }
}

bool Graph::addEdge(int u, int v, WeightType w)
{
    u -= startIndex;
    v -= startIndex;
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return 0; //vertex out of range
    for (int i = 0; i < adjList[u].size(); i++)
    {
        if (adjList[u][i].getV() == v + startIndex)
        {
            adjList[u][i].setW(min(adjList[u][i].getW(), w));

            if (!directed)
            {
                for (int j = 0; j < adjList[v].size(); j++)
                {
                    if (adjList[v][j].getV() == u + startIndex)
                    {
                        adjList[v][j].setW(min(adjList[v][j].getW(), w));
                        break;
                    }
                }
            }
            return 1;
        }
    }
    adjList[u].push_back({u+startIndex, v + startIndex , w});
    if (!directed)
        adjList[v].push_back({v + startIndex , u + startIndex, w});
    return 1;
}
bool Graph::isEdge(int u, int v)
{
    u -= startIndex;
    v -= startIndex;
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return 0; //vertex out of range
    for (auto e : adjList[u])
        if (e.getV() == v + startIndex)
            return 1;
    return 0;
}
void Graph::removeEdge(int u, int v)
{
    u -= startIndex;
    v -= startIndex;
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return; //vertex out of range
    for (int i = 0; i < adjList[u].size(); i++)
    {
        if (adjList[u][i].getV() == v + startIndex)
        {
            adjList[u].erase(adjList[u].begin() + i);
            i--;
            nEdges--;
        }
    }
}

void Graph::printGraph()
{
    cout << "Graph:" << endl;
    for (int i = 0; i < nVertices; i++)
    {
        cout << i + startIndex << " : ";
        for (int j = 0; j < adjList[i].size(); j++)
        {
            if (j > 0)
                cout << " --> ";
            cout << (adjList[i][j].getV()) << "(" << adjList[i][j].getW() << ")";
        }
        cout << endl;
    }
}

void Graph::initializeSingleSource(int source)
{
    for (int i = 0; i < nVertices; i++)
    {
        dist[i] = INFINITY;
        parent[i] = NIL;
        color[i] = WHITE;
    }
    if (source < nVertices and source >= 0)
        dist[source] = 0;
}

void Graph::dijkstra(int source)
{
    source -= startIndex;
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

        if (color[u] != WHITE)
            continue;

        color[u] = GRAY;
        for (int i = 0; i < adjList[u].size(); i++)
        {
            int v = adjList[u][i].getV() - startIndex;
            if (color[v] != WHITE)
                continue;
            WeightType w = adjList[u][i].getW();
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
    source -= startIndex;

    if (source < 0 || source > nVertices)
        return 0;
    initializeSingleSource(source);
    if (source == nVertices) // johnson case
    {
        for (int i = 0; i < nVertices; i++)
            dist[i] = 0;
    }
    for (int i = 1; i <= nVertices - 1; i++)
    {
        for (int u = 0; u < nVertices; u++)
        {
            for (int j = 0; j < adjList[u].size(); j++)
            {
                int v = adjList[u][j].getV() - startIndex;
                WeightType w = adjList[u][j].getW();
                if (dist[v] > dist[u] + w)
                    dist[v] = dist[u] + w, parent[v] = u;
            }
        }
    }
    for (int u = 0; u < nVertices; u++)
    {
        for (int j = 0; j < adjList[u].size(); j++)
        {
            int v = adjList[u][j].getV() - startIndex;
            WeightType w = adjList[u][j].getW();
            if (dist[v] > dist[u] + w)
            {
                return 1;
            }
        }
    }
    return 0;
}

Graph::~Graph()
{
    if (adjList != 0)
        delete[] adjList; //delete previous list
    if (color != 0)
        delete[] color; //delete previous color
    if (parent != 0)
        delete[] parent; //delete previous parent
    if (dist != 0)
        delete[] dist; //delete previous parent
    if (distMatrix)
    {
        for (int i = 0; i < nVertices; i++)
            delete[] distMatrix[i];
        delete[] distMatrix;
    }
    if (parentMatrix)
    {
        for (int i = 0; i < nVertices; i++)
            delete[] parentMatrix[i];
        delete[] parentMatrix;
    }
    nVertices = nEdges = 0;
}

#endif
