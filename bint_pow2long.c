#include "lightmp.h"
/*
 * computes
 * x**y and saves the result in z
 * with y long type
 * z must have enought memory, generaly the memory needed is
 * x->len * y
 */

bint *
bint_pow2long (bint * x, _ulong y, bint * z)
{
  int i;
  bint *t;
  t =  bint_alloc ((x->len+1)*y, POSITIVE);
  t->len = 1;
  t->digits[0] = 1;
  t->sign = POSITIVE;
  if (!y)
    {
      z->digits[0] = 1;
      z->len = 1;
      bint_free(t);
      return z;
    }


     for(i=0;i<y;i++) {
	      bint_mul(x,t,z);
	      bint_copy(t,z);
      }

  bint_free(t); 
  return z;
}
