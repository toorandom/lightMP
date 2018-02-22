/* Fast division for elliptic curves with O(nlog(n)) complexity 
 * beck@math.co.ro
 */
#include "lightmp.h"
/* Calculates q,r such that
 * qy+r = x
 * with r < y
 */
bint *
bint_div (bint * x, bint * y, bint * q, bint * r)
{
  char xflag = 0, yflag = 0;
  bint *xbak,*ybak;
  bint_clean (q);
  bint_clean (r);

  if (unlikely((y->len == 1) & (y->digits[0] < 0x100)))
    {
      bint_short_div (x, y->digits[0], y->sign, q, r);
      bint_normalize (q);
      bint_normalize (r);
      return q;
    }





  /* if y is bigger than x then q = 0 and leave the residue as x */

  if (bint_cmp (x, y) == SECOND_GREATER)
    {
      q->len = 1;
      bint_copy (r, x);
      return q;
    }
  /* if y is zero then division cannot be performed */
  if (unlikely((y->len == 1) & (y->digits[0] == 0)))
    {
      fprintf (stderr, "Division by zero!\n");
      exit (EXIT_FAILURE);
    }
  /* if len of both is 1 , we do the calculus without entering the loop */
  if ((x->len == 1) && (y->len == 1))
    {
      if (y->digits[0] != 0)
	{
	  q->len = 1;
	  q->digits[0] = x->digits[0] / y->digits[0];
	  r->len = 1;
	  r->digits[0] = x->digits[0] % y->digits[0];
	  return q;
	}
      else
	{
	  fprintf (stderr, "Division by zero\n");
	  exit (EXIT_FAILURE);
	}
    }
  /* We don't want conflicts with the substraction when the input is a negative
     big integer
     * so we convert it to positive to handle it and flag it to return the origina
     l sign of the pointers
   */
  xbak = bint_alloc(x->len+1,x->sign);
  ybak = bint_alloc(y->len+1,y->sign);
  bint_copy(xbak,x);
  bint_copy(ybak,y);
  if (x->sign == NEGATIVE)
    {
      xflag = 1;
      x->sign = POSITIVE;
    }
  if (y->sign == NEGATIVE)
    {
      yflag = 1;
      y->sign = POSITIVE;
    }
  q->len = x->len - y->len + 1;

  unsigned char *xh = (unsigned char *) x->digits;
  unsigned char *yh = (unsigned char *) y->digits;
  unsigned char *qh = (unsigned char *) q->digits;
 // unsigned char *rh = (unsigned char *) r->digits;
  bint *yb_to_nsubt, *b_to_nsubt, *b, *t1, *t2, *t3;
  unsigned int n, t;
  int i, j, f = 0;
  unsigned long long c1, c2, prebase = 0x0000000000000100UL, temp1 = 0;
  n = x->len * 8;
  t = y->len * 8;
/* Fix zero's with new cast */
  i = t - 1;
  while (!yh[i])
    {
      f = 1;
      i--;
      t -= 1;
    }
  //if (f)
    //t++;
  i = n - 1;
  f = 0;
  while (!xh[i])
    {
      f = 1;
      i--;
      n -= 1;
    }
 // if (f)
   // n++;


  yb_to_nsubt = bint_alloc (y->len + 2 * (x->len - y->len + 1), POSITIVE);
  b_to_nsubt = bint_alloc (x->len + y->len + 1, POSITIVE);
  b = bint_alloc (1, POSITIVE);
  t1 =
    bint_alloc (x->len + y->len + 1 + (b->len * (n + t) * (n + t)), POSITIVE);
  t2 =
    bint_alloc (x->len + y->len + 1 + (b->len * (n + t) * (n + t)), POSITIVE);
  t3 =
    bint_alloc (x->len + y->len + 1 + (b->len * (n + t) * (n + t)), POSITIVE);
/* check wordsize */
  b->len = 1;
  b->digits[0] = prebase;

  bint_pow2long (b, n - t, b_to_nsubt);
  bint_mul (y, b_to_nsubt, t1);
  bint_copy (yb_to_nsubt, t1);

  while (bint_cmp (x, yb_to_nsubt) != SECOND_GREATER)
    {
      temp1++;
      bint_sub (x, yb_to_nsubt, t1);
      bint_copy (x, t1);
    }
  qh[n - t] += (unsigned char) temp1 & (unsigned char) 0xff;
 // qh[n - t] += ((unsigned char) (temp1 >> 8) & (unsigned char) 0xff);

  n--;
  for (i = n; i >= t; i--)
    {
      j = i - t;
      if (xh[i] == yh[t - 1])
	{
	  temp1 =
	    (unsigned int) qh[j] + (unsigned int) prebase - (unsigned int) 1;
	  qh[j] += (unsigned char) temp1 & (unsigned char) 0xff;
	  qh[j + 1] += (unsigned char) ((unsigned int) (temp1 >> 8) & 0xff);
	}
      else
	{
	  temp1 =
	    ((((unsigned long long) xh[i] * (unsigned long long) prebase) +
	      (unsigned long long) (xh[i - 1])) / (unsigned long long) yh[t -
									  1]);
	  qh[j] += ((unsigned char) temp1 & (unsigned char) 0xff);
	  qh[j + 1] += ((unsigned char) (temp1 >> 8) & 0xff);
	}
      do
	{
	  c1 =
	    (unsigned long long) ((unsigned long long) qh[j] *
				  (((unsigned long long) yh[t - 1] *
				    prebase) + (unsigned long long) yh[t -
								       2]));
	  c2 =
	    (unsigned long
	     long) ((((unsigned long long) xh[i] * prebase * prebase)) +
		    ((unsigned long long) xh[i - 1] * prebase) +
		    (unsigned long long) xh[i - 2]);
	  if (c1 > c2)
	    {
	      qh[j]--;
	      //printf("q[%d] quedo %04X\n",j,qh[j]);
	    }
	  else
	    break;
	}
      while (1);

      bint_pow2long (b, j, t1);
      bint_mul (t1, y, t3);
      bint_mul_long (t3, qh[j], t2);


      //bint_debug(x,"x");
      //bint_debug(t2,"y");
      bint_sub (x, t2, t3);
      //bint_debug(t3,"z");
      //printf("(x-y)-z\n");


      bint_copy (x, t3);

      if (!bint_is_positive (x))
	{
	  bint_mul (t1, y, t3);
	  bint_add (x, t3, t2);
	  bint_copy (x, t2);
	  qh[j]--;
	  //printf("q[%d] quedo %04X\n",j,qh[j]);
	}
    }

  bint_copy (r, x);
  bint_free (yb_to_nsubt);
  bint_free (b_to_nsubt);
  bint_free (b);
  bint_free (t1);
  bint_free (t2);
  bint_free (t3);
  bint_normalize (r);
  bint_normalize (q);
  bint_clean(x);
  bint_clean(y);
  bint_copy(x,xbak);
  bint_copy(y,ybak);
  bint_free(xbak);
  bint_free(ybak);
  return q;
}
