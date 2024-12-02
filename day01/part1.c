/*
 * 1. Extract each column to its own array
 * 2. Sort each array
 * 3. Calculate sum of differences per index (reduce differences)
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Builds both arrays from the input file.
 */
void build_unsorted_arrays(FILE *fptr, int *array_a, int *array_b);
void selection_sort(int *unsorted, int *sorted);
int calc_difference_sum(int *sorted_a, int *sorted_b);
void printarray(int *array);

int main(void) {
  FILE *fptr = fopen("input.txt", "r");
  int array_size = 1000, unsorted_a[1001], unsorted_b[1001], sorted_a[1001],
      sorted_b[1001];

  printf("%ptr\t%ptr\n", &sorted_a, &sorted_b);
  build_unsorted_arrays(fptr, unsorted_a, unsorted_b);
  printarray(unsorted_a);
  printarray(unsorted_b);
  printf("%ptr\t%ptr\n", &sorted_a, &sorted_b);

  fclose(fptr);

  selection_sort(unsorted_a, sorted_a);
  selection_sort(unsorted_b, sorted_b);

  printf("%d\n", calc_difference_sum(sorted_a, sorted_b));

  return 0;
}

void printarray(int *array) {
  for (int i = 0; i < 1000; i++) {
    printf("%d\n", array[i]);
  }
  printf("\n");
}

int get_file_line_count(FILE *fptr) {
  int count = 0;
  for (char c = getc(fptr); c != EOF; c = getc(fptr)) {
    if (c == '\n') {
      count++;
    }
  }
  return count;
}

void build_unsorted_arrays(FILE *fptr, int *array_a, int *array_b) {
  int line_count = 0;
  while (!feof(fptr)) {
    int input_a = 0, input_b = 0;
    fscanf(fptr, "%d", &input_a);
    fscanf(fptr, "%d", &input_b);
    array_a[line_count] = input_a;
    array_b[line_count] = input_b;
    line_count++;
    // printf("%d\t%d - %d\t%d - %d\n", file_iterator, input_a,
    //        array_a[file_iterator - 1], input_b, array_b[file_iterator - 1]);
  }

  printf("\n");
}

void selection_sort(int *unsorted, int *sorted) {
  printf("%ptr\t%d\n", &sorted, *(sorted));
  int size = 1000;
  for (int i = 0; i < size; i++) {
    int max = -1, index_of_max = 0;
    for (int j = 0; j < size; j++) {
      if (unsorted[j] > max) {
        max = unsorted[j];
        index_of_max = j;
      }
    }
    sorted[i] = max;
    unsorted[index_of_max] = 0;
  }
  printf("\n");
}

int calc_difference_sum(int *sorted_a, int *sorted_b) {
  int total = 0;
  printf("%ptr\t%ptr\n", &sorted_a, &sorted_b);
  for (int i = 0; i < 1000; i++) {

    printf("%d\t%d    %d\n", i, sorted_a[i], sorted_b[i]);
    int dif = sorted_a[i] - sorted_b[i];
    if (dif < 0)
      dif = dif * -1;
    total += dif;
  }
  return total;
}
