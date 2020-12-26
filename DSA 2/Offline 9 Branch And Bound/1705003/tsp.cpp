
#include<bits/stdc++.h>

using namespace std;


#include "tsp.h"

string to(int n)
{
    string ret= "";
    while(n)
    {
        ret+='0'+(n%10) ;
        n/=10;
    }
    reverse(ret.begin(),  ret.end());
    return ret;
}


#include<windows.h>
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}


int main()
{
    int n;

    for(int i=17; i<=18; i++)
    {
        //if(i==17) continue;
        const string file = "data"+to(i)+".txt";

        ifstream in(file);

//        freopen(file.c_str() , "r", stdin );
        string s;
        in>>s;
        DBG(s);
        DBG(file);

        in>>n;
        TSP<int> t(n);
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
                in>>t.adj[i][j];
        }
        DBG(s);
        StartCounter();
        DBG(t.bnb_recursion());
        DBG(GetCounter()/1000000.0);
        cout<<"\n";
    }
    while(1)
        getchar();
}
