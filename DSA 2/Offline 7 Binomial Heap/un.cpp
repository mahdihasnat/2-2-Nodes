#include <bits/stdc++.h>
#define ff first
#define ss second
#define pii pair < ll , ll  >
#define psi pair < string , ll  >
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define input freopen("input.txt","r",stdin)
#define output freopen("output.txt","w",stdout)
#define fast_input ios_base::sync_with_stdio(false)


using namespace std;
typedef long long ll;
const ll  inf=1e16;
/// code starts here



#define DBG(a) cerr<< "line "<<__LINE__ <<" : "<< #a <<" --> "<<(a)<<endl
#define NL cout<<endl


template < class T >
class BinomialTree
{
private :

public :
    T data ;
    int degree ;

#define pTree BinomialTree<T>*
    pTree parent;
    pTree sibling;
    pTree child;

    /// child points to largest degree child , sibling points to smaller degree tree under same parent


    BinomialTree(T data = T(0)): data(data)
    {
        degree = 0;
        parent = sibling = child = 0;
    }

    void Print()
    {
        queue<pair < pTree ,int >  > q;
        q.push(make_pair(this , 0));

        int lastlevel = -1;

        while(!q.empty())
        {
            pTree now = q.front().first;
            int level = q.front().second;
            q.pop();

            if(lastlevel != level)
                cout<<"\nLevel "<<level<<" :";
            lastlevel = level;

            cout<<" "<<now->data;

            now = now->child;
            while(now)
            {
                q.push(make_pair(now , level+1));
                now =now->sibling;
            }

        }
    }

    ~BinomialTree()
    {
        
        if(child)
            delete child;
        if(sibling)
            delete sibling;
    }
};


template<class T >
pTree Union(pTree t1, pTree t2)
{

    //make sure degree of both tree are same
    assert(t1->degree == t2->degree);

    // make t1->data < t2->data
    if( t2->data < t1->data )
        swap(t1, t2);

    t2->parent = t1 ;
    t2->sibling  = t1->child;
    t1->child = t2;
    t1->degree ++;

    return t1;
}

template < class T >
class BinomialHeap
{
private :
    BinomialTree < T> * head;

    void AddTree(pTree & last_head, pTree new_head)
    {
        new_head->parent = 0;
        if(last_head)
            last_head->sibling = new_head;
        else
            head=new_head ;
        last_head = new_head;
        new_head->sibling = 0;
    }

public:
    BinomialHeap():head(0) {}
    BinomialHeap(T data )
    {
        head = new BinomialTree<T>(data);
    }

    bool Empty()
    {
        return head == 0;
    }

    void Union(BinomialHeap<T> &h)
    {


        pTree carry_head = 0;
        pTree head1 = head; /// current head from this heap
        pTree head2 = h.head; /// current head from h heap
        pTree last_head = 0;


        while(head1 or head2)
        {

            int d1 = head1 ? head1->degree : 1000000 ;
            int d2 = head2 ? head2->degree : 1000001 ;
            int dmin = min(d1,d2);

            if(d1 > d2)
            {
                swap(d1, d2 );
                swap(head1, head2);
            }

            assert(head1);

            /// now head1 contains minimum degree

            assert(dmin >= (carry_head ? carry_head->degree  : -1 ));

            pTree nxt_head1 = head1;
            pTree nxt_head2 = head2;

            if(d1 == d2 )
            {
                assert(head1);
                assert(head2);

                nxt_head1 = head1 -> sibling;
                nxt_head2 = head2 -> sibling;

                pTree merged_head = ::Union(head1, head2);

                if(carry_head)
                {
                    AddTree(last_head,carry_head );
                }
                carry_head = merged_head;

            }
            else
            {
                nxt_head1 = head1->sibling;

                if(carry_head)
                {
                    if(carry_head->degree < d1)
                    {
                        AddTree(last_head, carry_head);
                        AddTree(last_head , head1);
                        carry_head = 0;
                    }
                    else
                    {
                        assert(carry_head->degree ==  d1);
                        carry_head = ::Union(head1, carry_head);
                    }
                }
                else
                {
                    AddTree(last_head, head1);

                }
            }

            head1 = nxt_head1;
            head2 = nxt_head2;
        }
        if(carry_head)
        {
            AddTree(last_head , carry_head);
        }
        h.head=0;

    }

