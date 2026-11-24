#include <stdio.h>
#include <string.h>

int main() {
    char email[100], password[100];
    
    // Predefined valid credentials for simulation
    char validEmail[] = "student@gmail.com";
    char validPassword[] = "password123";

    printf("=== GMAIL LOGIN SIMULATION ===\n");

    // Step 1: Enter and verify Email ID
    printf("Enter Email ID: ");
    scanf("%s", email);

    if (strcmp(email, validEmail) != 0) {
        printf("Error: Couldn't find your Google Account.\n");
        return 0;
    }

    // Step 2: Enter and verify Password
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(password, validPassword) == 0) {
        printf("\nLogin Successful! Welcome to your Gmail Inbox.\n");
    } else {
        printf("\nError: Wrong password. Try again.\n");
    }

    return 0;
}