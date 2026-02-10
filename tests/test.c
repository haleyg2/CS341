#include <stdio.h>


int main() {
  int x = -3;

  int s = (x >> 31);

  int absVX = (x-1) ^( s);

  printf("%d" ,absVX);

    return 0;
}