    void Insert(T data)
    {
        BinomialHeap h(data);
        Union(h);
    }
    pTree FindMin()
    {
        assert(head);
        pTree ret_head = head;
        pTree now = head->sibling;
        while(now)
        {
            if(now->data < ret_head->data)
                ret_head = now;
            now = now->sibling;
        }
        return ret_head;
    }
    pTree ExtractMin()
    {
        pTree ret_head = FindMin();

        pTree last_head = 0 ; /// last head in root list where ret_head is sibling of last_head

        if(head != ret_head)
        {
            last_head = head;
            while(last_head->sibling != ret_head)
            {
                last_head = last_head->sibling;
            }
        }
        /// detach  ret_head from this heap

        if(last_head )
        {
            last_head->sibling = ret_head->sibling ;
        }
        else
            head = ret_head->sibling;


        ret_head->parent = 0;
        ret_head->sibling = 0;

        /// now make a heap with child of ret_head


        if(ret_head->child)
        {
            stack<pTree > heads;
            pTree now = ret_head->child;

            while(now)
            {
                heads.push(now);
                now = now->sibling;
            }
            BinomialHeap h;
            last_head = 0;

            while(!heads.empty())
            {
                h.AddTree(last_head, heads.top());
                heads.pop();
            }

            Union(h);

        }
        return ret_head;
    }

    void Print()
    {
        cout<<"Printing Binomial Heap...\n";
        pTree now = head;
        while(now)
        {
            cout<<"Binomial Tree, B"<<now->degree ;
            now->Print();
            cout<<"\n";
            now = now->sibling;
        }
        cout<<"\n";
    }

    ~BinomialHeap()
    {
        if(head)
            delete head;
        head = 0;
    }
};


vector < pii > path[100005];
ll pre[100005];
ll dis[100005];


struct data
{
    ll v;
    data(ll a)
    {
        v=a;
    }
    friend bool operator < (data a,data b)
    {
        return dis[a.v]<dis[b.v];
    }
};

void Dijkstra(ll n)
{
    for(ll i=2; i<=n; i++)
        dis[i]=inf;
    BinomialHeap < data > q;
    q.Insert((data)1);
    dis[1]=0;
    while(!q.Empty())
    {
        data aux=q.ExtractMin()->data;
        //cout<<" q.top ()"<<aux.v<<endl;

        if(aux.v==n)
            return ;
        //cout<<path[aux.v].size()<<endl;
        for(ll i=0; i<path[aux.v].size(); i++)
        {
            //cout<<" l hs = "<<dis[path[aux.v][i].ff]<<" rhs "<< dis[aux.v] + path[aux.v][i].ss<<endl;
            if(dis[path[aux.v][i].ff] > dis[aux.v] + path[aux.v][i].ss)
            {
                pre[path[aux.v][i].ff]=aux.v;
                dis[path[aux.v][i].ff] = dis[aux.v] + path[aux.v][i].ss ;
                q.Insert((data)path[aux.v][i].ff);
            }
        }
    }
    //cout<<" here ";
    return ;
}
int main()
{
    fast_input;
    //freopen("output.txt","w+",stdout);

    ll n,m;
    cin>>n>>m;
    while(m--)
    {
        ll a,b,w;
        cin>>a>>b>>w;
        path[a].pb(mp(b,w));
        path[b].pb(mp(a,w));
    }
    Dijkstra(n);
    if(dis[n]==inf)
        cout<<-1<<endl;
    else
    {
        ll b=n;
        ll a=1;
        vector < ll  >ans;
        do
        {
            ans.pb(b);
            b=pre[b];
        }
        while (a!=b);
        ans.pb(a);
        reverse(ans.begin(),ans.end());

        for(ll i=0; i<ans.size(); i++)
        {
            cout<<ans[i]<<" ";
        }
    }
}