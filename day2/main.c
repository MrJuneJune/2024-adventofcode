#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool IsSafeNums(int* nums, int count) {
  bool isIncreasing = nums[1] > nums[0];
  
  for (int i = 1; i < count; i++) {
    int diff = nums[i] - nums[i - 1];
    if (diff == 0 || abs(diff) > 3) {
      return false;
    }
  
    if ((isIncreasing && diff < 0) || (!isIncreasing && diff > 0)) {
      return false;
    }
  }
  
  return true;
}

bool IsSafeWithDampener(int* nums, int count) {
  if (IsSafeNums(nums, count)) {
    return true;
  }


  // This is really kinda dumb since it is N^2 solutions.
  // I feel like I can optimize this using omitting the first and second one but I can't seem to get right answer idk why lol
  for (int i = 0; i < count; i++) {
    int temp[100];
    int temp_count = 0;

    for (int j = 0; j < count; j++) {
      if (j != i) {
        temp[temp_count++] = nums[j];
      }
    }

    if (IsSafeNums(temp, temp_count)) {
      return true;
    }
  }

  return false; 
}

bool IsSafeLine(char* line) {
  int nums[100];
  int count = 0;
  
  char *token = strtok(line, " ");
  while (token != NULL) {
    nums[count++] = atoi(token);
    token = strtok(NULL, " ");
  }
  
  return IsSafeWithDampener(nums, count);
}

int main() {
  FILE* file;
  int ans = 0;
  int linePos = 0;
  int c;
  char line[200]; // longest line was like 100 so just to be sure
  
  file = fopen("inputs.txt", "r");
  
  while ((c = fgetc(file)) != EOF) {
    if ((char)c == '\n') {
      line[linePos] = '\0';
      if (IsSafeLine(line)) {
        ans++;
      }
      linePos = 0;
      continue;
    }
    line[linePos++] = (char)c;
  }
  
  if (linePos > 0) {
    line[linePos] = '\0';
    if (IsSafeLine(line)) {
      ans++;
    }
  }
  
  fclose(file);
  printf("Result: %i\n", ans);
  return ans;
}

