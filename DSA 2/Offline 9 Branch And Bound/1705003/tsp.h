#ifndef TSP_ADDED
#define TSP_ADDED


#include<bits/stdc++.h>
using namespace std;

#define INF 1000000000

#define DBG(x) cout<<(#x) <<" --> "<<(x)<<"\n"
#define NL cout<<endl

template< typename WeightType >
class TSP
{
public:
    WeightType ** adj;
    int n;
    TSP(int n) : n(n)
    {
        adj = new int* [n+1];
        for(int i=0; i<n+1; i++)
            adj[i] = new int [n+1];

    }
    ~TSP()
    {
        if(adj)
        {
            for(int i=0; i<n+1; i++)
                delete [] adj[i];
            delete [] adj;
        }
    }
    WeightType brute_force()
    {
        WeightType mn = INF;
        vector<int > order (n-1);
        for(int i=0; i<n-1; i++)
            order[i] = i+2;
        do
        {
            WeightType now  = 0;
            now+=adj[1][order[0]];
            for(int i=1; i<n-1; i++)
                now+=adj[order[i-1]][order[i]];
            now+=adj[order[n-2]][1];
            mn = min(mn, now);
        }
        while(next_permutation(order.begin(), order.end()));

        return mn;
    }

    class Node
    {
    public:
        bool * visited  ;
        int present_node;

        WeightType bound_x_2 ;
        Node(int n):present_node(1), bound_x_2(0)
        {
            visited = new bool [n+1];
            for(int i=0; i<n+1; i++)
                visited[i] = 0;
            visited[1] = 1;
        }


        ~Node()
        {
            if(visited)
                delete [] visited;
        }
    };

    class cmp
    {
    public:
        bool operator()(const Node * l,const Node * r)
        {
            return l->bound_x_2 > r->bound_x_2;
        }
    };

    WeightType bnb()
    {
        priority_queue< Node *, vector < Node * >, cmp > pq;

        Node * root = new Node(n) ;

        vector<WeightType> outgoing_minimum(n+1), incoming_minimum(n+1) ;
        for(int i=1; i<=n; i++)
            incoming_minimum[i]=outgoing_minimum[i]=INF;
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(i==j)
                    continue;
                outgoing_minimum[i] = min(outgoing_minimum[i], adj[i][j]);
                incoming_minimum[j] = min(incoming_minimum[j], adj[i][j]);
            }
        }

        for(int i=1; i<=n; i++)
            root->bound_x_2 += outgoing_minimum[i] + incoming_minimum[i];


        pq.push(root);

        WeightType current_minimum_x_2 = INF;

        while(!pq.empty())
        {

            Node * x = pq.top();
            pq.pop();

            if(current_minimum_x_2 < x->bound_x_2 )
                break;

            bool have_branch = 0;
            for(int i=2; i<=n; i++)
            {
                if(x->visited[i] == 0)
                {
                    have_branch = 1;

                    Node * y = new Node(n);
                    memcpy(y->visited, x->visited, sizeof(bool) * (n+1));   /// dest , source , size (byte)
                    y->visited[i] = 1;
                    y->present_node = i;
                    y->bound_x_2 = x->bound_x_2 -  outgoing_minimum[x->present_node] - incoming_minimum[i]  + adj[x->present_node][i] * 2 ;

                    pq.push(y);

                }
            }
            if(!have_branch)
            {
                x->bound_x_2 += -outgoing_minimum[x->present_node] -incoming_minimum[1] + adj[x->present_node][1] * 2;

                current_minimum_x_2 = min(current_minimum_x_2, x->bound_x_2);
            }

        }

        return current_minimum_x_2/2;

    }

    WeightType bnb_stack()
    {
        stack< Node * > st;

        Node * root = new Node(n) ;

        vector<WeightType> outgoing_minimum(n+1), incoming_minimum(n+1) ;
        for(int i=1; i<=n; i++)
            incoming_minimum[i]=outgoing_minimum[i]=INF;
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(i==j)
                    continue;
                outgoing_minimum[i] = min(outgoing_minimum[i], adj[i][j]);
                incoming_minimum[j] = min(incoming_minimum[j], adj[i][j]);
            }
        }

        for(int i=1; i<=n; i++)
            root->bound_x_2 += outgoing_minimum[i] + incoming_minimum[i];


        st.push(root);

        WeightType current_minimum_x_2 = INF;

