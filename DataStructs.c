#include <stdio.h>
#include <stdlib.h>
# define MAX 100
//impliment basic data structures in c 
//implimment an array and work out opinters 




// stacks and queues 


// linked lists

struct node{
    int value;
    struct node* next ;

};
typedef struct node node_t; // renaming struct node to node_t

void printlist(node_t *head){  // to print a linked list 
    node_t *temporary = head;
    while (temporary != NULL){
        printf("%d-",temporary->value);
        temporary = temporary->next;

    }
}

node_t *create_new_node(int value){  // creates new node and returns its pointer  
    node_t *result = malloc (sizeof(node_t));
    result -> value = value ;
    result->next = NULL;
    return result;
}



node_t *add_head(node_t *oldhead, int value){
    
    node_t *head;

    head = create_new_node(value);
    
    head->next = oldhead;
    return head;
}



int main(){


    int x=10;
    int *p; // contains garbage memory address
   // *p=&x; // incorrect as you are wrioting to a garbage address
    p=&x; // correct as you are writing the address of x to p
    printf("%d", *p);
    printf("\n");
    printf("%p", p);
    printf("\n");
    printf("the adress fo x is %p", &x);
    printf("\n");
    printf("----NEW CODE STARTS HERE----");
    printf("\n");





   node_t *head;
   node_t *tmp;
   tmp = create_new_node(1);
   head = tmp;

   tmp = create_new_node(2);
   tmp -> next = head;
   head = tmp;

   tmp = create_new_node(3);
   tmp -> next = head;
    head = tmp;



    printlist(head);


    return 0;
}


