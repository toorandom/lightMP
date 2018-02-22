#include "lightmp.h"
/*
 * Computes
 * c = a*b
 * c must have at least a->len+b->len+1 memory allocated
 */
bint *
bint_mul (bint * a_new, bint * b_new, bint * c)
{
  int i, j;
  unsigned int *a_hdl, *b_hdl,*c_hdl;
  unsigned long long t,digit,cf=0;
  bint *a,*b;
  bint_clean (c);
  if (bint_is_zero (a_new) || bint_is_zero (b_new))
    {
      c->len = 1;
      c->digits[0] = 0;
      return c;
    }
  if(bint_is_one(a_new)) {
	  bint_copy(c,b_new);
	  c->sign = (b_new->sign == a_new->sign) ? POSITIVE : NEGATIVE;
	  return c;
  }
  if(bint_is_one(b_new)) {
	  bint_copy(c,a_new);
	  c->sign = (b_new->sign == a_new->sign) ? POSITIVE : NEGATIVE;
	  return c;
  }

  a = bint_alloc(a_new->len+1,a_new->sign);
  b = bint_alloc(b_new->len+1,b_new->sign);
  bint_copy(a,a_new);
  bint_copy(b,b_new);

 
/*
  Lame reminder
         AA BB CC
            11 22
   ------------------        
      16 AC F1 18
   0B 56 78 8C
   ------------------
   0B 6D 25 7D 18
*/
  a_hdl = (unsigned int *)a->digits;
  b_hdl = (unsigned int *)b->digits;
  c_hdl = (unsigned int *)c->digits;

  for (i = 0; i < a->len*2; i++)
    for (j = 0; j < b->len*2; j++)
      {
        t = (unsigned long long)c_hdl[i + j] + (unsigned long long)a_hdl[i] * (unsigned long long)b_hdl[j] + (j < 1 ? 0 : cf);
        cf = ((t & 0xFFFFFFFF00000000) >> 32);
        digit = (int)t & 0xFFFFFFFF;
        c_hdl[i + j] = digit;
        c_hdl[i + (b->len*2)] = (j > (b->len*2) - 2) ? cf : 0;
      }
  c->len = a->len + b->len + 1;
  c->sign = (a->sign == b->sign) ? POSITIVE : NEGATIVE;
  bint_free(a);
  bint_free(b);
  bint_normalize (c);
  return c;
}
