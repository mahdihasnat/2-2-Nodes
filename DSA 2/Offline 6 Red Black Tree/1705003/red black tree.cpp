#include<bits/stdc++.h>
using namespace std;
#define DBG(a) cerr<< "line "<<__LINE__ <<" : "<< #a <<" --> "<<(a)<<endl
#define NL cout<<endl


#include "red black tree.h"

int main()
{

    freopen("input.txt","r+", stdin);
    freopen("output.txt","w+", stdout);
    RBT<int > rbt;
    char c ;
    int a;
    while(cin>>c>>a)
    {
        if(c=='I')
        {
            rbt.insert(a);

            rbt.print();
            cout<<"\n";
        }
        else if(c=='F')
        {
            cout<<(rbt.find(a)?"True\n":"False\n");
        }
        else if(c=='D')
        {
            rbt.Delete(a);
            rbt.print();
            cout<<"\n";
        }
    }
}
