#include <stdio.h>

int main() {
    int rows, cols, i, j;

    // Input dimensions of the matrices
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    int matrixA[rows][cols], matrixB[rows][cols], sum[rows][cols];

    // Input elements of the first matrix
    printf("\n--- Enter elements of Matrix A ---\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("Enter element A[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrixA[i][j]);
        }
    }

    // Input elements of the second matrix
    printf("\n--- Enter elements of Matrix B ---\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("Enter element B[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrixB[i][j]);
        }
    }

    // Adding the two matrices
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            sum[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    // Displaying the resultant matrix
    printf("\n=== SUM OF MATRICES (A + B) ===\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d\t", sum[i][j]);
        }
        printf("\n");
    }

    return 0;
}