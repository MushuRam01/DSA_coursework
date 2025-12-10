#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "heap.c" // complies with this files so i can call funtion from ther

int correct_queryfile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }   

    FILE* output = fopen("queries_corrected.txt", "w");
    if (output == NULL) {
        printf("Error opening output file: queries_corrected.txt\n");
        fclose(file);
        return 0;
    }

    char line[256];
    
    while (fgets(line, sizeof(line), file) != NULL) {
        int i = 0;
        
        // Convert characters to lowercase until space
        while (line[i] != '\0' && line[i] != ' ') {
            fputc(tolower(line[i]), output); // using builtin function from ctype.h
            i++;
        }
        
        // Copy the rest of the line as is (including the space and everything after)
        while (line[i] != '\0') {
            fputc(line[i], output);
            i++;
        }
    }
    
    fclose(file);
    fclose(output);
    printf("Query file corrected successfully\n");
    return 1;
}

int final_parse(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);   
        return 0;
    }
    
    FILE* output = fopen("final_output.txt", "w");
    if (output == NULL) {
        printf("Error opening output file: final_output.txt\n");
        fclose(file);
        return 0;
    }
    
    fprintf(output, "Outputs of queries:\n");
    
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        char command[50];
        sscanf(line, "%s", command);
        
        if (strcmp(command, "build_heap") == 0) {
            build_heap(NULL);
            fprintf(output, "BUILD_HEAP → SUCCESS\n");
        }
        else if (strcmp(command, "insert") == 0) {
            char event_id[32];
            int key1, key2;
            sscanf(line, "%s %s %d %d", command, event_id, &key1, &key2);
            struct HeapNode new_node;
            strcpy(new_node.event_id, event_id);
            new_node.key1 = key1;
            new_node.key2 = key2;
            insert(heap, new_node);
            fprintf(output, "INSERT_KEY → SUCCESS\n");
        }
        else if (strcmp(command, "extract_min") == 0) {
            struct HeapNode min = extract_min(heap);
            if (strlen(min.event_id) > 0) {
                fprintf(output, "EXTRACT_MIN → %s %d %d\n", min.event_id, min.key1, min.key2);
            } else {
                fprintf(output, "EXTRACT_MIN → HEAP EMPTY\n");
            }
        }
        else if (strcmp(command, "decrease_key") == 0) {
            char event_id[32];
            int new_key1, new_key2;
            sscanf(line, "%s %s %d %d", command, event_id, &new_key1, &new_key2);
            decrease_key(heap, event_id, new_key1, new_key2);
            fprintf(output, "DECREASE_KEY → SUCCESS\n");
        }
        else if (strcmp(command, "print_heap_array") == 0) {
            fprintf(output, "PRINT_HEAP_ARRAY → SUCCESS\n");
            // Print heap elements in heap order
            for (int i = 0; i < heap_size; i++) {
                fprintf(output, "%s", heap[i].event_id);
                if (i < heap_size - 1) {
                    fprintf(output, ", ");
                }
            }
            if (heap_size > 0) {
                fprintf(output, "\n");
            }
        }
    }
    
    fclose(file);
    fclose(output);
    printf("Queries processed successfully\n");
    return 1;
}

int main() {
    
    if(correct_queryfile("../queries.txt") == 0) {
        correct_queryfile("../queries.txt.txt");
    }
    
    //correct_queryfile("../queries.txt.txt");

    final_parse("queries_corrected.txt");
    return 0;
}