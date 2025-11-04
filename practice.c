#include <stdio.h>
#include <stdlib.h>

//Given array silvoing for two-sum problem





int twosum(int arr[], int k, int len){
    printf("check1 \n");

    int left = 0;
    int right = len -1; 
    while (left<right){
        printf("loop check \n");
        int sum = arr[left] + arr[right] ;
        if( sum == k){
            
            printf("soln found");
            break;
        }
        else if(sum < k){
            left ++ ;
            continue;
        }
        else if( sum > k){
            right -- ;
            continue;
        }

        printf("check3");



    }

    printf("left: %d , right: %d \n", left, right);
    printf("soln values: %d , %d \n", arr[left], arr[right]);

    return -1 ;



}




int main(){

    int arr[8] = {1,2,3,4,5,6,7,8};

    twosum(arr , 20, 8);


    return 0;
}