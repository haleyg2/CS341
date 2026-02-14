/* 
 * CS:APP Data Lab 
 * 
 * <Haley Gray 102061485>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  //0x55 55 55 55
  //when all nibles 0x5 -> all even positions are 1
  int temp = 0x55;
  int evenPosCopy = 0;
  int result = 0;
  //extend 0x55 to all bytes
  temp = (temp | (temp << 8));
  temp = (temp | (temp << 8));
  temp = (temp | (temp << 8));

  //& temp with input
  //even 1bits that match the mask goto the copy
  //don't care about odd bits
  evenPosCopy = temp & x;
  //if copy doesn't completely match, some 1s are left over
  result =  temp ^ evenPosCopy;
  //flip to 1 if they completely match / 0 if not
  result = !result;
  return result;
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 * Refrences: https://youtu.be/c8qAti1zBVQ?si=MB8cc-3m5iyg43z_
 *  video link helped me create a truth table for parity
 *  I made a truth table with 4 bits to start.
 *  Rows where there's an odd # of 0s simplifies to A^B^C^D
 * 
 * https://www.geeksforgeeks.org/dsa/compute-parity-number-using-xor-table-look/
 * Helped me come up with a solution to xor each bit
 * If you shift half of an Int to the right and XOR to
 * itself continously shifting half the amount of the last shift
 * until you only shifted 1bit; Still XOR after each shift;
 * 
 * Then the last bit will be the result of all bits XOR'd
 */
int bitParity(int x) {
  //EX of 4bit a xor b xor c xor d
  // a b c d                       a b c d
  // 0 0 a b ^                     a a a b ^
  // a b a^c b^d                a^a a^b a^C b^d
  // 0 a  b a^c  ^               a^a a^a a^b a^c  ^
  // a a^b (a^c)^b (a^c)^(b^d)  ==       (a^c)^(b^d) 
  //DOESN't MATTER IF LOGIC or ARITH. RIGHT SHIFT
  // Last bit == a xor b xor c xor d
  // -> if last bit == 1, -> odd #of 0s.
  //assuming 32bit sized Int
  int temp = x ^ (x >> 16);
  temp = temp ^ (temp >> 8);
  temp = temp ^ (temp >> 4);
  temp = temp ^ (temp >> 2);
  temp = temp ^ (temp >> 1);
  
  //if LSB == 1, odd 0s -- Cut off last bit
  temp = temp & 1;
  return temp;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int temp = ~(x & y); // becomes notX or notY
  int temp2 = ~(~x & ~y); // becomes x or y
  int result = temp & temp2; //intersection is x XOR y

  return result;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {

  //And Two's comp isolates lsb that's a 1
  int xTC = (~x)+1;
  int result = x & xTC;
  return result;
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  int byteShift = (n << 3); //shift 8 bits
  int shiftVal = (c << byteShift); //shift val to right byte position

  //fill replaced byte in x with 0
  int mask = ~(0xFF << byteShift);
  //replace pos in x with 0s
  x = (x & mask);
  //put c in x
  x = x | shiftVal;
  return x;

}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  //Two's complement Ints lose a bit for the sign
  int max = 0xFF; 
  max = (max << 8) | max; //first 16bits 1
  max = (max << 15) | max; //first 31 bits are 1

  return max;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  //signed int
  //max value = 2^(n-1) -1
  //min value = -2^(n-1)
  //shifting pos num to right n-1 makes all 0 bits if fit.
  int shift = (n + ~0);
  int fitsPos = !(x >> (shift));
  //flip without subracting to keep max num out of bounds
  int fitNeg = (!((~(x)) >> shift));

  //(test does not like anything where n = 32) or where
  //X = 2^n-1 -1 or -2^n-1
  //either fits or is not n=32
  return (fitsPos | fitNeg) & !!(n^32);
 
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    int sign = (x >> 31);
    int result = 0;
    //does nothing if x is Pos,
    //flips to positive if x is Neg 
    int xTC = (x + sign) ^sign;

    //special case for x is the MIN
    //when x is pos, neg but not Min -> Do Nothing
    //force sign to zero if neg and the Min
    sign = !!(x^(1<<31)) & sign;
    //spread 1s throughout sign if x is neg but not Min
    sign = (sign << 31);
    sign = (sign >> 31);
    //divide x by 2^n
    result = (xTC >> n);
    //flip back to origional sign if we need to
    return (result + sign) ^sign;

}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  //are x and y diff
  //if same ^ = 0
  int eq = x ^ y;
  //force eq to 1 if x^y = 0 (match),
  // else some num force to 0
  eq = !eq;
  return eq;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  // return 0 if  x <= 0, 1 if x > 0
  // return 0 if x is either negative or 0
  // return 1 if x is positive

  //sign bit will be 1 if negative number
  int signBit = (x >> 31) & 1;
  //!x will be 1 if x is 0
  int isZero = !x;

  //return 1 if not (neg or zero) -> not(neg) and not(zero)
  int result = !(signBit | isZero);
  return result;
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  //if x and y are diff signs --> possibility of overflow
  //x and y are same signs, x-y has no chance of overflow
  //get -y 
  int newY = (~y) + 1;
  int signX = (x >> 31) & 1;
  int signY = (y >> 31) & 1;
  int diffXY = (x + newY);
  int newSign = (diffXY >> 31) & 1;

  //if same sign x-y will not overflow 
  int signXY = (signX ^ signY);
  int OverFlows = signXY & (signX ^ newSign);

  return !OverFlows;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5 
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 * 
 *  refrences: https://graphics.stanford.edu/~seander/bithacks.html#ParityWith64Bits
 */


