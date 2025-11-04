#include <stdio.h>
#include <stdlib.h>

//Given array silvoing for two-sum problem
void twosum(int* arr[], int k, int len){



    
    for(int i = 0; i<len;i++ ){
        for (int j = i+1; j <= len;j++){
            if ( *arr[i] + *arr[j] == k){
                printf("soln found: %d , %d , with values %d , %d \n", i , j , *arr[i], *arr[j]);
            }
            
            
        }
    }
    printf("loop finished \n");
    
    
}




int main(){

    int arr[3] = {1,2,3} ;

    twosum((int**)&arr , 4, 3);


    return 0;
}