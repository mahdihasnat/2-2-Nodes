#include <iostream>
#include <iterator>
#include <random>
#include <chrono>
using namespace std;
#include "GraphAdjacencyList.h"
#define DBG(a) cout << (#a) << " --> " << (a) << endl
#define NL cout << endl
namespace Timer
{
typedef chrono::nanoseconds duration;
typedef duration::rep rep;
typedef duration::period period;
typedef chrono::time_point<chrono::_V2::system_clock, duration> time_point;
time_point start, stop;
void StartTimer()
{
    start = chrono::high_resolution_clock::now();
}
double StopTimer()
{
    stop = chrono::high_resolution_clock::now();
    return (chrono::duration_cast<chrono::microseconds>(stop - start)).count();
}

} // namespace Timer
mt19937 rng((unsigned)chrono::system_clock::now().time_since_epoch().count()); //mt199937_64 for ll

inline int random(int a, int b) // [1,b]
{
    return a + rng() % (b - a + 1);
}

int main()
{
    srand(time(0));
    const int TOTAL_ITERATION = 10;
    for (int v = 1e3; v <= 16e3; v *= 2)
    {
         for (int e = v; e <= (v * v - v) / 8; e *= 2)
        //for (int e = v; e <=v; e *= 2)
        {
            /* DBG(v);
            DBG(e);
            NL;  */
            Graph g;
            g.setnVertices(v);
            for (int i = 0; i < e; i++)
                g.addEdge(random(0, v - 1), random(0, v - 1));
            Timer::StartTimer();
            for(int i=0;i<TOTAL_ITERATION;i++)
            {
                g.bfs(rng() % v);
            }
            double tim = Timer::StopTimer();
            tim/=TOTAL_ITERATION;
            cout<<v<<" "<<e<<" "<<tim<<"\n";
            // printf("%f\n",tim);
            // printf("%d\n",e);
        }
    }
}
