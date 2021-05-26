#include <stdio.h>
#include <ctype.h>


void charsort(char* array, unsigned size){
    for(unsigned i = 0; i < size - 1; i++){
        for(unsigned j = 0; j < size - i - 1; j++){
            if(array[j] > array[j+1]){
                char temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

void intsort(int* array, unsigned size){
    for(unsigned i = 0; i < size - 1; i++){
        for(unsigned j = 0; j < size - i - 1; j++){
            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

void printIntArray(int* array, unsigned size){
    for(unsigned i = 0; i < size; i++){
        printf(" %d", array[i]);
    }
}

void printCharArray(char* array, unsigned size){
    for(unsigned i = 0; i < size; i++){
        printf(" %c", array[i]);
    }
}

int main(){
    //declare variables
    unsigned alp = 26, n1 = 8, n2 = 6, ari = 4;

    char alpha[26] = {'D', 'H', 'Y', 'Q', 'T', 'E', 'K', 'O', 'C', 'V',
    'N', 'S', 'P', 'Z', 'M', 'R', 'I', 'F', 'U', 'W', 'A', 'G', 'B', 'J', 'X', 'L'};

    int numbers1[8] = {4,7,10,11,15,12,3,7};
    int numbers2[6] = {10,10,4,12,3,6};

    char arith[4] = {'*','-','+','/'};

    printf("\nOriginal Alphabet:\n");
    printCharArray(alpha,alp);

    printf("\nOriginal first numbers:\n");
    printIntArray(numbers1,n1);

    printf("\nOriginal second numbers:\n");
    printIntArray(numbers2,n2);

    printf("\nOriginal arithmatic characters:\n");
    printCharArray(arith,ari);


    printf("\n");
    //sort all in ascending order

    charsort(alpha,alp);
    intsort(numbers1,n1);
    intsort(numbers2,n2);
    charsort(arith,ari);

    printf("\nSorted Alphabet:\n");
    printCharArray(alpha,alp);

    printf("\nSorted first numbers:\n");
    printIntArray(numbers1,n1);

    printf("\nSorted second numbers:\n");
    printIntArray(numbers2,n2);

    printf("\nSorted arithmatic characters:\n");
    printCharArray(arith,ari);


    //clear stream
    printf("\n\n");

    return 0;
}
