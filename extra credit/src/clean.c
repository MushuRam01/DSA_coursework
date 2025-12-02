#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper function to check if string is valid integer
int is_integer(char* str) {
    if (str == NULL || strlen(str) == 0) return 0;
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int read_write(char* filename) {
    FILE *ptr ; //creating file porinter name ptr   
    char ch;

    FILE *outptr;
    outptr = fopen("merged.txt", "a"); // writing to output file

    ptr = fopen(filename,"r") ; //opening file

    if (ptr == NULL) {                        //check if file exists
        printf("file not fond\n");
        return 0;
    }

    while( (ch=fgetc(ptr)) != EOF ) {
        printf("%c", ch);
        fputc(ch, outptr);
    }
   
    
    fputc('\n', outptr); // newlin addd aftre ednd of each file
   
    fclose(ptr);
    fclose(outptr);
    return 1;
}

int remove_emptyid(char* filename){
    FILE *ptr;
    FILE *outptr;
    char line[1000];
    
    ptr = fopen(filename, "r");
    outptr = fopen("id_filtered.txt", "w");
    
    if (ptr == NULL) {
        printf("file not found\n");
        return 0;
    }
    
    while (fgets(line, sizeof(line), ptr) != NULL) {
        // Check if line contains id= followed by something
        char *id_pos = strstr(line, "id="); // search substr of id
        if (id_pos != NULL) {
            id_pos += 3; // skip "id="
            // Check if there's actual content after id= (not empty, comma, or newline)
            if (*id_pos != ',' && *id_pos != '\n' && *id_pos != '\0' && *id_pos != '\r') {
                // Make sure it's not just whitespace
                char *check = id_pos;
                while (*check == ' ' || *check == '\t') check++; // skip whitespace
                if (*check != ',' && *check != '\n' && *check != '\0' && *check != '\r') {
                    fputs(line, outptr);
                }
            }
        }
    }
    
    fclose(ptr);
    fclose(outptr);
    return 1;
}



int keys_corrected(char* filename){

    FILE *ptr;
    FILE *outptr;
    char line[1000];
    char key1_val[100];
    char key2_val[100];
    
    ptr = fopen(filename, "r");
    outptr = fopen("keys_corrected.txt", "w");
    
    if (ptr == NULL) {
        printf("file not found\n");
        return 0;
    }

    while(fgets(line, sizeof(line), ptr) != NULL){
        //check if line contains key1= followed by an integer
        char *key1_pos = strstr(line, "key1=");
        if(key1_pos == NULL){
        strcpy(key1_val, "9999"); // Use strcpy to copy string to array
        }

        else{          
            
            char *start = key1_pos + 5; // skip "key1=" 
            char *end = start;
        
            // Find the end of the value (comma, newline, or end of string)
            while(*end != ',' && *end != '\n' && *end != '\0') {
                end++;
            }
        
        
            int len = end - start; // length of stuff after key 1
            strncpy(key1_val, start, len); // copy exactly n charachters(len) from start to key1_val and saves to key1_val array
            key1_val[len] = '\0'; // null terminate (i pickerd thos from the glorious internet) removes grabage avles nd only keeps valid stuff
        
            if(is_integer(key1_val) == 0){
                strcpy(key1_val, "9999");
            }
            if(is_integer(key1_val) == 1){
                //valid integer do nothing
            }
        }

        // Process key2 similarly
         //check if line contains key2= followed by an integer
        char *key2_pos = strstr(line, "key2=");
        if(key2_pos == NULL){
        strcpy(key2_val, "9999"); // Use strcpy to copy string to array
        }

        else{          
            
            char *start2 = key2_pos + 5; // skip "key2=" 
            char *end2 = start2;
        
            // Find the end of the value (comma, newline, or end of string)
            while(*end2 != ',' && *end2 != '\n' && *end2 != '\0' && *end2 != '\r') {
                end2++;
            }
        
        
            int len = end2 - start2; // length of stuff after key 2
            strncpy(key2_val, start2, len); // copy exactly n charachters(len) from start2 to key2_val array
            key2_val[len] = '\0'; // null terminate
        
            if(is_integer(key2_val) == 0){
                strcpy(key2_val, "9999");
            }
            if(is_integer(key2_val) == 1){
                //valid integer do nothing
            }
        }
        //creating master str to write to file
        char output_line[1000];
        //extract idval
        char id_val[100];
        char *id_pos = strstr(line, "id=");
        char *id_start = id_pos + 3; // skip "id="
        char *id_end = id_start;
        while(*id_end != ',' && *id_end != '\n' && *id_end != '\0' && *id_end != '\r') {
            id_end++;  
        }
        int len = id_end - id_start;
        strncpy(id_val, id_start, len);
        id_val[len] = '\0';

        //bild output line
        //sprintf(output_line, "id=%s,key1=%s,key2=%s\n", id_val, key1_val, key2_val);
        sprintf(output_line, "key1=%s,key2=%s,id=%s\n", key1_val, key2_val, id_val); // required orded.. pry this does not conflict with other funtions
        fputs(output_line, outptr);
        
    }

    fclose(ptr);
    fclose(outptr);
    return 1;
}

//funtion to extract 3 values from a line for comparison
void extract_values(char* line, char* id_out, char* key1_out, char* key2_out) {
    // Extract ID
    char *id_pos = strstr(line, "id=");
    char *id_start = id_pos + 3;
    char *id_end = id_start;
    while(*id_end != ',' && *id_end != '\n' && *id_end != '\0' && *id_end != '\r') {
        id_end++;
    }
    int id_len = id_end - id_start;
    strncpy(id_out, id_start, id_len);
    id_out[id_len] = '\0';

    // Extract key1
    char *key1_pos = strstr(line, "key1=");
    char *key1_start = key1_pos + 5;
    char *key1_end = key1_start;
    while(*key1_end != ',' && *key1_end != '\n' && *key1_end != '\0' && *key1_end != '\r') {
        key1_end++;
    }
    int key1_len = key1_end - key1_start;
    strncpy(key1_out, key1_start, key1_len);
    key1_out[key1_len] = '\0';

    // Extract key2
    char *key2_pos = strstr(line, "key2=");
    char *key2_start = key2_pos + 5;
    char *key2_end = key2_start;
    while(*key2_end != ',' && *key2_end != '\n' && *key2_end != '\0' && *key2_end != '\r') {
        key2_end++;
    }
    int key2_len = key2_end - key2_start;
    strncpy(key2_out, key2_start, key2_len);
    key2_out[key2_len] = '\0';
}

//funtion to compare 2 lines and decide which to keep
int should_keep_first(char* line1, char* line2) {
    char id1[100], key1_1[100], key2_1[100];
    char id2[100], key1_2[100], key2_2[100];
    
    extract_values(line1, id1, key1_1, key2_1);
    extract_values(line2, id2, key1_2, key2_2);
    
    int key1_same = (strcmp(key1_1, key1_2) == 0);
    int key2_same = (strcmp(key2_1, key2_2) == 0);
    
    if (key1_same && !key2_same) {
       // key1 same, key2 smthg els...keep smaller key2
        return (strcmp(key2_1, key2_2) < 0);
    }
    else if (!key1_same) {
        // key1 diff... keep smaller key1
        return (strcmp(key1_1, key1_2) < 0);
    }
    else if (key1_same && key2_same) {
        // both same sy vasls.... keep smaller ID alphabetically
        return (strcmp(id1, id2) < 0);
    }
    
    return 1; // default keep first
}

// Selection sort types function to remove duplicates
void remove_duplicates_selection_style(char* filename) {
    FILE *ptr = fopen(filename, "r");
    if (ptr == NULL) {
        printf("file not found\n");
        return;
    }
    
    // Count lines first
    char line[1000];
    int count = 0;
    while (fgets(line, sizeof(line), ptr) != NULL) {
        count++;
    }
    fclose(ptr);
    
    // Read all lines into array... this be a massive array but oh well... 
    char lines[1000][1000];
    int keep[1000]; // 1 = keep, 0 = remove
    
    ptr = fopen(filename, "r");
    for (int i = 0; i < count; i++) {
        fgets(lines[i], sizeof(lines[i]), ptr);
        keep[i] = 1; // initially keep all
    }
    fclose(ptr);
    
    // Selection style duplicate removal
    for (int i = 0; i < count; i++) {
        if (keep[i]==0) continue; // already marked for removal
        
        char id_i[100], key1_i[100], key2_i[100];
        extract_values(lines[i], id_i, key1_i, key2_i); // extract values foe each line and store in variables mention above
        
        for (int j = i + 1; j < count; j++) {
            if (keep[j]==0) continue;
            
            char id_j[100], key1_j[100], key2_j[100];
            extract_values(lines[j], id_j, key1_j, key2_j);
            
            // Check if IDs are the same 
            if (strcmp(id_i, id_j) == 0) {  // returd wither positive, neg or 0  and is comparision operator that omparts lexiogrphucaaly
                // Apply rules to decide which to keep
                if (should_keep_first(lines[i], lines[j])) {
                    keep[j] = 0; // remove j, keep i
                } else {
                    keep[i] = 0; // remove i, keep j
                    break; // i is removed, no need to continue with i
                }
            }
        }
    }
    
    // Write only kept lines to output file
    FILE *outptr = fopen("ready_events.txt", "w");
    for (int i = 0; i < count; i++) {
        if (keep[i]==1) {
            fputs(lines[i], outptr);
        }
    }
    fclose(outptr);
    printf("removed duplicates and saved to final files.. ready to heap\n");
}


int keep_values(char* filename){
    FILE *ptr = fopen(filename,"r");
    if (ptr == NULL) {                      //check if file exists
        printf("file not fond\n");
        return 0;
    }
    FILE *outptr;
    outptr = fopen("cleaned_events.txt", "w"); // writing to output file  
    char line[1000];
    while(fgets(line, sizeof(line), ptr) != NULL){
        //extract key1 value
        char *key1_pos = strstr(line, "key1=");
        char key1_val[100];
        if(key1_pos != NULL){
            char *start = key1_pos + 5; // skip "key1=" 
            char *end = start;
            while(*end != ',' && *end != '\n' && *end != '\0') {
                end++;
            }
            int len = end - start; // length of stuff after key 1
            strncpy(key1_val, start, len); // copy exactly n charachters(len) from start to key1_val and saves to key1_val array
            key1_val[len] = '\0'; // null terminate
        } else {
            strcpy(key1_val, "9999");
        }

        //extract key2 value
        char *key2_pos = strstr(line, "key2=");
        char key2_val[100];
        if(key2_pos != NULL){
            char *start2 = key2_pos + 5; // skip "key2=" 
            char *end2 = start2;
            while(*end2 != ',' && *end2 != '\n' && *end2 != '\0') {
                end2++;
            }
            int len = end2 - start2; // length of stuff after key 2
            strncpy(key2_val, start2, len); // copy exactly n charachters(len) from start2 to key2_val array
            key2_val[len] = '\0'; // null terminate
        } else {
            strcpy(key2_val, "9999");
        }

        //extract id value
        char *id_pos = strstr(line, "id=");
        char id_val[100];       
        if(id_pos != NULL){
            char *id_start = id_pos + 3; // skip "id="
            char *id_end = id_start;
            while(*id_end != ',' && *id_end != '\n' && *id_end != '\0') {
                id_end++;  
            }
            int len = id_end - id_start;
            strncpy(id_val, id_start, len);
            id_val[len] = '\0';
        } else {
            strcpy(id_val, "unknown");
        }

        //write to output file
        fprintf(outptr, "%s,%s,%s\n", id_val, key1_val, key2_val);
    }
    fclose(ptr);
    fclose(outptr);
    return 1;
}

int main(void) {
    // Clear merged.txt file first
    FILE *clear_file = fopen("merged.txt", "w");
    if (clear_file) fclose(clear_file);
    
    // Loop through region files from 00 to 30
    for (int i = 0; i <= 30; i++) { //pocess all posible files in the events_raw directory
        char filename[100];
        sprintf(filename, "../events_raw/region_%02d_log.txt", i);

        int x = read_write(filename);
        
        if (x == 1) {
            printf("Success: Processed %s\n", filename);
        }
        // If returns 0, just move to next (file not found)
    }
    
    remove_emptyid("merged.txt"); // removed empty ids and written to id_filtered.txt
    printf("removed empty ids and data saved to id_filtered.txt\n");
    
    keys_corrected("id_filtered.txt"); // fix missing/invalid keys
    printf("Key corrected data saved to key_corrected.txt\n");
    
    remove_duplicates_selection_style("keys_corrected.txt"); // remove duplicates based on rules
    printf("removed duplicates and saved to ready_events.txt\n");

    keep_values("ready_events.txt"); // final clean up to keep values in order
    printf("final clean up done and saved to cleaned_events.txt\n");
    
    return 0;
}