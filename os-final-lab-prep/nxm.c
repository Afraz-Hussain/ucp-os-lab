#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define the maximum size of the matrices
#define MAX_N 100
#define MAX_M 100

// Structure to pass matrix information to threads
typedef struct {
    int row;
    int col;
    int (*matrix1)[MAX_M];
    int (*matrix2)[MAX_M];
    int (*result)[MAX_M];
} MatrixInfo;

// Function to perform matrix addition in a specific row and column
void *matrixSum(void *arg) {
    MatrixInfo *info = (MatrixInfo *)arg;

    int row = info->row;
    int col = info->col;
    int (*matrix1)[MAX_M] = info->matrix1;
    int (*matrix2)[MAX_M] = info->matrix2;
    int (*result)[MAX_M] = info->result;

    result[row][col] = matrix1[row][col] + matrix2[row][col];

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <N> <M>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);

    if (N <= 0 || M <= 0 || N > MAX_N || M > MAX_M) {
        fprintf(stderr, "Invalid matrix size.\n");
        return 1;
    }

    // Initialize matrices
    int matrix1[MAX_N][MAX_M];
    int matrix2[MAX_N][MAX_M];
    int result[MAX_N][MAX_M];

    printf("Enter elements for Matrix 1 (%d x %d):\n", N, M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf("%d", &matrix1[i][j]);
        }
    }

    printf("Enter elements for Matrix 2 (%d x %d):\n", N, M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf("%d", &matrix2[i][j]);
        }
    }

    // Display matrices
    printf("\nMatrix 1:\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix 2:\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    // Create threads for matrix addition
    pthread_t threads[N][M];
    MatrixInfo info[N][M];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            info[i][j].row = i;
            info[i][j].col = j;
            info[i][j].matrix1 = matrix1;
            info[i][j].matrix2 = matrix2;
            info[i][j].result = result;

            pthread_create(&threads[i][j], NULL, matrixSum, (void *)&info[i][j]);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Display the resultant matrix
    printf("\nResultant Matrix:\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
