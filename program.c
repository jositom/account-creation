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
                return 0;
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
    printf("Generating user ID..\n");

    do{ // generate id and check if its already being used
        generatingID = false;
        userID = generateID();

        FILE *ID_list = fopen("data/id_list.txt", "r");

        if(ID_list == NULL){
            printf("An error has occured.\n");
            return;
        }
        else{
            while(fscanf(ID_list, "%d", &check_for_existing_ID) == 1){
                if(check_for_existing_ID == userID){
                    generatingID = true;
                    break;
                }
            }
        }

        if(!generatingID){
            FILE *ID_list = fopen("data/id_list.txt", "a");
            fprintf(ID_list, "%d\n",userID);
        }

        fclose(ID_list);

    }while(generatingID);

    printf("User ID generated! (%0.7d)\n",userID);

    printf("Saving details..\n");

    char file_name[100];

    sprintf(file_name, "data/accounts/%d.txt", userID);

    FILE *account_details = fopen(file_name, "w");

    fprintf(account_details, "%s\n",username);
    fprintf(account_details, "%s\n",password);
    fprintf(account_details, "%d\n",userID);

    fclose(account_details);

    printf("Details saved! You may now log in to your account. Make sure to copy your user ID so you can log in.\n")
}

void login(){

}

int generateID(){
    srand(time(0));
    long long id = (rand() % 10000000);
    return id;
}
