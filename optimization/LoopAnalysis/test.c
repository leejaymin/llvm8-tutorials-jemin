#include <stdio.h>

#define MATSIZE 1024

int add(int x, int y);

int main(){
  int x = 1;
  int y = 2;
  int i, j, k;
  int a[MATSIZE][MATSIZE];
  int b[MATSIZE][MATSIZE];
  int c[MATSIZE][MATSIZE];
  
  printf("Hello world!\n");
  printf("%d + %d = %d \n",x,y,add(x,y));

  for (i = 0; i < MATSIZE; i++) {
    for (j = 0; j < MATSIZE; j++) {
      a[i][j] = i;
      b[i][j] = j;
    }
  }
  
  // TODO: Optimize this loop
  for (i = 0; i < MATSIZE; i++) {
    for (k = 0; k < MATSIZE; k++) {
      for (j = 0; j < MATSIZE; j++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  printf("%d",c[i][j]);
 
  return 0;
}

int add(int x, int y){
  return x+y;
}
