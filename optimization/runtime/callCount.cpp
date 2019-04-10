#include <stdio.h>

static int count = 0;

void countCall() {
  count += 1;
}

void printResult() {
  printf("Dynamic call count: %d\n", count);
}
