#include <stdio.h>

// Function to compute factorial WITH recursion
unsigned long long factorialRecursive(int n) {
    if (n == 0 || n == 1) {
        return 1; // Base case
    }
    return n * factorialRecursive(n - 1); // Recursive call
}

// Function to compute factorial WITHOUT recursion (Iterative)
unsigned long long factorialIterative(int n) {
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    int num;

    printf("Enter a positive integer: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("Error: Factorial is not defined for negative numbers.\n");
    } else {
        printf("\nFactorial of %d (Without Recursion): %llu\n", num, factorialIterative(num));
        printf("Factorial of %d (With Recursion):    %llu\n", num, factorialRecursive(num));
    }

    return 0;
}