#include "lightmp.h"
/*
 * calculates
 * a=a-1
 * and fix the size if the carry flag modifies the size of the result
 */
bint *
bint_dec (bint * a)
{
  bint *one,*t;
  t = bint_alloc(a->len,POSITIVE);
  one = bint_alloc(1,POSITIVE);
  one->len = 1;
  one->digits[0] = 1;
  bint_sub(a,one,t);
  bint_copy(a,t);
  bint_free(t);
  bint_free(one);
  bint_normalize (a);
  return a;
}
