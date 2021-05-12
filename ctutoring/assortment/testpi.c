#include <stdio.h>

#define pi 3.14159

int main()
{   
    int op; //Declares which operation you choose
    while(1){
        
        float num1=-1, num2=-1, numAnswer; //Number of choice and Answer

        printf("Geometry Calcualtor\n"); //Calculates whatever shape you desire
        printf("1. Calculate the Area of a Circle\n");
        printf("2. Calculate the Area of a Rectangle\n");
        printf("3. Calculate the Area of a Triangle\n");
        printf("4. Quit\n");
       
        do{
            printf("Enter your choice 1-4: "); //choose which shape you want to calculate accordingly
            scanf(" %d", &op);
        }while(op < 1 || op >4); //Forces the user to reinput the operator if it is not 1-4

        if(op==4)
            return 0;

        do{
        switch(op){
            case 1:
                printf("Enter the radius of the circle: "); //calculates the area of a circle
                scanf(" %f", &num1);
                numAnswer = pi * num1 * num1; // 3.14159 times the 2 other numbers gets you area
                num2 = 0;
                break;
            case 2:
                printf("Enter the length of the rectangle: "); //calculates the length of the rectangle
                scanf(" %f", &num1);
                printf("Enter the width of the rectangle: "); //calculates the width of the rectangle
                scanf(" %f", &num2);
                numAnswer = num1 * num2; //1st number multiplied by the 2nd number
                break;
            case 3:
                printf("Enter the base of the triangle: "); //calculates the base of the triangle
                scanf(" %f", &num1);
                printf("Enter the height of the triangle: "); //calculates the height of the triangle
                scanf(" %f", &num2);
                numAnswer = num1 * num2 * 0.5; //1st number multiplied by the 2nd number multiplied by 0.5 or 1/2
                break;
        }
        }while(num1 < 0 || num2 < 0);
       
        printf("The area = ");
        printf("%f",numAnswer);
        printf("\n");       
    } //Declares that if the user enters 4 as the operator, it will end the program  
    return 0;
}