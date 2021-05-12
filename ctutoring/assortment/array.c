#include <stdio.h>

int main(){
    int hours[10]; //declare array of 10 ints
    float payRate; //declare payrate

    printf("\nEnter hourly wage: ");
    scanf("%f",&payRate); //read in payrate
    printf("\n");

    for(int i = 0; i < 10; i++){
        printf("Enter hours worked for employee %d: ",i+1);
        scanf("%d",&hours[i]); //read in hours for each employee
    }    

    for(int i = 0; i < 2; i++){
        printf("\n");
        for(int j = 0; j < 10; j++){
            if(i == 0){
                printf("\nEmployee %d worked %d hours.",j+1,hours[j]); //print out how many hours each employee worked
            }else{
                printf("\nEmployee %d earned $%.2f.",j+1,hours[j]*payRate);//print out how much each employee made
            }
        }
    }

    printf("\n");

    return 0;
}