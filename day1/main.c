#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZES 1000 /* input line numbers */

typedef struct {
  char* key;  
  int value; 
} KeyValue;

typedef struct {
  KeyValue* k_v[LINE_SIZES];
} HashMap;

// Simple hashing for indexing 
unsigned int hash(const char* key) {
  unsigned int hash = 0;
  while (*key) {
    hash = (hash << 5) + *key++;
  }
  return hash % LINE_SIZES;
}

HashMap* CreateHashMap() {
  // Zero-initialize the struct
  HashMap* table = calloc(1, sizeof(HashMap)); 
  return table;
}

void insert(HashMap* hashMap, const char* key) {
  unsigned int hashKey = hash(key);
  
  while (hashMap->k_v[hashKey] != NULL) {
    if (strcmp(hashMap->k_v[hashKey]->key, key) == 0) {
      hashMap->k_v[hashKey]->value += 1;
      return;
    }
    hashKey = (hashKey + 1) % LINE_SIZES;
  }
  
  hashMap->k_v[hashKey] = malloc(sizeof(KeyValue));
  hashMap->k_v[hashKey]->key = strdup(key);
  hashMap->k_v[hashKey]->value = 1;
}

void add(HashMap* hashMap, const char* key) {
  unsigned int hashKey = hash(key);

  while (hashMap->k_v[hashKey] != NULL) {
    // Check if the keys are same.
    if (strcmp(hashMap->k_v[hashKey]->key, key) == 0) {
        hashMap->k_v[hashKey]->value += 1;
        return;
    }
    hashKey = (hashKey + 1) % LINE_SIZES;
  }

  insert(hashMap, key);
}

int get(HashMap* hashMap, const char* key) {
  unsigned int hashKey = hash(key);

  while (hashMap->k_v[hashKey] != NULL) {
    if (strcmp(hashMap->k_v[hashKey]->key, key) == 0) {
      return hashMap->k_v[hashKey]->value;
    }
    hashKey = (hashKey + 1) % LINE_SIZES;
  }

  return 0;
}

int comp(const void* a, const void* b) {
  // if smaller than it is postiive.
  return (*(int*)a - *(int*)b);
}

int main() {
  printf("Day1 \n");

  FILE *file = fopen("inputs.txt", "r");

  int posNum=0, posList1=0, posList2=0;
  char nums[6] = {0};
  int list1[LINE_SIZES] = {0};
  int list2[LINE_SIZES] = {0};
  HashMap* hashMap = CreateHashMap();

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
      add(hashMap, nums);
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
  qsort(list1, LINE_SIZES, sizeof(int), comp);
  qsort(list2, LINE_SIZES, sizeof(int), comp);

  int sum = 0, sum2 = 0;
  char str[12];
  for(int i=0; i<LINE_SIZES; i++) {
    sum += abs(list1[i] - list2[i]);
    snprintf(str, sizeof(str), "%d", list1[i]);
    sum2 += list1[i] * get(hashMap, str);
  }
  printf("Result Part 1: %i\n", sum);
  printf("Result Part 2: %i\n", sum2);

  return 0;
}
