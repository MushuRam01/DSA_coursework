#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000

struct HeapNode {
    int key1; // primary priority
    int key2; // secondary priority
    char event_id[32]; //alphanumeric event ID, uppercase
};

struct HeapNode heap[MAXN];
int heap_size = 0;

int read_heap_data(const char*  filename, struct HeapNode** nodes, int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }
    
   //count number of lines in the doc
    char line[256];
    *count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        (*count)++;
    }
    
    // Allocate memory for array of heap nodes
    *nodes = (struct HeapNode*)malloc(*count * sizeof(struct HeapNode)); // we counted to alloc memory correctly
    if (*nodes == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return 0;
    }
    
    
    rewind(file); // rst file ptr to start of doc
    
    // Read each line and store in heap node
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL && i < *count) {
        //  line format will be of type E1234,345,677
        char *event_id_str = strtok(line, ",");  //using delimiter logic to split the line into parts.. essentially the file is a csv now
        char *key1_str = strtok(NULL, ","); // neat little trick i learnt from stackoverflow and used ai to understand how to splitthe string
        char *key2_str = strtok(NULL, ",\n");
        
        if (event_id_str != NULL && key1_str != NULL && key2_str != NULL) {
            // if it is valid then Store in heap node
            //stranger over discord helped me with this part 
            strncpy((*nodes)[i].event_id, event_id_str, 31); // we use 31 to leave space for null terminator,, adnensure t hat t doe snot overflow beyond 30
            (*nodes)[i].event_id[31] = '\0';
            (*nodes)[i].key1 = atoi(key1_str); //converts from str to int for easy comparisn 
            (*nodes)[i].key2 = atoi(key2_str);
            i++;
        }
    }
    
    fclose(file);
    printf("Successfully read %d heap nodes from file\n", *count);
    return 1;
}


int compare_nodes(struct HeapNode* a, struct HeapNode* b) {// compares 2 nodes based on priority rules as given in the assignmet
    //key1 < key1
    if (a->key1 < b->key1) {// A has higher priority
        return -1;          // -1 means choose a
    }  
    if (a->key1 > b->key1) {
        return 1;           // 1 means choose b
    }
    
    // key2 comparison when key1 is same
    if (a->key2 < b->key2) {
        return -1;  
    }
    if (a->key2 > b->key2) {
        return 1;   
    }
    
    //  keys -> compare id lexicographically... found this funtion on reddit 
    return strcmp(a->event_id, b->event_id);  // returns negative if A comes before B
}

//  maintain heap property by moving node down when conflict
void heapify_down(struct HeapNode* heap, int heap_size, int index) {
    int smallest = index;
    int left = 2 * index + 1;   // left child formula
    int right = 2 * index + 2;  // right child formula
    
   //l check
    if (left < heap_size && compare_nodes(&heap[left], &heap[smallest]) < 0) {
        smallest = left; // sset who is da smallest
    }
    
    //r check
    if (right < heap_size && compare_nodes(&heap[right], &heap[smallest]) < 0) {
        smallest = right;
    }
    
    // if we need to swap then do it
    if (smallest != index) {
        // swp operation 
        struct HeapNode temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        
        
        heapify_down(heap, heap_size, smallest); // call again recursively
    }
}

struct HeapNode extract_min(struct HeapNode *A){ 
    if (heap_size == 0) { // empty heap edge case
        struct HeapNode empty;
        strcpy(empty.event_id, "");
        empty.key1 = 0;
        empty.key2 = 0;
        printf("Heap is empty\n");
        return empty;
    }
    
    struct HeapNode min = heap[0];
    heap[0] = heap[heap_size - 1];
    heap_size--;
    heapify_down(heap, heap_size, 0);
    return min;
}

void print_heap_array(struct HeapNode *A, FILE* fp) {
    for (int i = 0; i < heap_size; i++) {
        fprintf(fp, "%s,%d,%d\n", heap[i].event_id, heap[i].key1, heap[i].key2); 
    }
}

// function to move node up to fix heap property
void heapify_up(struct HeapNode* heap, int index) {
    if (index == 0) return; // already at root
    
    int parent = (index - 1) / 2; // parent formula
    
    // check if current node has higher priority than parent
    if (compare_nodes(&heap[index], &heap[parent]) < 0) {
        // swap
        struct HeapNode temp = heap[index];
        heap[index] = heap[parent];
        heap[parent] = temp;
        
        // recursive call
        heapify_up(heap, parent);
    }
}

void insert(struct HeapNode *A, struct HeapNode x) {// insert into array adn keep doing sift/heapifyup till resolved
    if (heap_size >= MAXN) {
        printf("Heap overflow\n");
        return;
    }
    
    heap[heap_size] = x;
    heapify_up(heap, heap_size); 
    heap_size++;
}

void decrease_key(struct HeapNode *A, char event_id[], int new_key1, int new_key2) { //reassign vale for given node then run heapyfy up and down.. it will edal with it
    int index = -1;
    for (int i = 0; i < heap_size; i++) {
        if (strcmp(heap[i].event_id, event_id) == 0) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Event ID not found in heap\n");
        return;
    }
    
    heap[index].key1 = new_key1;
    heap[index].key2 = new_key2;
    
    //run both.. it will resolve itself
    heapify_up(heap, index);
    heapify_down(heap, heap_size, index);
}

void build_heap(FILE* fp) {
    struct HeapNode* nodes;
    int count;
    
    if (read_heap_data("cleaned_events.txt", &nodes, &count) == 0) {
        printf("Failed to read heap data\n");
        return;
    }
    
    // Copy data to global heap array
    heap_size = count;
    for (int i = 0; i < count; i++) {
        heap[i] = nodes[i];
    }
    
    // Build heap from bottom to top
    for (int i = (heap_size / 2) - 1; i >= 0; i--) {
        heapify_down(heap, heap_size, i);
    }
    
    free(nodes);
    printf("Heap built successfully with %d nodes\n", heap_size);
}


/*
int main() {
    // For testing purposes - build heap from cleaned_events.txt
    FILE* fp = fopen("heap_output.txt", "w");
    if (fp == NULL) {
        printf("Error opening output file\n");
        return 1;
    }
    
    build_heap(fp);
    
    fclose(fp);
    return 0;
}
*/