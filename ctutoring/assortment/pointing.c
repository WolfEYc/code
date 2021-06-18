#include <stdio.h>

int main()
{
    //Set up the variables as well as define a few
    
    char firstInitial = 'J', middleInitial;
    int number_of_pencils;
    int number_of_notebooks;
    float pencils = .23;
    float notebooks = 2.89;
    float lunchbox = 4.99;

    char* fIptr = &firstInitial, *mIptr = &middleInitial;
    int* nPptr = &number_of_pencils, *nNptr = &number_of_notebooks;
    float* pencilPtr = &pencils, *nbookPtr = &notebooks, *lboxptr = &lunchbox;
    
    //The information for the first child
    
    *fIptr = 'J';
    *mIptr = 'R';
    
    *nPptr = 7;
    *nNptr = 4;
    
    printf("%c%c needs %d pencils, %d notebooks, and 1 lunchbox\n", *fIptr, *mIptr, *nPptr, *nNptr);
    printf("The total cost is $%.2f\n\n", *nPptr * *pencilPtr + *nNptr**nbookPtr + *lboxptr);
    
    //The information for the second child
    
    *fIptr = 'A';
    *mIptr = 'J';
    
    *nPptr = 10;
    *nNptr = 3;
    
    printf("%c%c needs %d pencils, %d notebooks, and 1 lunchbox\n", *fIptr, *mIptr, *nPptr, *nNptr);
    printf("The total cost is $%.2f\n\n", *nPptr**pencilPtr + *nNptr * *nbookPtr + *lboxptr);
    
    //The information for the third child
    
    *fIptr = 'M';
    *mIptr = 'T';
    
    *nPptr = 9;
    *nNptr =2; 
    
    printf("%c%c needs %d pencils, %d notebooks, and 1 lunchbox\n", *fIptr, *mIptr, *nPptr, *nNptr);
    printf("The total cost is $%.2f\n\n", *nPptr**pencilPtr + *nNptr * *nbookPtr + *lboxptr);

    return 0;
}
