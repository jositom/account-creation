#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

// functions

void createAccount();
void login();
int generateID();

int main(){
    char account_exists;
    bool signed_in = false;

    printf("%d",time(0));

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
                signed_in = true;
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
    long long userID;
    long long check_for_existing_ID;
    bool generatingID = false;

    printf("\nEnter a username (25 characters max): ");
    scanf("%s",username);
    printf("Enter a password (25 characters max): ");
    scanf("%s",password);
    printf("Generating user ID..");

    do{ // generate id and check if its already being used
        generatingID = false;
        userID = generateID();

        FILE *Fp = fopen("id_list.txt", "r");

        if(Fp == NULL){
            printf("An error has occured.\n");
            return;
        }
        else{
            while(fscanf(Fp, "%d", &check_for_existing_ID) == 1){
                if(check_for_existing_ID == userID){
                    generatingID = true;
                    break;
                }
            }
        }

        if(!generatingID){
            FILE *Fp = fopen("id_list.txt", "a");
            fprintf(Fp, "%d\n",userID);
        }

        fclose(Fp);

        printf("%0.7d\n",userID);
    }while(generatingID);

}

void login(){

}

int generateID(){
    srand(time(0));
    long long id = (rand() % 10000000);
    return id;
}
