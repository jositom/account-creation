#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void createAccount();
void login();

int main(){
    char account_exists;
    bool signed_in = false;

    printf("Welcome to the Libellant Account Manager. Do you have an existing account? (Y/N)\n");
    do{
        scanf(" %c",&account_exists);
        account_exists = toupper(account_exists);
        switch(account_exists){
            case 'Y':
                printf("Initialising login sequence..\n");
                break;
            case 'N':
                printf("Initialising account creation sequence..\n");
                createAccount();
                break;
            default:
                printf("Input not recognised. Please try again.\n");
                break;
        }
    }while(!signed_in);

    return 0;
}

void createAccount(){
    char username[25];
    char password[25];

    printf("\nEnter a username (25 characters max): ");
    scanf("%s",username);
    printf("Enter a password (25 characters max): ");
    scanf("%s",password);
}

void login(){

}
