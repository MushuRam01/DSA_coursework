#include <stdio.h>
#include <stdlib.h>
//storing graphs 
struct trQNode{
    int vertex;
    int status; // the status or color is not being used in this implementation.. insted we use a "visited" array for O(1) lookups
    struct trQNode* next;
};

void main(){
    printf("graphs for dsa \n");
    printf("BFS traversal of the graph: \n");
    //assume the following given graph (claude sonnet 4 generated test case)
    int graph[10][10] = {
    {0,1,0,1,1,0,0,1,0,1},  // 0 connects to: 1,3,4,7,9
    {1,0,1,0,1,1,0,0,1,0},  // 1 connects to: 0,2,4,5,8
    {0,1,0,1,0,1,1,0,0,1},  // 2 connects to: 1,3,5,6,9
    {1,0,1,0,0,0,1,1,1,0},  // 3 connects to: 0,2,6,7,8
    {1,1,0,0,0,1,0,0,1,1},  // 4 connects to: 0,1,5,8,9
    {0,1,1,0,1,0,1,1,0,0},  // 5 connects to: 1,2,4,6,7
    {0,0,1,1,0,1,1,1,1,0},  // 6 connects to: 2,3,5,7,8
    {1,0,0,1,0,1,1,0,0,1},  // 7 connects to: 0,3,5,6,9
    {0,1,0,1,1,0,1,0,0,1},  // 8 connects to: 1,3,4,6,9
    {1,0,1,0,1,0,0,1,1,0}   // 9 connects to: 0,2,4,7,8
    };

    BFS_Traversal(10, graph);

}


int exists_in_queue(struct trQNode* head, int value){ // not in use as i am checking using visited array
    struct trQNode* current = head;
    while(current != NULL){
        if(current->vertex == value){
            return 1;
        }
        current = current -> next ; // found

    }
    return 0 ; // notfound
}


void enque(struct trQNode** head, struct trQNode** tail, int value){
    struct trQNode* new_node = malloc (sizeof(struct trQNode));
    new_node->vertex = value;
    new_node->next=NULL;
    new_node->status= 0 ;

    if(*tail != NULL){
        (*tail)->next = new_node;
        *tail=new_node;
    }
    else{
        *head=new_node;
        *tail=new_node;
    }
}

void deque(struct trQNode** head, struct trQNode** tail){
    if(*head == NULL){
        printf("empty queue");
        return;
    }
    
    struct trQNode* to_remove= *head; // temporatu assign old head so we dont loose it in the memory
    *head = (*head)->next; // shift the head to next

    if(*head==NULL){ // if new head is null point tail to null also (single element list)
        *tail = NULL;

    }

    free(to_remove); // free the space
}




void BFS_Traversal (int n, int graph[n][n]){
    // Initialize head and tail pointers for the explore queue
    struct trQNode* explore_head = NULL;
    struct trQNode* curr_val = explore_head; // i dont hink i am ever using this variable 
    struct trQNode* explore_tail = explore_head;
   
    int visited[n] ;
    for (int i = 0; i<n ;i++){
        visited[i]= -1;
    }

    //stary BFS from vertex 0
    enque(&explore_head, &explore_tail, 0);
    visited[0]=1;


    //main BFS loop
    while( explore_head !=NULL ){
        //get current vertex to process
        int current_vertex = explore_head->vertex;

        //process current vertex (print)
        printf("%d ", current_vertex);

        //remove current vertex from queue 
        deque(&explore_head,&explore_tail);

        //add all unvisited neighbours of current_vertex
        for(int j=0; j<n;j++){
            if(graph[current_vertex][j]!= 0){//edge exists

                if (visited[j]==-1){// not visited
                    enque(&explore_head, &explore_tail, j);
                    visited[j] = 1 ;      // Mark as visited
                }
            }
        }    
    }
}