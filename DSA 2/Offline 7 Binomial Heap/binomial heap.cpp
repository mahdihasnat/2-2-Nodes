#include<bits/stdc++.h>

using namespace std ;


#define DBG(a) cerr<< "line "<<__LINE__ <<" : "<< #a <<" --> "<<(a)<<endl
#define NL cout<<endl

#include "Binomial Heap.h"


int main()
{

    freopen("input.txt" , "r+" , stdin);
    freopen("output.txt" , "w+" , stdout);

    BinomialHeap<int > h;

    char cmd ;
    while(cin>>cmd)
    {
        if(cmd == 'I')
        {
            int x;
            cin>>x;
            h.Insert(x);
        }
        else if(cmd == 'F')
        {
            cout<<"Find-Min returned "<<h.FindMin()->data<<"\n";
        }
        else if (cmd == 'E')
        {
            cout<<"Extract-Min returned "<<h.ExtractMin()->data<<"\n";
        }
        else if(cmd == 'P')
        {
            h.Print();
        }
        else if(cmd == 'U')
        {

            string line ;
            getline(cin , line);

            BinomialHeap<int> h2 ;

            stringstream ss(line);
            int x;
            while(ss>>x)
            {
                h2.Insert(x);
            }

            h.Union(h2);
        }

//        h.Print();
//        DBG(__LINE__);
//        NL;

    }
}
