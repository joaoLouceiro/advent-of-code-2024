#include <stdio.h>
#include <stdlib.h>

char FILENAME[] = "input_test.txt";

struct map {
  int number;
  int count;
};

int get_file_line_count(FILE *fptr) {
  int count = 0;
  for (char c = getc(fptr); c != EOF; c = getc(fptr)) {
    if (c == '\n') {
      count++;
    }
  }
  return count;
}

void print_array(int *arr_a, int *arr_b, int length) {
  for (int i = 0; i < length; i++) {
    printf("%d\t%d\t%d\n", i, arr_a[i], arr_b[i]);
  }
  printf("\n");
}

void build_lists(FILE *file, int *arr_a, int *arr_b) {
  freopen(FILENAME, "r", file);
  int i = 0;
  while (!feof(file)) {
    int input_a = 0, input_b = 0;
    fscanf(file, "%d", &input_a);
    fscanf(file, "%d", &input_b);
    if (input_a > 0) {
      arr_a[i] = input_a;
      arr_b[i] = input_b;
    }
    printf("%d - %d\n", i, arr_a[i]);
    i++;
  }
  printf("\n");
}

void qs_swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int qs_partition(int arr[], int low, int high) {
  int pivot = arr[low], i = low, j = high;
  while (i < j) {

    // Find index of the first element greater than the pivot
    while (arr[i] <= pivot && i <= high - 1) {
      i++;
    }

    // Find the index of the last element smaller than the pivot
    while (arr[j] > pivot && j >= low + 1) {
      j--;
    }

    // If the index of the greater number is lower than the index of the
    // smaller, we can swap those two numbers. The greater number can never be
    // before the smaller
    if (i < j) {
      qs_swap(&arr[i], &arr[j]);
    }
  }
  // Swap the number in the first position of the array (the pivot) with the
  // last smaller number found. This will put our pivot in the j variable, which
  // will be our new pivot position, with all smaller elements on lower indices
  // and all greater elements on higher indices.
  qs_swap(&arr[low], &arr[j]);
  return j;
}

void qs_sort(int arr[], int low, int high) {
  if (low < high) {
    // Build a Partition based on the first element of the array. Puts all
    // elements smaller than the first element to it's left and all greater
    // elements to it's right, without care for those elements' sort.
    int pivot_index = qs_partition(arr, low, high);

    // Recursively call Quick Sort on all elements smaller than the current
    // pivot
    qs_sort(arr, low, pivot_index - 1);
    // Recursively call Quick Sort on all elements greater than the current
    // pivot
    qs_sort(arr, pivot_index + 1, high);
  }
}

int calc_number_by_count_sum(int *arr_a, int *arr_b, int size) {
  int total = 0, count = 0, j = 0;
  for (int i = 0; i < size; i++) {
    printf("\n%d - %d\t", arr_a[i], arr_b[j]);
    printf("total = %d\t", total);
    if (i >= 1 && arr_a[i] == arr_a[i - 1]) {
      printf("i == i -1\n");
      total += arr_a[i] * count;
      continue;
    }
    while (arr_a[i] > arr_b[j]) {
      printf("a > b");
      j++;
    }
    if (arr_a[i] < arr_b[j]) {
      printf("a < b\n");
      continue;
    }
    count = 0;
    while (arr_a[i] == arr_b[j]) {
      count++;
      j++;
    }

    printf("%d\n", count);
    total += arr_a[i] * count;
  }
  return total;
}

int main(void) {
  FILE *file = fopen(FILENAME, "r");
  int line_count = get_file_line_count(file),
      *arr_a = (int *)malloc(line_count * sizeof(int)),
      *arr_b = (int *)malloc(line_count * sizeof(int)), total = 0;
  build_lists(file, arr_a, arr_b);
  fclose(file);

  qs_sort(arr_a, 0, line_count - 1);
  qs_sort(arr_b, 0, line_count - 1);
  // print_array(arr_a, arr_b, line_count);
  total = calc_number_by_count_sum(arr_a, arr_b, line_count);
  free(arr_a);
  free(arr_b);

  printf("total = %d\n", total);

  return 0;
}
