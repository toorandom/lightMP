#include "lightmp.h"
/*
 * Calculates x,y,gcd such that
 * ax+by = gcd(a,b)
 * gcd = gcd(a,b)
 * lx,ly,gcd must have enough memory to allocate the results
 */
bint *
bint_egcd (bint * a, bint * b, bint * lx, bint * ly, bint * gcd)
{
  bint *x, *y, *t, *q, *r, *m, *qx, *qy, *lx_qx, *ly_qy, *a_backup, *b_backup;
  a_backup = bint_alloc (a->len, a->sign);
  b_backup = bint_alloc (b->len, b->sign);
  bint_copy (a_backup, a);
  bint_copy (b_backup, b);
  bint_clean(lx);
  bint_clean(ly);
  bint_clean(gcd);
  x = bint_alloc (a->len + b->len + 2, POSITIVE);
  y = bint_alloc (a->len + b->len + 2, POSITIVE);
  t = bint_alloc (a->len + b->len + 2, POSITIVE);
  q = bint_alloc (a->len + b->len + 2, POSITIVE);
  r = bint_alloc (a->len + b->len + 2, POSITIVE);
  m = bint_alloc (a->len + b->len + 2, POSITIVE);
  qx = bint_alloc (a->len + b->len + 2 , POSITIVE);
  qy = bint_alloc (a->len + b->len + 2 , POSITIVE);
  ly_qy = bint_alloc (a->len + b->len + 2 , POSITIVE);
  lx_qx = bint_alloc (a->len + b->len + 2 , POSITIVE);
  lx->len = 1;
  ly->len = 1;
  lx->digits[0] = 1;
  ly->digits[0] = 0;
  x->len = 1;
  y->len = 1;
  x->digits[0] = 0;
  y->digits[0] = 1;
  while (!bint_is_zero (b))
    {
      bint_copy (t, b);
    //  bint_debug(a,"p");
    //  bint_debug(b,"q");
      bint_div (a,b,q,m);
    //  bint_debug(q,"r");
    //  bint_debug(m,"m");
    //  printf("(p/q)-r\n");
    //  printf("(p%%q)-m\n");
      bint_copy (b, m);
      bint_copy (a, t);
      bint_copy (t, x);
      bint_mul (q, x, qx);
      bint_sub (lx, qx, lx_qx);
      bint_copy (x, lx_qx);
      bint_copy (lx, t);
      bint_copy (t, y);
      bint_mul (q, y, qy);
      bint_sub (ly, qy, ly_qy);
      bint_copy (y, ly_qy);
      bint_copy (ly, t);
    }
  bint_copy (b, b_backup);
  bint_copy (gcd, a);
  bint_copy (a, a_backup);
  bint_free (a_backup);
  bint_free (b_backup);
  bint_free (x);
  bint_free (y);
  bint_free (t);
  bint_free (q);
  bint_free (r);
  bint_free (m);
  bint_free (qx);
  bint_free (qy);
  bint_free (lx_qx);
  bint_free (ly_qy);
  return gcd;
}
