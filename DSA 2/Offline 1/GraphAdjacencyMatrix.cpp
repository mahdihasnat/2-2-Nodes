#include<iostream>
#include<stdlib.h>

#include "GraphAdjacencyList.h"

int main(void)
{
    int n;
    int choice;
    bool dir=false;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    dir = choice == 1;
    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("Enter Choice\n\
                1. Add edge. \n\
                2. Remove edge\n\
                3. Check edge\n\
                4. Count In Degree\n\
                5. Count Out Degree\n\
                6. Print Adjacent Vertices \n\
                7. Check Common Adjacency \n\
                8. Get Distance from u to v\n\
                9. Print Graph \n\
                10. Run Bfs\n\
                11. Run Dfs\n\
                12. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            
            printf("%d  %d  edge %s added\n" ,u,v , g.addEdge(u, v) ? "" : "not");
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            g.removeEdge(u,v);
            printf("%d %d edge removed\n",u,v);
        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            cout<<"There is "<<(g.isEdge(u,v)?"a":"no")<<" edge from "<<u<<" to "<<v<<"\n";
        }
        else if(ch==4)
        {
            int u;
            cin>>u;
            cout<<"in degree of "<<u<<" is : "<<g.getInDegree(u)<<"\n";
        }
        else if(ch==5)
        {
            int u;
            cin>>u;
            cout<<"out degree of "<<u<<" is : "<<g.getOutDegree(u)<<"\n";
        }
        else if(ch==6)
        {
            int u;
            cin>>u;
            g.printAdjVertices(u);
        }
        else if(ch==7)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            cout<<u<<" "<<v<<(g.hasCommonAdjacent(u,v)? "": " don't")<<" have common adjacent vertices\n";
        }
        else if(ch==8)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            int dist = g.getDist(u,v);
            cout<<"Distance between "<<u<<" and "<<v<<" : "<<dist<<"\n";
        }
        else if(ch==9)
        {
            g.printGraph();
        }
        else if(ch==10)
        {
            int u;
            scanf("%d",&u);
            g.bfs(u);
        }
        else if(ch==11)
        {

            int u;
            scanf("%d",&u);
            g.dfs(u);
        }
        else if(ch==12)
        {
            break;
        }
    }

}
