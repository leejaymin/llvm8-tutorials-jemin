#include <stdio.h>

static int count = 0;

extern "C"

void countCall() {
  count += 1;
}

extern "C"
void printResult() {
  printf("Dynamic call count: %d\n", count);
}
