#include <stdio.h>
#define amt 20

int main(){
    //declare and init parallel arrays for student info
    int ids[amt] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    float grades[amt] = {70.25,80,49,97.77,98,78,86,83,89.95,78.54,67.77,76,73,87.77,67,97,94.2,92,78.3,92};

    //run algorithm to get highest and lowest student grades and sum
    int highest = 0, lowest = 0;
    float sum = grades[0];
    
    for(int i = 1; i < amt; i++){
        if(grades[i] > grades[highest])
            highest = i;
        else if (grades[i] < grades[lowest])
            lowest = i;
        sum += grades[i];
    }

    //calculate the average
    float avg = sum/amt;
    char letteravg;

    //get what letter grade that corresponds to
    if (avg >= 90){
        letteravg = 'A';
    }else if (avg >= 80){
        letteravg = 'B';
    }
    else if (avg >= 70)
    {
        letteravg = 'C';
    }
    else{
        letteravg = 'F';
    }
    
    //output gathered information
    printf("\nHighest Grade: %.2f scored by ID:%u\n",grades[highest],ids[highest]);
    printf("\nLowest Grade: %.2f scored by ID:%u\n",grades[lowest],ids[lowest]);
    printf("\nAverage Grade: %.2f which is a %c\n\n", avg, letteravg);


    return 0;
}