//        DBG(current_minimum_x_2);

        while(!st.empty())
        {

            Node * x = st.top();
            st.pop();

//            DBG(x->present_node);
//            DBG(x->visited);
//            for(int i=1;i<=n;i++)
//                cout<<x->visited[i]<<" ";
//            NL;
//            DBG(current_minimum_x_2/2);
//            DBG(x->bound_x_2/2);
//            NL;

            if(current_minimum_x_2 < x->bound_x_2 )
                continue;

            bool have_branch = 0;
            for(int i=n; i>=2; i--)
            {
                if(x->visited[i] == 0)
                {
                    have_branch = 1;

                    Node * y = new Node(n);
                    memcpy(y->visited, x->visited, sizeof(bool) * (n+1));   /// dest , source , size (byte)
                    y->visited[i] = 1;
                    y->present_node = i;
                    y->bound_x_2 = x->bound_x_2 -  outgoing_minimum[x->present_node] - incoming_minimum[i]  + adj[x->present_node][i] * 2 ;

                    st.push(y);
                }
            }
            if(!have_branch)
            {
                x->bound_x_2 += -outgoing_minimum[x->present_node] -incoming_minimum[1] + adj[x->present_node][1] * 2;

                current_minimum_x_2 = min(current_minimum_x_2, x->bound_x_2);
            }

        }

        return current_minimum_x_2/2;

    }




    WeightType bnb_recursion()
    {
        vector<WeightType> outgoing_minimum(n+1), incoming_minimum(n+1) ;
        for(int i=1; i<=n; i++)
            incoming_minimum[i]=outgoing_minimum[i]=INF;
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(i==j)
                    continue;
                outgoing_minimum[i] = min(outgoing_minimum[i], adj[i][j]);
                incoming_minimum[j] = min(incoming_minimum[j], adj[i][j]);
            }
        }

        WeightType current_minimum_x_2 =  INF;

        bool*  visited = new bool [n+1];

        for(int i=2; i<=n; i++)
            visited[i] = 0;
        visited[1] =1;

        WeightType  bound_x_2 = 0;
        for(int i=1; i<=n; i++)
            bound_x_2+=incoming_minimum[i] + outgoing_minimum[i];

        bnb_recursion_util(1,visited, bound_x_2, current_minimum_x_2,outgoing_minimum,incoming_minimum);
        delete []visited;
        return current_minimum_x_2/2;

    }

    void bnb_recursion_util(int present_node, bool * visited, WeightType bound_x_2, WeightType  & current_minimum_x_2, vector<WeightType> &outgoing_minimum,vector<WeightType> &incoming_minimum)
    {
        if(current_minimum_x_2 < bound_x_2)
            return ;
        bool have_branch = 0;
        for(int i=2; i<=n; i++)
        {
            if(visited[i] == 0)
            {
                have_branch = 1;

                visited[i] =1;

                WeightType child_bound_x_2 = bound_x_2 -  outgoing_minimum[present_node] - incoming_minimum[i]  + adj[present_node][i] * 2 ;

                bnb_recursion_util(i,visited , bound_x_2 , current_minimum_x_2 , outgoing_minimum , incoming_minimum);

                visited[i] = 0;
            }
        }
        if(!have_branch)
        {
            bound_x_2 += -outgoing_minimum[present_node] -incoming_minimum[1] + adj[present_node][1] * 2;

            current_minimum_x_2 = min(current_minimum_x_2, bound_x_2);
        }

    }




};


#endif // TSP_ADDED
