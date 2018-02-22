/* Fast division for elliptic curves with O(nlog(n)) complexity 
 * beck@math.co.ro
 */
#include "lightmp.h"
/* Calculates q,r such that
 * qy+r = x
 * with r < y
 */
bint *
bint_short_div (bint * x, unsigned char y, char ysign, bint * q, bint * r)
{
  char xflag = 0, yflag = 0;
  bint_clean (q);
  bint_clean (r);
  /* We don't want conflicts with the substraction when the input is a negative
   * big integer
   * so we convert it to positive to handle it and flag it to return the origina
   *l sign of the pointers
   */
  if (x->sign == NEGATIVE)
    {
      xflag = 1;
      x->sign = POSITIVE;
    }
  if (ysign == NEGATIVE)
    {
      yflag = 1;
      y *= -1;
    }

  /* if y is bigger than x then q = 0 and leave the residue as x */



  if (x->len == 1)
    if (x->digits[0] < y)
      {
	q->len = 1;
	bint_copy (r, x);
	return q;
      }
  /* if y is zero then division cannot be performed */
  if (!y)
    {
      fprintf (stderr, "Division by zero!\n");
      exit (EXIT_FAILURE);
    }
  /* if len of both is 1 , we do the calculus without entering the loop */
  if (x->len == 1)
    {
      if (y != 0)
	{
	  q->len = 1;
	  q->digits[0] = x->digits[0] / y;
	  r->len = 1;
	  r->digits[0] = x->digits[0] % y;
	  return q;
	}
      else
	{
	  fprintf (stderr, "Division by zero\n");
	  exit (EXIT_FAILURE);
	}
    }
  if (unlikely(y == 2))
    {
      r->digits[0] = bint_div_2 (x, q);
      r->sign = POSITIVE;
      r->len = 1;
      if (yflag)
	y = y * -1;
      if (xflag)
	x->sign = NEGATIVE;
      if ((y == NEGATIVE) && (x->sign == POSITIVE))
	q->sign = NEGATIVE;
      if ((y == POSITIVE) && (x->sign == NEGATIVE))
	q->sign = NEGATIVE;
      return q;
    }

  q->len = x->len + x->len + 1;

  unsigned char *xh = (unsigned char *) x->digits;
  unsigned char *qh = (unsigned char *) q->digits;
  int i, j, f = 0;
  unsigned long long t, r0 = 0;
  unsigned int xlen = (x->len * 8) - 1, base = 0x100;
  j = xlen;
  while (!xh[j--])
    {
      xlen--;
      f = 1;
    }
  /*
     if(f)
     xlen--;
   */

  for (i = xlen; i >= 0; i--)
    {
      t =
	((unsigned long long) r0 * (unsigned long long) base) +
	(unsigned long long) xh[i];
      qh[i] = ((r0 * base) + xh[i]) / y;
      //qh[i] = t&0xff;
      //qh[i+1] = (t&0x00ff)>>8;
      r0 = t % y;
    }
  r->digits[0] = r0;
  r->len = 1;
  bint_normalize (q);
  if (yflag)
    y = y * -1;
  if (xflag)
    x->sign = NEGATIVE;
  if ((y == NEGATIVE) && (x->sign == POSITIVE))
    q->sign = NEGATIVE;
  if ((y == POSITIVE) && (x->sign == NEGATIVE))
    q->sign = NEGATIVE;
  return q;
}
