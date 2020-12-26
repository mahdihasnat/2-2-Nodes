#include<bits/stdc++.h>

using namespace std;
const int N = 100005;

double x[N];
double y[N];


int dist(int i,int j)
{
    return round(sqrt((x[i] - x[j]) *(x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) ));
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int u;
        cin>>u;
        cin>>x[u]>>y[u];
    }

    freopen("input.txt" , "w" , stdout);

    cout<<n<<"\n";
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<dist(i,j)<<" ";

        }
        cout<<'\n';
    }
    getchar();
}
