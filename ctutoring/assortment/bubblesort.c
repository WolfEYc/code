#include <stdio.h>

int main(){

    //declare variables
    int array[8];
    int acount = 0, dcount = 0;

    //input original 8 in any order
    printf("\nInput integers: ");
    for(int i = 0; i < 8; i++){
        scanf("%d",&array[i]);
    }

    //print out original
    printf("\nOriginal:\n");
    for(int i = 0; i < 8; i++){
        printf(" %d", array[i]);
    }

    //sort ascending
    for(int i = 0; i < 8 - 1; i++){
        for(int j = 0; j < 8 - i - 1; j++){
            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                acount++;
            }
        }
    }

    //print out ascending order
    printf("\n\nAscending: (%d exchanges)\n", acount);
    for(int i = 0; i < 8; i++){
        printf(" %d", array[i]);
    }

    //sort descending
    for(int i = 0; i < 8 - 1; i++){
        for(int j = 0; j < 8 - i - 1; j++){
            if(array[j] < array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                dcount++;
            }
        }
    }

    //print out in descending order
    printf("\n\nDescending: (%d exchanges)\n", dcount);
    for(int i = 0; i < 8; i++){
        printf(" %d", array[i]);
    }

    //clear stream
    printf("\n\n");

    return 0;
}
