#line 174 "bits.c"
int allEvenBits(int x) {


  int temp=  0x55;
  int evenPosCopy=  0;
  int result=  0;

  temp =( temp |( temp << 8));
  temp =( temp |( temp << 8));
  temp =( temp |( temp << 8));
#line 188
  evenPosCopy = temp & x;

  result = temp ^ evenPosCopy;

  result = !result;
  return result;
}
#line 214
int bitParity(int x) {
#line 225
  int temp=  x ^( x >> 16);
  temp = temp ^( temp >> 8);
  temp = temp ^( temp >> 4);
  temp = temp ^( temp >> 2);
  temp = temp ^( temp >> 1);


  temp = temp & 1;
  return temp;
}
#line 242
int bitXor(int x, int y) {
  int temp=  ~(x & y);
  int temp2=  ~(~x & ~y);
  int result=  temp & temp2;

  return result;
}
#line 257
int leastBitPos(int x) {


  int xTC=(  ~x)+1;
  int result=  x & xTC;
  return result;
}
#line 273
int replaceByte(int x, int n, int c) {
  int byteShift=(  n << 3);
  int shiftVal=(  c << byteShift);


  int mask=  ~(0xFF << byteShift);

  x =( x & mask);

  x = x | shiftVal;
  return x;

}
#line 292
int tmax(void) {

  int max=  0xFF;
  max =( max << 8) | max;
  max =( max << 15) | max;

  return max;
}
#line 309
int fitsBits(int x, int n) {
#line 314
  int shift=(  n + ~0);
  int fitsPos=  !(x >>( shift));

  int fitNeg=(  !((~(x)) >> shift));
#line 322
  return (fitsPos | fitNeg) & !!(n^32);

}
#line 333
int divpwr2(int x, int n) {
    int sign=(  x >> 31);
    int result=  0;


    int xTC=(  x + sign) ^sign;
#line 343
    sign = !!(x^(1<<31)) & sign;

    sign =( sign << 31);
    sign =( sign >> 31);

    result =( xTC >> n);

    return (result + sign) ^sign;

}
#line 360
int isEqual(int x, int y) {


  int eq=  x ^ y;


  eq = !eq;
  return eq;
}
#line 376
int isPositive(int x) {
#line 382
  int signBit=(  x >> 31) & 1;

  int isZero=  !x;


  int result=  !(signBit | isZero);
  return result;
}
#line 398
int subOK(int x, int y) {
#line 402
  int newY=(  ~y) + 1;
  int signX=(  x >> 31) & 1;
  int signY=(  y >> 31) & 1;
  int diffXY=(  x + newY);
  int newSign=(  diffXY >> 31) & 1;


  int signXY=(  signX ^ signY);
  int OverFlows=  signXY &( signX ^ newSign);

  return !OverFlows;
}
#line 430
int howManyBits(int x) {
#line 435
  int sign=(  x >> 31);
  int saveX=  0;
  int fiveMask=  0x55;
  int threeMask=  0x33;
  int altNibMask=  0xF;
  int temp=  0;
  int result=  0;
  int subOne=  0;

  x =( x + sign) ^ sign;
  saveX = x;

  x =( x >> 1) | x;
  x =( x >> 2) | x;
  x =( x >> 4) | x;
  x =( x >> 8) | x;
  x =( x >> 16) | x;


  fiveMask =( fiveMask << 8) | fiveMask;
  fiveMask =( fiveMask << 16) | fiveMask;


  threeMask =( threeMask << 8) | threeMask;
  threeMask =( threeMask << 16) | threeMask;


  altNibMask =( altNibMask << 8) | altNibMask;
  altNibMask =( altNibMask << 16) | altNibMask;

  temp =(( x >> 1) & fiveMask);
  x = x +(( ~temp)+1);
  x =( x & threeMask) +(( x >> 2) & threeMask);
  result =( x +( x >> 4) & altNibMask);
#line 472
  result =( result << 24) +( result << 16) +( result << 8) + result;
  result =( result >> 24)+1;


  subOne =( sign &( !!!(saveX &( saveX + ~0))));

  subOne =( ~subOne) + 1;

  return result + subOne;

}
#line 494
unsigned float_abs(unsigned uf) {
#line 500
  return uf;
}
#line 513
unsigned float_twice(unsigned uf) {
  return 2;
}
#line 526
int trueFiveEighths(int x)
{
    int xMin=  !!((1 << 31)^(x));
    int sign=(  x >> 31);
    int xTC=  0;
    int div8=  0;
    int rem8=  0;
    int main_part=  0;
    int fractional=  0;
    int result=  0;
#line 539
    sign =( sign & xMin);

    sign =( sign << 31);
    sign =( sign >> 31);

    xTC =( x + sign) ^ sign;

    div8 = xTC >> 3;
    rem8 = xTC & 7;

    main_part =( div8 << 2) + div8;

    fractional =(( rem8 << 2) + rem8) >> 3;

    result = main_part + fractional;
    return (result & ~sign) |(( ~(result)+1) &( sign));

}
