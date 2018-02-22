#include "lightmp.h"
/*
 * Calculates
 * x*y and saves result in z
 * note that y is a long type
 * z must have memory
 */
bint *
bint_mul_long (bint * x, _ulong y, bint * z)
{
  bint *t;
  t = bint_alloc (2, POSITIVE);
  t->digits[0] = y;
  t->len = 1;
  bint_clean(z);
  //bint_debug(x,"x");
  //bint_debug(t,"y");
  z = bint_mul (x, t, z);
  //bint_debug(z,"z");
  bint_normalize (z);
  bint_free (t);
  return z;
}

