/* 
 * CS:APP Data Lab 
 * 
 * Brendon Ng (304-925-492)
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
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */

int bitParity(int x) {
  /* By splitting a binary string in half and XOR'ing the two halves, in the 
     left-most half of that result will contain an odd number of 1's if the 
     string had an odd number of 1's, so we cut the string in half until we 
     reach one bit which is a 1 if there were an odd nubmer of 1's in the
     original string. If # of 1's is odd then # of 0's is odd.
   */
  int half = x ^ (x >> 16);
  int quarter = half ^ (half >> 8);
  int eighth = quarter ^ (quarter >> 4);
  int sixteenth = eighth ^ (eighth >> 2);
  int one = sixteenth ^ (sixteenth >> 1);

  return one & 1;
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  /* Save the n bits on the right, shift x right n bits, clear the n bits on
     the left of our new x, then replace the saved bits into that spot.
  */
  int rightNBits = ((~(~0 << n)) & x) << (32 + (~n+1));
  int shiftedX = x >> n;
  int leftNBits = ((1 << 31) >> n) << 1;
  x = shiftedX & (~leftNBits);
  return x | rightNBits; 
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  /* Save the nth byte and the mth byte, clear those bytes from the original
     x, then replace them but switched */
  int nShift = n << 3;
  int mShift = m << 3;
  int nByte = 255 << nShift;    //All 1's in the nth byte, 0's elsewhere
  int nByteVals = (((x & nByte) >> nShift) & 255) << mShift;
  int mByte = 255 << mShift;    //All 1's in the mth byte, 0's elsewhere
  int mByteVals= (((x & mByte) >> mShift) & 255) << nShift;
  int combine = nByteVals | mByteVals;
  int takeOut = x & (~nByte & ~mByte);
  return takeOut | combine;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
  /* If x fits in a 16-bit integer, left 17 bits need to be all 1's or all 0's
     so they can be truncated with an arithmetic shift w/o changing the value
  */
  int allMatching = ((~0 & x) >> 15);
  return !allMatching | !(allMatching + 1);
  
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /* negate x and y and use | so it returns 1 if there was a 0 originally, then
     we negate this because we want 1's where there were no 0's
  */
  return ~(~x | ~y);
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
  /* If the two operands have the same sign, subtraction will always be ok.
     If they have different signs, we can tell subtraction caused an overflow
     if the result has the same sign as the second operand 
  */
  int signX = (x >> 31) & 1;
  int signY = (y >> 31) & 1;
  int signSub = ((x+ (~y+1)) >> 31) & 1;
  int sameSign = !(signX ^ signY);
  return ((!sameSign) & (signY ^ signSub)) | sameSign;
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /* If the signs of x and y are different we can easily tell if x is greater
     if they are the same, we can safely do subtraction y-x and if its negative
     then x is greater.
  */
  int signX = x >> 31;
  int signY = y >> 31;
  int sameSign = !(signX ^ signY);
  int test1 = (!sameSign) & ((!signX) & signY);
  int test2 = sameSign & (((y + (~x+1)) >> 31) & 1);
  return test1 | test2;
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
  /* If x fits in an n-bit integer, the right n-1 bits are the only ones that 
     matter. The rest need to be all 0's or all 1's so they can be truncated.
  */
  int toShift = n + ~0;
  int allMatching = ((~0 & x) >> toShift);
  return !allMatching | !(allMatching + 1);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* We take advantage of the complement operator, but complementing a number
     causes it to be off by 1 so we add 1. */
  return ~x + 1;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* It is known that Tmax+1=Tmin, Tmin+Tmax = -1, and Tmin+Tmin = 0.
     We check that these conditions hold because x should be Tmax. 
     However, when x=-1, these properties will also be satisfied because
     Tmin will be zero, so we use !tMin and check that it must be zero ensuring
     that x=-1 will not return true. 
  */ 
  int tMin = x+1;
  int neg1 = tMin + x;
  int zero = (!tMin) | (tMin + tMin);
  return !(~neg1 | zero);
}
