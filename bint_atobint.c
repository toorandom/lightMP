#include "lightmp.h"
/* Allocates a bint *x
 *  using the number expressed in ascii from ascii_num
 */
#define __BYTE_ORDER__ __LITTLE_ENDIAN__

bint *
atobint (void *data_num, size_t bytes, char sign, bint * x)
{
  int k, m, rsize;


  _ulong *temp = data_num;
  bint_clean (x);

  if(bytes <= sizeof(_ulong)) { 
	  x->sign = sign;
	  x->len = 1;
	  memcpy(&x->digits[0],data_num,bytes);
#if (__BYTE_ORDER__ == __LITTLE_ENDIAN__) 
	  x->digits[0] = INVERT64(x->digits[0]);
#endif 
	  return x;
  }

  rsize = bytes / sizeof (_long);
  x->len = ((bytes % sizeof (_long) != 0)&(bytes > sizeof(_long))) ? rsize + 1 : rsize;

  if ((rsize == 1) && (x->len == 1))
    memcpy (&x->digits[0], data_num, bytes);
  else
    {
      for (k = x->len - 1; k >= 0 + (((bytes % sizeof (_long)) > 0)&(bytes > sizeof(_long))); k--) 
	x->digits[k] = temp[x->len - 1 - k];
 	

      if ((m = bytes % sizeof (_long)))
	memcpy (&x->digits[0], data_num + bytes - m, m);
    }

  x->sign = sign == NEGATIVE ? NEGATIVE : POSITIVE;
#if (__BYTE_ORDER__ == __LITTLE_ENDIAN__)
  int i;
  for (i = 0; i < x->len; i++)
#if (__WORDSIZE == 64)
    x->digits[i] = INVERT64 (x->digits[i]);
#endif
#if (__WORDSIZE == 32)
  x->digits[i] = INVERT32 (x->digits[i]);
#endif

#endif
  //bint_normalize (x);
  return x;
}
