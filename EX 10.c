#include<stdio.h>
#include<limits.h>
#define V 5

int minKey(int key[],int mstSet[]){
    int min=INT_MAX,minIndex;
    for(int v=0;v<V;v++)
        if(mstSet[v]==0 && key[v]<min) min=key[v],minIndex=v;
    return minIndex;
}

void primMST(int graph[V][V]){
    int parent[V],key[V],mstSet[V] ={0};

    for(int i=0;i<V;i++) key[i]=INT_MAX;
    key[0]=0;
    parent[0]=-1;

    for(int count=0;count<V-1;count++){
        int u=minKey(key,mstSet);
        mstSet[u]=1;

        for(int v=0;v<V;v++)
            if(graph[u][v] && mstSet[v]==0 && graph[u][v]<key[v])
                parent[v]=u,key[v]=graph[u][v];
    }

    printf("Edge \tWeight\n");
    for(int i=1;i<V;i++) printf("%d-%d \t%d \n",parent[i],i,graph[i][parent[i]]);
}

int main(){
    int graph[V][V]={
       {0,2,0,6,0},
       {2,0,3,8,5},
       {0,3,0,0,7},
       {6,8,0,0,9},
       {0,5,7,9,0}};
        
        primMST(graph);
        return 0;

}


Sample output:

Edge    Weight
0 - 1    2
1 - 2    3
0 - 3    6
1 - 4    5


Scenario 2: A network engineer is tasked with setting up cables between multiple offices 
within a building, aiming to minimize the total length of cable used. The office locations 
are modeled as a graph, and the engineer needs to implement a minimum spanning tree algorithm.


#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define INF INT_MAX

int findMinKey(int* key,int* inMST,int numVertices){
    int min=INF,minIndex;
    for(int v=0;v<numVertices;v++){
        if(inMST[v]==0 && key[v]<min){
            min=key[v];
            minIndex=v;
        }
    }
    return minIndex;
}


void printMST(int* parent,int** graph,int numVertices){
    printf("Edge \tWeight\n");
    for(int i=1;i<numVertices;i++){
        printf("%d - %d \t%d\n",parent[i],i,graph[i][parent[i]]);
    }
}

void primMST(int** graph,int numVertices){
    int* parent=(int*)malloc(numVertices*sizeof(int));
    int* key=(int*)malloc(numVertices*sizeof(int));
    int* inMST=(int*)calloc(numVertices,sizeof(int));

    for(int i=0;i<numVertices;i++){
        key[i]=INF;
    }
    key[0]=0; // Start from the first vertex
    parent[0]=-1;// First node is the root of the MST

    for(int count=0;count<numVertices - 1;count++){
        int u=findMinKey(key,inMST,numVertices);
        inMST[u]=1;

        for(int v=0;v<numVertices;v++){
            if(graph[u][v] && inMST[v]==0 && graph[u][v]<key[v]){
                parent[v]=u;
                key[v]=graph[u][v];
            }
        }
    }

    printMST(parent,graph,numVertices);

    free(parent);
    free(key);
    free(inMST);
}

int main(){
    int numVertices;
    printf("Enter the number of offices: ");
    scanf("%d",&numVertices);

    int** graph=(int**)malloc(numVertices*sizeof(int*));
    for(int i=0;i<numVertices;i++){
        graph[i]=(int*)malloc(numVertices*sizeof(int));
        printf("Enter weights for office %d: ",i);
        for(int j=0;j<numVertices;j++){
            scanf("%d",&graph[i][j]);
            if(i != j && graph[i][j]==0){
                graph[i][j]=INF;// No edge
            }
        }
    }

    printf("Minimum Spanning Tree:\n");
    primMST(graph,numVertices);

    for(int i=0;i<numVertices;i++){
        free(graph[i]);
    }
    free(graph);

    return 0;
}



Sample output:

Enter the number of offices: 4
Enter weights for office 0: 0 10 20 0
Enter weights for office 1: 10 0 5 15
Enter weights for office 2: 20 5 0 30
Enter weights for office 3: 0 15 30 0
Minimum Spanning Tree:
Edge    Weight
0 - 1   10
1 - 2   5
1 - 3   15


Scenario 3: An electricity provider needs to set up power lines to connect 
multiple towns in a region. The goal is to minimize the total cost of laying 
down the power lines while ensuring all towns are connected. The towns and distances 
between them are represented as a graph, and the program should dynamically handle 
updates to the network.

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define INF INT_MAX

