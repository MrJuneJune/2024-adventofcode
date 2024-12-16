// This overcount and can't tell why lol
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define XMAS "XMAS"

struct Line {
  char* value;
};

bool IsXmasReverse(char* horizontal) {
  for (int i=0; i<4; i++) {
    if (XMAS[3-i] != horizontal[i]) return false;
  }
  return true;
}

void IsXmasDiagonal(struct Line* lines, int* ans) {
  char temp[4] = {0};

  for (int j=0; j<137; j++) {
    for (int i=0; i<4; i++) {
      temp[i] = lines[i].value[j + i];
    }
    if (strncmp(temp, XMAS, 4) == 0|| IsXmasReverse(temp)) (*ans)++;
  }


  for (int j=0; j<137; j++) {
    for (int i=0; i<4; i++) {
      temp[i] = lines[3-i].value[j + i];
    }
    if (strncmp(temp, XMAS, 4) == 0|| IsXmasReverse(temp)) (*ans)++;
  }

}

void IsXmasVertical(struct Line* lines, int* ans) {
  char temp[4] = {0};

  for (int j=0; j<140; j++) {
    for (int i=0; i<4; i++) {
      temp[i] = lines[i].value[j];
    }
    if (strncmp(temp, XMAS, 4) == 0 || IsXmasReverse(temp)) (*ans)++;
  }
}

bool IsXmasHorizontal(char* horizontal) {
  return strncmp(horizontal, XMAS, 4) == 0 || IsXmasReverse(horizontal);
}

int main() {
  FILE* file;

  file = fopen("inputs.txt", "r");
  int c;
  int ans = 0;
  char horizontal[5] = {0};

  char line1[140] = {0}, line2[140] = {0}, line3[140] = {0}, line4[140] = {0};
  struct Line currLine[4] = {{line1}, {line2}, {line3}, {line4}};

  int currLinePos = 0;
  int currLineLen = 0;

  while((c=fgetc(file)) != EOF) {

    // new line skip
    if ((char)c == '\n') {
      currLinePos++;
      if (currLinePos > 3) {
        IsXmasVertical(currLine, &ans);
        IsXmasDiagonal(currLine, &ans);

        // Rotate lines buffer
        memmove(&currLine[0], &currLine[1], 3 * sizeof(struct Line)); 
        currLine[3].value = calloc(140, sizeof(char)); 
        currLinePos = 3;
      } 
      currLineLen = 0;
      continue;
    }

    // 5 bytes window for xmas and copying
    memmove(horizontal, horizontal+1, 4);

    currLine[currLinePos].value[currLineLen++] = (char)c;
    horizontal[3] = (char)c;

    if (IsXmasHorizontal(horizontal)) ans++;
  }

  // habbit
  for (int i = 0; i < 4; i++) {
    free(currLine[i].value);
  }
  fclose(file);

  printf("Ans: %i\n", ans);
  return 0;
}
