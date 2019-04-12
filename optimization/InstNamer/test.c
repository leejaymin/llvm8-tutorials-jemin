#include <stdio.h>

int add(int x, int y);

int a() {
  return 0;
}

void b() {
  a();
}

void c() {

  for (int i =0; i <10; i++){
    b();
    b();
    b();
  }

}

int main(){
  int x = 1;
  int y = 2;
  printf("Hello world!\n");
  printf("%d + %d = %d \n",x,y,add(x,y));
  b();
  return 0;
}

int add(int x, int y){
  return x+y;
}
