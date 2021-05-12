#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(){
    char str[25], c;
    int level;

    while(1){
        printf("Enter a lowercase string without numbers ");
        scanf(" %s", str);

        int flag = 0;
        for(int i = 0; i < strlen(str); i++){
            if(isupper(str[i]))
                str[i] = tolower(str[i]);
                
            if(!islower(str[i])){
                printf("lowercase letters only!\n");
                flag = 1;
                break;
            }
        }

        if(flag == 0)
            break;
    }


    while (1){
        printf("Encrypt or Decrypt: (e or d) (n to exit): ");
        scanf(" %c", &c);

        if (c == 'n')
            break;

        if(c == 'e'){ //we are going to encrypt

            printf("Enter a digit: ");
            scanf(" %d", &level);

            printf("new string: ");
            for(int i = 0; i < strlen(str); i++){
                str[i]+=level;
                printf("%c",str[i]);
            }
            printf("\n");

        }else if(c == 'd'){ // we are going to decrypt

            printf("Enter a digit: ");
            scanf(" %d", &level);

            printf("new string: ");
            for(int i = 0; i < strlen(str); i++){
                str[i]-=level;
                printf("%c",str[i]);
            }
            printf("\n");
        }

    }
    


}