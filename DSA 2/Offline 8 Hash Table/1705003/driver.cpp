#include<bits/stdc++.h>
using namespace std;


#define DBG(a) cout << (#a) << " --> " << (a) << endl
#define NL cout << endl

#include "hash_functions.h"
#include "hash_chained.h"
#include "hash_double.h"
#include "hash_custom.h"


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

string random_string(const int len)
{

    string str (len,0);
    for(char &ch : str)
    {
        static const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        ch =  charset[ rng() % max_index ];
    }
    return str;
}

template<class Hash >
double HashCollisionRate(int total_string,int string_len, int tableSize)
{
    Hash h ;
    map< unsigned int, int > mp;
    int total_collision = 0;
    for(int i=0; i<total_string; i++)
    {
        auto x = h(random_string(string_len))%tableSize;
        total_collision += mp[x];
        mp[x]++;
    }
    return 100.0 * total_collision /total_string/(total_string -1) * 2;
}
template<class Hash >
double HashCollisionRate2(int total_string,int string_len, int tableSize)
{
    Hash h ;
    set<unsigned int > st;
    int total_collision = 0;
    for(int i=0; i<total_string; i++)
    {
        auto x = h(random_string(string_len))%tableSize;
        total_collision+=st.find(x)!=st.end();
        st.insert(x);
    }
    return 100.0 * total_collision /total_string;
}

int main()
{
    const int N = 10000;

    int tableSize = N;
    cin>>tableSize;


    DBG(HashCollisionRate<Hash1<string> >(10000, 7,  10000));
    DBG(HashCollisionRate2<Hash1<string> >(10000, 7,  10000));

    DBG(HashCollisionRate<Hash2<string> >(10000, 7, 10000));
    DBG(HashCollisionRate2<Hash2<string> >(10000, 7, 10000));


    using namespace HashCustom;

    HashTable<string,int, Hash2<string> > hashmap(tableSize);

    int total_inserted = 0;
    int generation_collision_count = 0;

    vector<string > keys;

    while(total_inserted < N)
    {
        string s = random_string(7);
        //DBG(s);
        if(hashmap.Search(s) == 0)
        {
            if(hashmap.Insert(s, ++total_inserted))
                keys.push_back(s);
        }
        else
            generation_collision_count++;
    }
    DBG(keys.size());
    hashmap.total_prob = 0;


    for(int i=0; i<1000; i++)
    {
        string s = keys[rng()%keys.size()];
        assert(hashmap.Search(s));
    }


    DBG(hashmap.total_collision);
    DBG(hashmap.total_prob * 1.0 /(keys.size()) );

}
