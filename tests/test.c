#include <stdio.h>
int allEvenBits(int x) {
  //0x55 55 55 55
  //when all 55 -> all even positions are 1
  //create mask of all 0x55
  int mask = 0x55;
  mask = ((mask << 8) | mask); //extend mask to 0x5555
  mask = ((mask << 16) | mask);//extend to all 32bits

  //& mask with input
  //even bit 1s that match with the mask goto the copy
  int evenPosCopy = mask & x;
  //evenPosCopy XOR mask - should be all 0s
  //if they completely match
  int result =  mask ^ evenPosCopy;
  printf("%d\n" ,result);
  //flip to 1 if they completely match / 0 if not
  result = !result;
  return result;
}

int main() {
    printf("%u" ,allEvenBits(0x55555555));


    return 0;
}