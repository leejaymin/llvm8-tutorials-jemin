#include <stdio.h>

int add(int x, int y);

int main(){
  int x = 1;
  int y = 2;
  printf("Hello world!\n");
  printf("%d + %d = %d \n",x,y,add(x,y));
  return 0;
}

int add(int x, int y){
  return x+y;
}
