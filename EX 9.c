#include<stdio.h>
#include<limits.h>

#define V 5  

int minDistance(int dist[],int visited[]){
    int min=INT_MAX,minIndex;
    for(int v=0;v<V;v++)
        if(!visited[v] && dist[v]<= min)
            min=dist[v],minIndex=v;
    return minIndex;
}

void dijkstra(int graph[V][V],int src){
    int dist[V],visited[V] ={0};

    for(int i=0;i<V;i++) dist[i]=INT_MAX;
    dist[src]=0;

    for(int count=0;count<V-1;count++){
        int u=minDistance(dist,visited);
        visited[u]=1;

        for(int v=0;v<V;v++)
            if(!visited[v] && graph[u][v] && dist[u]+graph[u][v]<dist[v])
                dist[v]=dist[u]+graph[u][v];
    }

    printf("Vertex \t Distance from Source\n");
    for(int i=0;i<V;i++) printf("%d \t\t %d\n",i,dist[i]);
}

int main(){
    int graph[V][V] ={
       {0,10,0,0,5},
       {10,0,1,0,2},
       {0,1,0,4,0},
       {0,0,4,0,3},
       {5,2,0,3,0}};

    dijkstra(graph,0);
    return 0;
}


Sample output:

Vertex   Distance from Source
0        0
1        7
2        8
3        9
4        5


Scenario 2: A game character needs to find the shortest path from its 
current position to a goal location on a grid. The game uses pointers 
to represent the grid dynamically, and the algorithm should consider 
obstacles along the path


#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100
#define INF 99999

typedef struct{
    int x,y;
    int distance;
} Node;

int directions[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

int isValid(int x,int y,int rows,int cols,int** grid,int** visited){
    return(x>=0 && x < rows && y>=0 && y< cols && grid[x][y]==0 && !visited[x][y]);
}

int findShortestPath(int** grid,int rows,int cols,int startX,int startY,int goalX,int goalY){
    int** visited=(int**)malloc(rows*sizeof(int*));
    for(int i=0;i< rows;i++){
        visited[i] =(int*)calloc(cols,sizeof(int));
    }

    Node queue[MAX_SIZE*MAX_SIZE];
    int front=0,rear=0;
    
    queue[rear++] =(Node){startX,startY,0};
    visited[startX][startY]=1;

    while(front< rear){
        Node current=queue[front++];
        
        if(current.x==goalX && current.y==goalY){
            for(int i=0;i< rows;i++) free(visited[i]);
            free(visited);
            return current.distance;
        }

        for(int i=0;i< 4;i++){
            int newX=current.x + directions[i][0];
            int newY=current.y + directions[i][1];

            if(isValid(newX,newY,rows,cols,grid,visited)){
                visited[newX][newY]=1;
                queue[rear++] =(Node){newX,newY,current.distance + 1};
            }
        }
    }

    for(int i=0;i< rows;i++) free(visited[i]);
    free(visited);
    return -1;
}

int main(){
    int rows,cols;
    printf("Enter number of rows and columns: ");
    scanf("%d %d",&rows,&cols);

    int** grid =(int**)malloc(rows*sizeof(int*));
    for(int i=0;i< rows;i++){
        grid[i] =(int*)malloc(cols*sizeof(int));
    }

    printf("Enter the grid(0 for open space,1 for obstacle):\n");
    for(int i=0;i< rows;i++){
        for(int j=0;j< cols;j++){
            scanf("%d",&grid[i][j]);
        }
    }

    int startX,startY,goalX,goalY;
    printf("Enter start position(x y): ");
    scanf("%d %d",&startX,&startY);
    printf("Enter goal position(x y): ");
    scanf("%d %d",&goalX,&goalY);

    int result=findShortestPath(grid,rows,cols,startX,startY,goalX,goalY);
    if(result != -1){
        printf("Shortest path length: %d\n",result);
    } else{
        printf("No path found.\n");
    }

    for(int i=0;i< rows;i++){
        free(grid[i]);
    }
    free(grid);
    return 0;
}



Sample output:

Enter number of rows and columns: 5 5
Enter the grid (0 for open space, 1 for obstacle):
0 0 1 0 0
0 1 1 0 0
0 0 0 0 0
1 1 0 1 0
0 0 0 1 0
Enter start position (x y): 0 0
Enter goal position (x y): 4 4
Shortest path length: 8




Scenario 3: A logistics company needs to calculate the shortest route for a 
fleet of trucks to travel between multiple warehouses and client locations. 
The routes are represented as a weighted graph, and the program should allow 
dynamic updates as new destinations are added.


#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define INF INT_MAX

int findMinDistance(int* distance,int* visited,int numNodes){
    int min=INF,minIndex;
    for(int i=0;i< numNodes;i++){
        if(!visited[i] && distance[i]<= min){
            min=distance[i];
            minIndex=i;
        }
    }
    return minIndex;
}

void dijkstra(int** graph,int numNodes,int startNode){
    int* distance =(int*)malloc(numNodes*sizeof(int));
    int* visited =(int*)calloc(numNodes,sizeof(int));

    for(int i=0;i< numNodes;i++){
        distance[i]=INF;
    }
    distance[startNode]=0;

    for(int count=0;count< numNodes - 1;count++){
        int u=findMinDistance(distance,visited,numNodes);
        visited[u]=1;

        for(int v=0;v< numNodes;v++){
            if(!visited[v] && graph[u][v] && distance[u] != INF && distance[u] + graph[u][v]< distance[v]){
                distance[v]=distance[u] + graph[u][v];
            }
        }
    }

    printf("Node\tDistance from Source\n");
    for(int i=0;i< numNodes;i++){
        if(distance[i]==INF){
            printf("%d\tINF\n",i);
        } else{
            printf("%d\t%d\n",i,distance[i]);
        }
    }

    free(distance);
    free(visited);
}

int main(){
    int numNodes;
    printf("Enter the number of nodes(warehouses and clients): ");
    scanf("%d",&numNodes);

    int** graph =(int**)malloc(numNodes*sizeof(int*));
    for(int i=0;i< numNodes;i++){
        graph[i] =(int*)malloc(numNodes*sizeof(int));
        for(int j=0;j< numNodes;j++){
            printf("Enter weight of edge from %d to %d(0 if no edge): ",i,j);
            scanf("%d",&graph[i][j]);
            if(i != j && graph[i][j]==0){
                graph[i][j]=INF;// No edge
            }
        }
    }

    int startNode;
    printf("Enter the starting node: ");
    scanf("%d",&startNode);

    dijkstra(graph,numNodes,startNode);

    for(int i=0;i< numNodes;i++){
        free(graph[i]);
    }
    free(graph);

    return 0;
}

Sample output:

Enter the number of nodes (warehouses and clients): 4
Enter weight of edge from 0 to 0: 0
Enter weight of edge from 0 to 1: 10
Enter weight of edge from 0 to 2: 15
Enter weight of edge from 0 to 3: 0
Enter weight of edge from 1 to 0: 10
Enter weight of edge from 1 to 1: 0
Enter weight of edge from 1 to 2: 35
Enter weight of edge from 1 to 3: 25
Enter weight of edge from 2 to 0: 15
Enter weight of edge from 2 to 1: 35
Enter weight of edge from 2 to 2: 0
Enter weight of edge from 2 to 3: 30
Enter weight of edge from 3 to 0: 0
Enter weight of edge from 3 to 1: 25
Enter weight of edge from 3 to 2: 30
Enter weight of edge from 3 to 3: 0
Enter the starting node: 0
Node    Distance from Source
0       0
1       10
2       15
3       35
