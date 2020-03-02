#ifndef ADDED_GRAPHADJMATRIX
#define ADDED_GRAPHADJMATRIX 1

#include "myqueue.h"
#include<stdio.h>
#include<iostream>

#define NULL_VALUE 0
#define INFINITY 999999
#define WHITE 1
#define GRAY 2
#define BLACK 3



using namespace std;

class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** adjmatrix ;
    int *color,*parent,*dist;
    void dfs_visit(int source); //will run dfs in the graph
public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    bool addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getOutDegree(int u);
    int getInDegree(int u);
    int getDegree(int u,bool out =true);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(int source); //will run dfs in the graph
    
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjmatrix = 0;
    directed = dir ; //set direction of the graph
    color= 0;
    parent= 0;
    dist= 0;
}

void Graph::setnVertices(int n)
{
    if(adjmatrix)
    {
        for(int i=0;i<nVertices;i++)
            delete  [] adjmatrix[i];
        delete [] adjmatrix;
    }

    if(color!=0) delete[] color ; //delete previous color
    if(parent!=0) delete[] parent ; //delete previous parent
    if(dist!=0) delete[] dist ; //delete previous parent


    this->nVertices = n ;
    this->nEdges=0;
    
    adjmatrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        adjmatrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            adjmatrix[i][j] = 0; //initialize the adjmatrix cells to 0
    }
    
    color = new int [n];
    parent = new int [n];
    dist = new int [n];
}

bool Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices || isEdge(u,v))
        return 0; //vertex out of range
    this->nEdges++ ;
    adjmatrix[u][v]++;
    if(!directed)
        adjmatrix[v][u]++;
    return 1;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices) return ;

    if(isEdge(u,v))
    {
        this->nEdges--;
        adjmatrix[u][v]--;
        if(!directed)
            adjmatrix[v][u]--;
    }
}

bool Graph::isEdge(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices) return 0;

    return adjmatrix[u][v];
    //returns true if (u,v) is an edge, otherwise should return false
}

/*
In graph theory, the degree (or valency) of a vertex of a graph is the number of edges 
that are incident to the vertex,  and in a multigraph, loops are counted twice.
*/

int Graph::getDegree(int u,bool out) 
{
    if(u<0||u>=nVertices)
        return 0;
    int deg=0;

    for(int i=0; i<nVertices; i++)
        deg+= out ? adjmatrix[u][i] :  adjmatrix[i][u] ; 

    return deg;
    //returns the degree of vertex u
}
int Graph::getOutDegree(int u)
{
    return getDegree(u);
}
int Graph::getInDegree(int u)
{
    return getDegree(u,0);
}

void Graph::printAdjVertices(int u)
{
     if(u<0||u>=nVertices)
        return ;
    cout<<"Adjacent vertices of "<<u<<" : ";
    for(int i=0; i<nVertices; i++)
        if(adjmatrix[u][i])
            cout<<i<<" ";
    cout<<"\n";
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices) return 0;

    for(int i=0;i<nVertices;i++)
        if((isEdge(u,i))&&(isEdge(v,i))) return 1;
    return 0;
    //returns true if vertices u and v have common adjacent vertices
}

void Graph::bfs(int source)
{
    if(source<0||source>=nVertices)
        return ;
    //write this function
    for(int i=0; i<nVertices; i++)
    {
        color[i]=WHITE;
        dist[i]=INFINITY;
        parent[i]= NULL_VALUE;
    }

    color[source]=GRAY;
    dist[source]=0;

    Queue <int > q;
    q.enqueue(source);

    cout<<"bfs order : ";

    while(!q.empty())
    {
        int u= q.dequeue();

        cout<<u<<" ";

        for(int i=0; i<nVertices; i++)
        {
            if(adjmatrix[u][i] && color[i]==WHITE)
            {
                color[i]=GRAY;
                dist[i]=dist[u]+1;
                parent[i]=u;
                q.enqueue(i);
            }
        }
        color[u]=BLACK;
    }
    cout<<endl;

}

int Graph::getDist(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices) return INFINITY;
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);
    return dist[v];
}
void Graph:: dfs_visit(int u)
{
    color[ u ] = GRAY;
    cout<<u<<" ";
    for(int v=0;v<nVertices;v++)
    {
        if(adjmatrix[u][v]  and color[v]== WHITE)
        {
            parent[v] = u;
            dfs_visit(v);
        }
    }
    color[u]= BLACK;
}
void Graph::dfs(int source)
{
    if(source< 0 || source>=nVertices) return ;
    cout<<"dfs order : ";
    for(int i=0;i<nVertices;i++)
        color[i]= WHITE , parent[i]= NULL_VALUE;
    dfs_visit(source);
    cout<<endl;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for (int i = 0; i < nVertices; i++)
    {
        printf("%d:", i);
        for (int j = 0; j < nVertices; j++)
        {
            if (adjmatrix[i][j] == 1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if (color)
        delete[] color;
    if (dist)
        delete[] dist;
    if (parent)
        delete[] parent;
    if (adjmatrix)
    {
        for (int i = 0; i < nVertices; i++)
        {
            delete[] adjmatrix[i];
        }
    }
    if (nVertices)
        delete[] adjmatrix;
    nVertices = nEdges = directed = 0;
}

#endif