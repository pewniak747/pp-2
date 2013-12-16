#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROWS 1000
#define COLUMNS 1000

float matrix_a[ROWS][COLUMNS];
float matrix_b[ROWS][COLUMNS];
float matrix_r[ROWS][COLUMNS];

void initialize() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      matrix_a[i][j] = (float) rand() / RAND_MAX;
      matrix_b[i][j] = (float) rand() / RAND_MAX;
      matrix_r[i][j] = 0.0;
    }
  }
}

void multiply_ikj() {
  //#pragma omp parallel for
  for (int i = 0 ; i < ROWS ; i++)
    for (int k = 0 ; k < COLUMNS ; k++)
      for (int j = 0 ; j < COLUMNS ; j++)
        matrix_r[i][j] += matrix_a[i][k] * matrix_b[k][j] ;
}

int main() {
  initialize();

  double start = (double) clock() / CLOCKS_PER_SEC;

  multiply_ikj();

  double elapsed = (double) clock() / CLOCKS_PER_SEC;
  printf("Time: %8.4f sec \n", elapsed-start);
}
