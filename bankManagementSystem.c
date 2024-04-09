// C program to implement
// the above approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For getpass

// Structure to store user data
struct user {
    char username[50];
    char password[50];
    // Add other user data fields as needed
};

// Structure to manage a transaction 
struct transaction {
    char receiver[50];
    char sender[50];
    long amount;
}; // Add a semicolon here

// Function prototypes
void createAccount();
void login(void);
void transferMoney(char* sender);
void checkBalance(const char* username);
void logout(void);

int main() {
    int choice;
    printf("WELCOME TO BANK ACCOUNT SYSTEM\n\n");
    printf("1. Create a bank account\n");
    printf("2. Already a user? Sign in\n");
    printf("3. Exit\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            login();
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice\n");
            break;
    }

    return 0;
}

void createAccount() {
    FILE *fp;
    struct user newUser;

    fp = fopen("users.txt", "a");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    printf("\nEnter username: ");
    scanf("%s", newUser.username);

    // Securely input password
    printf("Enter password: ");
    strcpy(newUser.password, getpass(""));

    fwrite(&newUser, sizeof(newUser), 1, fp);

    fclose(fp);

    printf("\nAccount created successfully!\n\n");
    login();
}

void login() {
    FILE *fp;
    struct user currentUser;
    char inputUsername[50], inputPassword[50];

    fp = fopen("users.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    printf("\nEnter username: ");
    scanf("%s", inputUsername);

    printf("Enter password: ");
    strcpy(inputPassword, getpass(""));

    while (fread(&currentUser, sizeof(currentUser), 1, fp)) {
        if (strcmp(inputUsername, currentUser.username) == 0 &&
            strcmp(inputPassword, currentUser.password) == 0) {
            printf("\nLogin successful!\n\n");
            fclose(fp);
            // Call the main menu or user dashboard function here
            return;
        }
    }

    fclose(fp);
    printf("\nInvalid username or password\n\n");
    login();
}

void transferMoney(char* sender) {
    FILE *fm;
    struct transaction newTransaction;

    fm = fopen("transactions.txt", "a");
    if (fm == NULL) {
        perror("Error opening file");
        exit(1);
    }

    printf("\nTransfer Money\n");
    printf("Enter receiver username: ");
    scanf("%s", newTransaction.receiver);

    printf("Enter amount to transfer: ");
    scanf("%ld", &newTransaction.amount);

    strcpy(newTransaction.sender, sender);

    fwrite(&newTransaction, sizeof(newTransaction), 1, fm);

    fclose(fm);

    printf("\nAmount transferred successfully!\n\n");
    // Redirect to user dashboard or main menu
}

void checkBalance(const char* username) {
    FILE *fm;
    struct transaction currentTransaction;
    long totalBalance = 0;

    fm = fopen("transactions.txt", "r");
    if (fm == NULL) {
        perror("Error opening file");
        exit(1);
    }

    printf("\nBalance Details\n");

    while (fread(&currentTransaction, sizeof(currentTransaction), 1, fm)) {
        if (strcmp(username, currentTransaction.sender) == 0) {
            totalBalance -= currentTransaction.amount;
        } else if (strcmp(username, currentTransaction.receiver) == 0) {
            totalBalance += currentTransaction.amount;
        }
    }

    fclose(fm);

    printf("Total balance for %s: %ld\n\n", username, totalBalance);
    // Redirect to user dashboard or main menu
}

void logout() {
    // Optional: Perform any cleanup or logout actions
    printf("\nLogged out successfully.\n\n");
    // Redirect to main menu or exit
}