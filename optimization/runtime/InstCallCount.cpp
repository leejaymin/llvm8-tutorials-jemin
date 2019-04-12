#include <stdio.h>
#include <map>
std::map<int, int> CountMap;

static int count = 0;

extern "C"
void countCall(int id) {
  CountMap[id]++;
}

extern "C"
void printResult() {
  printf("Dynamic call count: \n");
  
  for(auto &entry : CountMap){
    printf("%d %d\n", entry.first, entry.second);
  }
}
