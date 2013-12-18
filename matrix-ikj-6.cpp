#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

#define ROWS 1000
#define COLUMNS 1000
#define BLOCK 2

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

void multiply_ikj_6() {
  //#pragma omp parallel for
  for (int i = 0 ; i < ROWS ; i+=BLOCK)
    for (int k = 0 ; k < COLUMNS ; k+=BLOCK)
      for (int j = 0 ; j < COLUMNS ; j+=BLOCK)
        for (int i2 = i; i2<std::min(ROWS, i + BLOCK - 1); i2++)
          for (int k2 = k; k2<std::min(COLUMNS, k + BLOCK - 1); k2++)
            for (int j2 = j; j2<std::min(COLUMNS, j + BLOCK - 1); j2++)
              matrix_r[i2][j2] += matrix_a[i2][k2] * matrix_b[k2][j2] ;
}

int main() {
  initialize();

  double start = (double) clock() / CLOCKS_PER_SEC;

  multiply_ikj_6();

  double elapsed = (double) clock() / CLOCKS_PER_SEC;
  printf("Time: %8.4f sec \n", elapsed-start);
}
