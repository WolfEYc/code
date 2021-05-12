#include <stdio.h>
#include <ctype.h>

int main(){
    //declare arrays and array attributes
    unsigned questions = 20, wrong = 0, right = 0;
    char correctAnswers[20] = {'B','D','A','A','C','A','B','A','C','D','B','C','D','A','D','C','C','B','D','A'};
    char userAnswers[questions];

    printf("\nExam:\n");

    for(int i = 0; i < questions; i++){ //take in user input  

        char ans;
        do{
            printf("%d. ",i+1); //print question number
            scanf(" %c",&ans); //scan into ans
            ans = toupper(ans); //convert to uppercase

            //repeat if wrong invalid
        }while(ans != 'A' && ans != 'B' && ans!= 'C' && ans!='D'); 
        
        userAnswers[i] = ans; //save answer to user answers

        //check if right or wrong and iterate accordingly
        if(userAnswers[i]!=correctAnswers[i]) 
            wrong++;
        else
            right++;
    }

    if(right >= 15)
        printf("\nExam Passed!");
    else
        printf("\nExam Failed!");

    //prints out how many they got right or wrong
    printf("\nCorrect answers: %d \nWrong answers: %d\n",right,wrong);

    //loops through and prints out every question number they got wrong
    printf("Questions missed: ");
    for(int i = 0; i < questions; i++){ //iterates through each question
        if(correctAnswers[i]!=userAnswers[i]){ //checks if right or wrong
            printf("%d, ", i+1); //prints question number
        }
    }

    printf("\n\n"); //clear the console
    return 0;
}
