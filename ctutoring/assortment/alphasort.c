#include <stdio.h>
#include <ctype.h>

int main(){

    //declare variables
    char array[26] = {'D', 'H', 'Y', 'Q', 'T', 'E', 'K', 'O', 'C', 'V',
    'N', 'S', 'P', 'Z', 'M', 'R', 'I', 'F', 'U', 'W', 'A', 'G', 'B', 'J', 'X', 'L'};


    printf("\nOriginal Array:\n");
    for(unsigned i = 0; i < 26; i++){
        printf(" %c",array[i]);
    }

    //sorts in ascending order
    for(unsigned i = 0; i < 26 - 1; i++){
        for(unsigned j = 0; j < 26 - i - 1; j++){
            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }

    //puts in lowercase
    for(unsigned i = 0; i < 26; i++){
        array[i] = tolower(array[i]);
    }

    printf("\n\nSorted Lowercase Array:\n");
    for(unsigned i = 0; i < 26; i++){
        printf(" %c",array[i]);
    }

    //clear stream
    printf("\n\n");

    return 0;
}
