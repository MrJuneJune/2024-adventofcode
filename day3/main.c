#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int Multiply(int x, int y) {
  return x * y;
}

bool IsNumber(char c) {
  return c >= '0' && c <= '9';
}

int main() {
  FILE* file;
  // 10 is random number but didn't find anything bigger
  char firstNum[10] = {0}, secondNum[10] = {0};
  int ch;
  // since I want to move 4 bytes from the first position to the beginning
  // we need 5
  char current[5] = {0}; 
  // same for this as well
  char operation[8] = {0};
  int currentPos = 0;
  unsigned int ans = 0;

  bool on = true;

  file = fopen("inputs.txt", "r");

  while ((ch = fgetc(file)) != EOF) {
    // move by 1, total of 4 bytes
    memmove(current, current + 1, 4);
    memmove(operation, operation + 1, 7);

    // just put in at the 4th pos
    current[3] = (char)ch;
    operation[6] = (char)ch;

    if (strncmp(operation, "don't()", 7) == 0) {
      on = false;
    }

    if (strncmp(operation, "do()", 4) == 0) {
      on = true;
    }

    if (on && strncmp(current, "mul(", 4) == 0) {
      memset(current, 0, sizeof(current));

      int i = 0;
      while ((ch = fgetc(file)) != EOF && IsNumber((char)ch)) {
        firstNum[i++] = (char)ch;
      }
      firstNum[i] = '\0';

      // if i == 0 then no number at all just mul(,
      if (ch != ',' || i == 0) {
        continue;
      }

      i = 0;
      while ((ch = fgetc(file)) != EOF && IsNumber((char)ch)) {
        secondNum[i++] = (char)ch;
      }
      secondNum[i] = '\0';

      if (ch != ')' || i == 0) {
        continue;
      }

      ans += Multiply(atoi(firstNum), atoi(secondNum));

      // no need to do this but in case...
      memset(firstNum, 0, sizeof(firstNum));
      memset(secondNum, 0, sizeof(secondNum));
    }
  }
  fclose(file);

  printf("Ans: %i\n", ans);
  return 0;
}

