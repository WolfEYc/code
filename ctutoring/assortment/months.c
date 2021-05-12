#include <stdio.h>
#include <string.h>

int main(){
    //initializes the array of days in each month
    int month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    char* name[12] = {"January", "February", "March", "April", "May",
    "June", "July","August", "September", "October", "November","December"};

    //prints out each month and the cooresponding days in it
    for(int i = 0; i < 12; i++){
        printf("\n%s has %d days.",name[i],month[i]);
    }

    printf("\n\n");

    return 0;
}