#include "mainDay02.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char filename[20] = "input.txt";
  if (*(argv[2]) == 't') {
    strcpy(filename, "input_test.txt");
  }
  FILE *fptr = fopen(filename, "r");
  int line_count = get_line_count(fptr);
  int(**matrix) = malloc(line_count * sizeof(int[10]));
  freopen(filename, "r", fptr);
  build_input_matrix(fptr, matrix, line_count);

  return 0;
}

int get_line_count(FILE *fptr) {
  int count = 0;
  for (char c = getc(fptr); c != EOF; c = getc(fptr)) {
    if (c == '\n') {
      count++;
    }
  }
  return count;
}

void build_input_matrix(FILE *fptr, int **matrix, int size) {
  int i = 0;
  while (!feof(fptr)) {
    int j = 0;
    for (char c = getc(fptr); c != '\n'; j++) {
      matrix[i][j] = c;
    };
  }
}
