#include<bits/stdc++.h>
#include "GraphAdjListWeighted.h"
using namespace std;

int id(map<string,int > &ids, map<int,string  > &re_ids,  string s)
{
    if(ids.find(s)==ids.end())
    {
//        DBG(s);
//        DBG(ids.size());
        int x = ids.size();
        re_ids[x] = s;
        return ids[s] = x;
    }
    else return ids[s];
}


void printpath(map< int  , string  > &re_ids ,int * parent ,  int s,int t  )
{
    if(s==t)
    {
        cout<<re_ids[s]<<" ";
    }
    else
    {
        printpath(re_ids ,parent ,  s, parent[t]);
        cout<<" -> "<<re_ids[t]<<" ";
    }
}

int main()
{
//    freopen("input.txt" , "r+" , stdin);
//    freopen("output.txt" , "w+" , stdout);
    int n1,m1;
    cin>>n1>>m1;

    int n2,m2;
    cin>>n2>>m2;

    vector< pair < pair < int, int  >, int > >   edges;
    map<string,int > ids;
    map<int, string  > re_ids;

    for(int i=1; i<=m1; i++)
    {
        pair < pair < int, int  >, int > e ;
        string u,v;
        int w;
        cin>>u>>v>>w;
        e.first.first=id(ids, re_ids, u);
        e.first.second=id(ids, re_ids, v);
        e.second = w;
        edges.push_back(e);
    }
    for(int i=1; i<=m2; i++)
    {
        pair < pair < int, int  >, int > e ;
        string u,v;
        int w;
        cin>>u>>v>>w;
        e.first.first=id(ids, re_ids, u);
        e.first.second=id(ids, re_ids, v);
        e.second = w;
        edges.push_back(e);
    }
    int p1,p2;
    cin>>p1;
    vector < pair <int,int >   > left_city(p1);

    for(int i=0; i<p1; i++)
    {
        string s;
        cin>>s>>left_city[i].second;

        left_city[i].first = id(ids, re_ids, s);
    }
    cin>>p2;
    vector < pair <int,int >   > right_city(p2) ;

    for(int i=0; i<p2; i++)
    {
        string s;
        cin>>s>>right_city[i].second;
        right_city[i].first = id(ids, re_ids, s);
    }

    for(int i=0; i<p1; i++)
    {
        for(int j=0; j<p2; j++)
            edges.push_back(make_pair( make_pair (left_city[i].first,right_city[j].first  ), left_city[i].second + right_city[j].second ) );
    }

    int s,t;

    string ss;
    cin>>ss;
    s=id(ids, re_ids,ss);

    cin>>ss;
    t=id(ids, re_ids,ss);

    Graph g;
    g.setnVertices(ids.size());
//    DBG(ids.size());
    for(auto e: edges)
    {
        g.addEdge(e.first.first , e.first.second , e.second);
        g.addEdge(e.first.second , e.first.first , e.second);
    }

//    for(auto i: re_ids) cout<<" { " <<i.first<<" , "<<i.second<<"}\n";
//    for(auto i: ids) cout<<" { " <<i.first<<" , "<<i.second<<"}\n";

//    DBG(s);
//    DBG(t);
//
//    g.printGraph();

    g.dijkstra(s);


    cout<<g.getDist(t)<<"\n";
//    g.printPath(s,t);

    printpath(re_ids ,g.getParent() , s, t);
    cout<<"\n";
    map<int ,bool > lefts;
    map<int ,bool > rights;
    for(auto i: left_city) lefts[i.first] = 1;
    for(auto i: right_city) rights[i.first] = 1;

    pair < int  , int > ans;
    while(s!=t)
    {
        if(rights.find(t)!=rights.end()) ans.second = t;
        if(lefts.find(t)!=lefts.end()) ans.first = t;
        t = g.getParent()[t];
    }
    if(lefts.find(t)!=lefts.end()) ans.first = t;
    cout<<re_ids[ans.first]<<" ";
    cout<<re_ids[ans.second]<<" \n";
}
