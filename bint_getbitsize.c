#include "lightmp.h"
_ulong
bint_getbitsize (bint * x)
{
  _ulong r = x->len * sizeof (_ulong)*8;
  _ulong t = x->digits[x->len - 1],i=0;
  while (!((t >> ((sizeof (_ulong) * 8) - (i++))) & 1))
    r--;
  return r+1;
}


