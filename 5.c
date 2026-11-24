#include <stdio.h>
#include <string.h>

int main() {
    int choice;
    char str1[100], str2[100], result[200];

    do {
        printf("\n=== STRING OPERATIONS MENU ===\n");
        printf("1. String Length (strlen)\n");
        printf("2. String Copy (strcpy)\n");
        printf("3. String Concatenation (strcat)\n");
        printf("4. String Comparison (strcmp)\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a string: ");
                scanf(" %[^\n]", str1);
                printf("Length of string: %zu\n", strlen(str1));
                break;

            case 2:
                printf("Enter source string: ");
                scanf(" %[^\n]", str1);
                strcpy(str2, str1);
                printf("Copied string: %s\n", str2);
                break;

            case 3:
                printf("Enter first string: ");
                scanf(" %[^\n]", str1);
                printf("Enter second string: ");
                scanf(" %[^\n]", str2);
                strcpy(result, str1);
                strcat(result, str2);
                printf("Concatenated string: %s\n", result);
                break;

            case 4:
                printf("Enter first string: ");
                scanf(" %[^\n]", str1);
                printf("Enter second string: ");
                scanf(" %[^\n]", str2);
                if (strcmp(str1, str2) == 0) {
                    printf("Strings are equal.\n");
                } else {
                    printf("Strings are not equal.\n");
                }
                break;

            case 5:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}