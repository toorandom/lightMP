#include "lightmp.h"
/*
 * This calculates  e
 * such that
 * a**n = e mod m
 */
bint *
bint_mod_exp (bint * a, bint * n, bint * m, bint * e)
{
  bint *x, *q, *r, *tmp, *exp, *nback,*xcopy;
  tmp = bint_alloc (a->len * n->len * (n->len + m->len)+10000, POSITIVE);
  x = bint_alloc (m->len * a->len * n->len, POSITIVE);
  xcopy = bint_alloc(a->len*n->len+m->len,POSITIVE);
  r = bint_alloc (m->len * a->len * n->len, POSITIVE);
  q = bint_alloc ((m->len * a->len * n->len), POSITIVE);
  nback = bint_alloc ((m->len * a->len * n->len), POSITIVE);
  exp = bint_alloc (n->len * a->len * m->len + 1000, POSITIVE);
  exp->len = 1;
  exp->digits[0] = 1;
  bint_mod (a, m, x);
  bint_normalize (x);
  bint_copy (nback, n);
  while (!bint_is_zero (n))
    {
      if (!bint_is_even (n))
        {
        //  bint_debug(exp,"x");
	//  bint_debug(x,"y");
	// printf("even mul\n");
          tmp = bint_mul (exp, x, tmp);
	//  bint_debug(tmp,"z");
	//  printf("(x*y)-z\n");
          bint_clean (exp);
          bint_copy (exp, tmp);
          bint_clean (tmp);
          
	//  bint_debug(exp,"x");
	//  bint_debug(m,"y");
          tmp = bint_mod (exp, m, tmp);
	 // bint_debug(tmp,"z");
	 // printf("(x%%y)-z\n");
	 //printf("clean things\n");
          bint_clean (exp);
          bint_normalize (tmp);
          bint_copy (exp, tmp);
          bint_normalize (exp);
          bint_clean (tmp);
	  //printf("end even\n");
        }
      bint_clean(xcopy);
      bint_copy(xcopy,x);
    //  bint_debug(x,"x");
    //  bint_debug(xcopy,"y");
      tmp = bint_mul (x, xcopy, tmp); /* cambiar */
     // bint_debug(tmp,"z");
     // printf("(x^2)-z\n");
      bint_clean (x);
      bint_normalize (tmp);

      bint_copy (x, tmp);
      bint_clean (tmp);
     // bint_debug(x,"x");
     // bint_debug(m,"y");
      tmp = bint_mod (x, m, tmp);
     // bint_debug(tmp,"z");
     // printf("(x%%y)-z\n");
      bint_clean (x);
      bint_normalize (tmp);
      bint_copy (x, tmp);
      bint_clean (tmp);
      //bint_debug(n,"x");
      
      r->digits[0] = bint_div_2 (n,q);
      /*
      bint_debug(n,"x");
      bint_debug(q,"z");
      */
      //bint_debug(r,"w");
      /*
      printf("(x/2)-z\n");
      */
      bint_normalize (q);
      //printf("normalizado\n");
      bint_clean (n);
      //printf("limpiado\n");
      bint_copy (n, q);
      //printf("copiado\n");
    }
   // printf("Freeing\n");
  bint_free (tmp);
  bint_free (r);
  bint_free (q);
  bint_free (x);
  bint_free (xcopy);
  //printf("clean y norm\n");
  bint_clean (e);
  bint_normalize (exp);
 // bint_debug(exp,"x");
 // bint_debug(m,"y");
// printf("modulo\n");
  bint_mod(exp,m,e);
 // printf("modulo termina\n");
 // bint_debug(e,"z");
 // printf("(x%%y)-z\n");
  bint_free (exp);
  bint_copy (n, nback);
  bint_free (nback);
 // printf("Termina mod exp\n");
  return e;
}
