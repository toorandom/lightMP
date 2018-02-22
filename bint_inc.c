#include "lightmp.h"
/*
 *  Calculates
 *  a=a+1
 *  a must have enough memory to handle a carry flag to the BASE
 *  in the most significative digit
 */
bint *
bint_inc (bint * a)
{
  bint *one = bint_alloc(1,POSITIVE);
  bint *t = bint_alloc(a->len,POSITIVE);
  one->len = 1;
  one->digits[0] = 1;
  bint_add(a,one,t);
  bint_copy(a,t);
  bint_free(one);
  bint_free(t);
  bint_normalize (a);
  return a;
}
