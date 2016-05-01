#include<stdio.h>
#include<stdlib.h>
#define INF 9999
enum {WHITE,BLACK,GRAY};
// linked list data type for adjacency list
typedef struct node 
{
  int vertex,weight;
 struct node *next;

}  List ;

// each node of graph

typedef struct {
   List *link;
   int color,distance,parent;
}  Node;

// graph data type

typedef struct {
   Node nodes[100]; // Array of nodes
   int n_v; // number  of vertices
   int n_e; // number of edges
}  Graph;

// function to insert to linked list

void insert(List *link,int vertex,int weight){
// creating new node to insert
List *new=(List*) malloc(sizeof(List));
new->next= NULL ;
new ->  vertex = vertex ;
new -> weight = weight ;

// List won't be empty(since create function is used ) so iterating to end of list
List *cur=link;
while ( cur -> next != NULL )
  cur=cur->next;
// attaching new at end
cur -> next = new; 

}


Graph inputGraph()
{
    int i;
    Graph g;
    // filling first data in link, which is a sentinal element
    
    printf("Enter no of vertices \n");
    scanf("%d",&(g.n_v));

    for(i=0;i<g.n_v;i++)
    {
        g.nodes[i].link = (List*) malloc(sizeof(List));
        g.nodes[i].link -> next = NULL;
        g.nodes[i].link -> vertex = -1;
    }
    printf("Enter no of edges \n");
    scanf("%d",&(g.n_e));
    printf("Enter  %d edges each as from, to ( 0 indexed ) : \n",g.n_e );
    for(i=0;i<g.n_e;i++)
    {
      int x,y;
      scanf("%d%d",&x,&y);
      insert(g.nodes[x].link,y,1);
    }
    return g;
}


// Queue for bfs implementation
int queue[100],front=0,rear=-1;
// simple implementation, no overflow/underflow check
// so, it's assumed that isempty wll be checked before dequeing
void enque(int n)
{
  rear++;
  queue[rear]=n;
}
int deque()
{
  front++;
  return queue[front-1];
}
int isempty(){
  return front>rear;
}
void bfs(Graph *g)
{
  printf("Enter Starting node : ");
  int s,u,i;
  scanf("%d",&s);
  printf("\tBFS : \n\n| Vertex | Parent | Distance |\n");
// Algorithm  exactly as in clrs textbook
  for(i=0; i < g -> n_v ; i++){
    g -> nodes[i].color = WHITE;
    g -> nodes[i].distance = INF;
    g -> nodes[i].parent = -1;
  }
  g->nodes[s].color=GRAY;
  g->nodes[s].distance=0;
  
  enque(s);
  while(!isempty())
  {
    u=deque();
    List *cur= g -> nodes[u].link -> next; // first one is sentinel, so next
    while(cur != NULL)
    {
      if(g -> nodes[cur -> vertex].color == WHITE)
      {
        g -> nodes[cur -> vertex].color = GRAY;
        g -> nodes[cur -> vertex].distance = g -> nodes[u].distance + 1;
        g -> nodes[cur -> vertex].parent = u;
        enque(cur -> vertex);
      }
      cur=cur->next;
    }
    g -> nodes[u].color = BLACK;
    printf("| %6d | %6d | %8d |\n",u,g ->nodes[u].parent,g->nodes[u].distance );
  }
   
}

 int main(){
  int i,j;
  Graph g=inputGraph();
  bfs(&g);
} 