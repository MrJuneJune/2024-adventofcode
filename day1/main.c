#include <stdio.h>
#include <stdlib.h>

int comp(const void* a, const void* b) {

  // if smaller than it is postiive.
  return (*(int*)a - *(int*)b);
}

int main() {
  printf("Day1 \n");

  FILE *file = fopen("inputs.txt", "r");

  int posNum=0, posList1=0, posList2=0;

  char nums[6] = {0};
  int list1[1000] = {0};
  int list2[1000] = {0};

  int ch = fgetc(file);

  while((ch != EOF)) {
    // First word.
    if ((char)ch == ' ') {
      while ((char)ch == ' ') {
        ch = fgetc(file);
      }
      list1[posList1++] = atoi(nums);
      posNum = 0;
    }

    // Second word
    if ((char)ch == '\n') {
      list2[posList2++] = atoi(nums);
      posNum = 0;
      ch = fgetc(file);
      continue;
    }

    // Collect all words
    nums[posNum++] = (char)ch; 
    ch = fgetc(file);
  }
  fclose(file);

  // sort the list
  qsort(list1, 1000, sizeof(int), comp);
  qsort(list2, 1000, sizeof(int), comp);

  int sum = 0;
  for(int i=0; i<1000; i++) {
    sum += abs(list1[i] - list2[i]);
  }
  printf("Result: %i\n", sum);
  return 0;
}
