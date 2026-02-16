#include <stdio.h>
#include <float.h>
#define MAXINT 2147483647


int main()
{
  float value_for_conversion = FLT_MAX;
  int output = (int)value_for_conversion;

  printf("output %d, value %f\n", output, value_for_conversion);
  return 0;
}