int howManyBits(int x) {
  //max number rep with n bits = 2^n -1
  //min = -2^n
  
  //convert to positive or stay at max or stay positive
  int sign = (x >> 31);
  int saveX = 0;
  int fiveMask = 0x55;
  int threeMask = 0x33;
  int altNibMask = 0xF;
  int temp = 0;
  int result = 0;
  int subOne = 0;

  x = (x + sign) ^ sign;
  saveX = x; //reuse this og x when determining if x is a pow of 2
  //fill all to the right of the msb 1bit with 1s
  x = (x >> 1) | x;
  x = (x >> 2) | x;
  x = (x >> 4) | x;
  x = (x >> 8) | x;
  x = (x >> 16) | x;
  //...5555
  
  fiveMask = (fiveMask << 8) | fiveMask;
  fiveMask = (fiveMask << 16) | fiveMask;
  //...3333
  
  threeMask = (threeMask << 8) | threeMask;
  threeMask = (threeMask << 16) | threeMask;
  //...0F0F
  
  altNibMask = (altNibMask << 8) | altNibMask;
  altNibMask = (altNibMask << 16) | altNibMask;

  temp = ((x >> 1) & fiveMask);
  x = x + ((~temp)+1) ;
  x = (x & threeMask) + ((x >> 2) & threeMask);
  result = (x + (x >> 4) & altNibMask);
  //result * 0x1010101 = 16,843,009
  // result = result * 2^24 + result * 2^16 + result * 2^8 + result
  // 2*5 = (2 << 2) + 2 = 2*4 + 2
  result = (result << 24) + (result << 16) + (result << 8) + result;
  result = (result >> 24)+1;

  //x & (x-1) will be 0 if x is just 2^n
  subOne = (sign & (!!!(saveX & (saveX + ~0))));
  //be neg 1 if subOne = 1
  subOne = (~subOne) + 1;
  //subOne if x is most neg value
  return result + subOne; //+ subOne;//+ (sign & (~1 + !!(x ^ min)+1));
  
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  //if NAN exponent is 255 and mantissa is not 0
  unsigned mantissa = (uf << 9);
  unsigned expo = (uf << 1);
  unsigned newUF = expo >> 1;
  mantissa = mantissa >> 9;
  expo = expo >> 24;
  //NaN if expo == 255 & mantissa == not 0
  if (!(expo ^ 255) && mantissa) {
    return uf;  
  }
  return newUF;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  //argument is an unsigned int but as bits (singlept float)
 
  //single point float: sign bit (8 exponent bits) [23 mantissa]
  //expo = 0 & mantissa = not 0 -> subnormal num
  //expo = 0 & mantissa =  0 -> 0 (ZERO)
  //expo = 255 & mantissa = not 0 -> NaN
  //expo = 255 & mantissa = 0 -> ∞
  unsigned maskM = 0;
  unsigned maskEx = 0;
  unsigned mantissa = 0;
  unsigned exponent = 0;
  unsigned sign = 0;
  unsigned nan = 0;

  maskM = 0x7F; //0111 1111
  maskM = (maskM << 8) | 0xFF; //0111 1111 1111 1111 [mantissa mask]
  maskM = maskM << 7 | 0xFF; //23 bits 1s
  maskEx = 0xFF;
  maskEx = maskEx << 23; // [exponent mask]
  mantissa = uf & maskM;
  exponent = uf & maskEx;
  sign = ((1 << 31) & uf);
  exponent = exponent >> 23; 
  nan = (mantissa ^ 0) && !(exponent ^ 255);
  //nan or uf == +0 or -0
  if ((nan || !(uf << 1)) || ((!(exponent ^ 255)) && (!mantissa))){
    return uf; //return argument if uf == nan
  }
  //>> on unsigned pads left with 0s
  //only on signed ints, >> pads left with the (sign bit)

  //if input uses 1 -> 0s (0x00)(Expo) [0x1] [Mantissa] -> 0*2^-126
  //vs 1.0 -> 0s (127)(Expo) [0] [Mantissa] -> 1*2^0
  //0expo and non0 mantissa
  //uf*2 is just shifting the mantissa << 1
  if (exponent) {
    exponent += 1;
    //shift back expo
    exponent = exponent << 23;
    //combine back replace exponent
    uf = uf & (~maskEx); //just 0s at exponent
    uf = uf | exponent; //copy expo back into uf
  } 
  else {
    uf = (uf << 1) | sign;
  }

  return uf;
}
/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */
int trueFiveEighths(int x)
{
    int xMin = !!((1 << 31)^(x));
    int sign = (x >> 31);
    int xTC = 0;
    int div8 = 0;
    int rem8 = 0;
    int main_part = 0;
    int fractional = 0;
    int result = 0;


    //0 if x is pos or min
    //treat -2^31 as if it were positive
    sign = (sign & xMin);
    //exand 1s to whole if neg
    sign = (sign << 31);
    sign = (sign >> 31);
    //Decide to use Two's comp. or stay if pos
    xTC = (x + sign) ^ sign;


    // x/8 and save remainder
    div8 = xTC >> 3;    
    rem8 = xTC & 7;    
    // (x/8) * 5
    main_part = (div8 << 2) + div8;
    //5/8 on remainder
    fractional = ((rem8 << 2) + rem8) >> 3;
    //flip result to neg if we started neg
    result = main_part + fractional;
    return (result & ~sign) | ((~(result)+1) & (sign));
 
}
