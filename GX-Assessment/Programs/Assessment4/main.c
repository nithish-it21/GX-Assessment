#include <stdio.h>
#include <stdlib.h>
#include "memory_allocation.h"
#include "matrix_input.h"
#include "memory_deallocation.h"
#include "multiplication.h"
#include "print_matrix.h"

void matrix_multiply() {
    int row1, col1, row2, col2;

    printf("Enter the row size of matrix 1    :");
    if (scanf("%d", &row1) != 1) {
        printf("Enter only Integer\n\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter the column size of matrix 1 :");
    if (scanf("%d", &col1) != 1) {
        printf("Enter only Integer\n\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter the row size of matrix 2    :");
    if (scanf("%d", &row2) != 1) {
        printf("Enter only Integer\n\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter the column size of matrix 2 :");
    if (scanf("%d", &col2) != 1) {
        printf("Enter only Integer\n\n");
        while (getchar() != '\n');
        return;
    }

    if (col1 != row2) {
        printf("\nInvalid matrix dimensions for multiplication: Re-enter values.\n\n");
        return;
    }

    int** mat1 = memory_allocation(row1, col1);
    int** mat2 = memory_allocation(row2, col2);
    int** res = memory_allocation(row1, col2);

    input(mat1, row1, col1, 1);
    input(mat2, row2, col2, 2);

    multiplication(mat1, mat2, res, row1, col1, row2, col2);

    printf("Result\n");
    printf("\n-----------------------------------------\n");
    print_matrix(res, row1, col2);
    printf("-----------------------------------------\n\n");

    free_memory(mat1, row1);
    free_memory(mat2, row2);
    free_memory(res, row1);
    printf("\n");
}

int main() {
    while (1) {
        int num;
        printf("Menu\n");
        printf("-----------------------------------------\n");
        printf("1. Matrix multiplication\n");
        printf("2. Exit\n");
        printf("-----------------------------------------\n");
        printf("\nEnter: ");
        
        if (scanf("%d", &num) != 1) {
            printf("Invalid input. Please enter 1 or 2.\n");
            while (getchar() != '\n');
            continue;
        }

        if (num == 1) {
            matrix_multiply();
        }
        else if (num == 2) {
            printf("\nExited Successfully\n");
            break;
        }
        else {
            printf("Please enter number 1 or 2 only.\n");
        }
    }

    return 0;
}