int findMinKey(int* key,int* inMST,int numVertices){
    int min=INF,minIndex;
    for(int v=0;v<numVertices;v++){
        if(inMST[v]==0 && key[v]<min){
            min=key[v];
            minIndex=v;
        }
    }
    return minIndex;
}

void printMST(int* parent,int** graph,int numVertices){
    printf("Edge \tWeight\n");
    for(int i=1;i<numVertices;i++){
        printf("%d - %d \t%d\n",parent[i],i,graph[i][parent[i]]);
    }
}

void primMST(int** graph,int numVertices){
    int* parent=(int*)malloc(numVertices*sizeof(int));
    int* key=(int*)malloc(numVertices*sizeof(int));
    int* inMST=(int*)calloc(numVertices,sizeof(int));

    for(int i=0;i<numVertices;i++){
        key[i]=INF;
    }
    key[0]=0; // Start from the first vertex
    parent[0]=-1;// First node is the root of the MST

    for(int count=0;count<numVertices - 1;count++){
        int u=findMinKey(key,inMST,numVertices);
        inMST[u]=1;

        for(int v=0;v<numVertices;v++){
            if(graph[u][v] && inMST[v]==0 && graph[u][v]<key[v]){
                parent[v]=u;
                key[v]=graph[u][v];
            }
        }
    }

    printMST(parent,graph,numVertices);

    free(parent);
    free(key);
    free(inMST);
}

void updateGraph(int*** graph,int* numVertices){
    int newVertex;
    printf("Enter new number of towns(vertices): ");
    scanf("%d",&newVertex);
    
    int oldVertices=*numVertices;
    *numVertices=newVertex;
    
    *graph=(int**)realloc(*graph,newVertex*sizeof(int*));
    for(int i=0;i<newVertex;i++){
       (*graph)[i]=(int*)realloc((*graph)[i],newVertex*sizeof(int));
        if(i >= oldVertices){
            for(int j=0;j<newVertex;j++){
               (*graph)[i][j]=INF;
            }
        }
    }

    for(int i=0;i<newVertex;i++){
        for(int j=oldVertices;j<newVertex;j++){
            printf("Enter weight of edge from %d to %d(0 if no edge): ",i,j);
            scanf("%d",&(*graph)[i][j]);
            if(i != j &&(*graph)[i][j]==0){
               (*graph)[i][j]=INF;
            }
           (*graph)[j][i]=(*graph)[i][j];
        }
    }
}

int main(){
    int numVertices;
    printf("Enter the number of towns: ");
    scanf("%d",&numVertices);

    int** graph=(int**)malloc(numVertices*sizeof(int*));
    for(int i=0;i<numVertices;i++){
        graph[i]=(int*)malloc(numVertices*sizeof(int));
        printf("Enter weights for town %d: ",i);
        for(int j=0;j<numVertices;j++){
            scanf("%d",&graph[i][j]);
            if(i != j && graph[i][j]==0){
                graph[i][j]=INF;
            }
        }
    }

    printf("Initial Minimum Spanning Tree:\n");
    primMST(graph,numVertices);

    char choice;
    printf("Do you want to update the network(add new towns/edges)?(y/n): ");
    scanf(" %c",&choice);
    if(choice=='y' || choice=='Y'){
        updateGraph(&graph,&numVertices);
        printf("Updated Minimum Spanning Tree:\n");
        primMST(graph,numVertices);
    }

    for(int i=0;i<numVertices;i++){
        free(graph[i]);
    }
    free(graph);

    return 0;
}


Sample output:

Enter the number of towns: 4
Enter weights for town 0: 0 8 0 0
Enter weights for town 1: 8 0 3 5
Enter weights for town 2: 0 3 0 7
Enter weights for town 3: 0 5 7 0

Initial Minimum Spanning Tree:
Edge    Weight
0 - 1   8
1 - 2   3
1 - 3   5

Do you want to update the network (add new towns/edges)? (y/n): y
Enter new number of towns (vertices): 5
Enter weight of edge from 0 to 4 (0 if no edge): 10
Enter weight of edge from 1 to 4 (0 if no edge): 0
Enter weight of edge from 2 to 4 (0 if no edge): 6
Enter weight of edge from 3 to 4 (0 if no edge): 9
Enter weight of edge from 4 to 4 (0 if no edge): 0

Updated Minimum Spanning Tree:
Edge    Weight
0 - 1   8
1 - 2   3
1 - 3   5
2 - 4   6
