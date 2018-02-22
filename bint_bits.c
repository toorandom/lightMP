#include "lightmp.h"

_ulong masks64[64] = {
0x7FFFFFFFFFFFFFFFUL,0xBFFFFFFFFFFFFFFFUL,0xDFFFFFFFFFFFFFFFUL,0xEFFFFFFFFFFFFFFFUL,0xF7FFFFFFFFFFFFFFUL,
0xFBFFFFFFFFFFFFFFUL,0xFDFFFFFFFFFFFFFFUL,0xFEFFFFFFFFFFFFFFUL,0xFF7FFFFFFFFFFFFFUL,0xFFBFFFFFFFFFFFFFUL,
0xFFDFFFFFFFFFFFFFUL,0xFFEFFFFFFFFFFFFFUL,0xFFF7FFFFFFFFFFFFUL,0xFFFBFFFFFFFFFFFFUL,0xFFFDFFFFFFFFFFFFUL,
0xFFFEFFFFFFFFFFFFUL,0xFFFF7FFFFFFFFFFFUL,0xFFFFBFFFFFFFFFFFUL,0xFFFFDFFFFFFFFFFFUL,0xFFFFEFFFFFFFFFFFUL,
0xFFFFF7FFFFFFFFFFUL,0xFFFFFBFFFFFFFFFFUL,0xFFFFFDFFFFFFFFFFUL,0xFFFFFEFFFFFFFFFFUL,0xFFFFFF7FFFFFFFFFUL,
0xFFFFFFBFFFFFFFFFUL,0xFFFFFFDFFFFFFFFFUL,0xFFFFFFEFFFFFFFFFUL,0xFFFFFFF7FFFFFFFFUL,0xFFFFFFFBFFFFFFFFUL,
0xFFFFFFFDFFFFFFFFUL,0xFFFFFFFEFFFFFFFFUL,0xFFFFFFFF7FFFFFFFUL,0xFFFFFFFFBFFFFFFFUL,0xFFFFFFFFDFFFFFFFUL,
0xFFFFFFFFEFFFFFFFUL,0xFFFFFFFFF7FFFFFFUL,0xFFFFFFFFFBFFFFFFUL,0xFFFFFFFFFDFFFFFFUL,0xFFFFFFFFFEFFFFFFUL,
0xFFFFFFFFFF7FFFFFUL,0xFFFFFFFFFFBFFFFFUL,0xFFFFFFFFFFDFFFFFUL,0xFFFFFFFFFFEFFFFFUL,0xFFFFFFFFFFF7FFFFUL,
0xFFFFFFFFFFFBFFFFUL,0xFFFFFFFFFFFDFFFFUL,0xFFFFFFFFFFFEFFFFUL,0xFFFFFFFFFFFF7FFFUL,0xFFFFFFFFFFFFBFFFUL,
0xFFFFFFFFFFFFDFFFUL,0xFFFFFFFFFFFFEFFFUL,0xFFFFFFFFFFFFF7FFUL,0xFFFFFFFFFFFFFBFFUL,0xFFFFFFFFFFFFFDFFUL,
0xFFFFFFFFFFFFFEFFUL,0xFFFFFFFFFFFFFF7FUL,0xFFFFFFFFFFFFFFBFUL,0xFFFFFFFFFFFFFFDFUL,0xFFFFFFFFFFFFFFEFUL,
0xFFFFFFFFFFFFFFF7UL,0xFFFFFFFFFFFFFFFBUL,0xFFFFFFFFFFFFFFFDUL,0xFFFFFFFFFFFFFFFEUL
};

unsigned int masks32[64] = {
0x7FFFFFFFUL,0xBFFFFFFFUL,0xDFFFFFFFUL,0xEFFFFFFFUL,0xF7FFFFFFUL,
0xFBFFFFFFUL,0xFDFFFFFFUL,0xFEFFFFFFUL,0xFF7FFFFFUL,0xFFBFFFFFUL,
0xFFDFFFFFUL,0xFFEFFFFFUL,0xFFF7FFFFUL,0xFFFBFFFFUL,0xFFFDFFFFUL,
0xFFFEFFFFUL,0xFFFF7FFFUL,0xFFFFBFFFUL,0xFFFFDFFFUL,0xFFFFEFFFUL,
0xFFFFF7FFUL,0xFFFFFBFFUL,0xFFFFFDFFUL,0xFFFFFEFFUL,0xFFFFFF7FUL,
0xFFFFFFBFUL,0xFFFFFFDFUL,0xFFFFFFEFUL,0xFFFFFFF7UL,0xFFFFFFFBUL,
0xFFFFFFFDUL,0xFFFFFFFEUL
};


bint *
bint_bitmodify (bint * x, _ulong bitpos, unsigned char bitstatus)
{
  int digit_pos = x->len - 1 - (bitpos / (sizeof (_ulong)*8));
  assert(digit_pos >= 0);
  if (!(bitstatus & 1))
    x->digits[digit_pos] &= masks64[bitpos%64];
  else
    x->digits[digit_pos] = ~((~x->digits[digit_pos]) & masks64[bitpos%64]);
  return x;
}

_ulong
bint_bitget (bint *x, _ulong bitpos)
{
  int digit_pos = x->len - 1 - (bitpos / (sizeof (_ulong)*8));
  _ulong r;
 // printf("DIGIT_POS=%d\txlen=%ld\tbitpos=%ld\n",digit_pos,x->len,bitpos);
  assert(digit_pos >= 0);
  r=x->digits[digit_pos] & ~masks64[(bitpos%64)] ;
  return r > 0 ? 1 : 0;
}