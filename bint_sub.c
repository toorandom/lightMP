#include "lightmp.h"
/*
 * Computes c such that c=a-b
 */
bint *
bint_sub (bint * a, bint * b, bint * c)
{
  int i, swapped = 0;
 // unsigned int *ahl, *bhl, *chl;
 // const unsigned long long B = 0x100000000;
  long long k = 0,cf = 0;
  _ulong ccf = 0;
  bint *temp;
  bint *bbak;
  
  bint_normalize (a);
  bint_normalize (b);
 // bint_debug(a,"x");
 // bint_debug(b,"y");
  bint_clean (c);
  c->sign = POSITIVE;

  if (unlikely((a->sign == POSITIVE) & (b->sign == NEGATIVE)))
    {
      b->sign = POSITIVE;
      c = bint_add (a, b, c);
      b->sign = NEGATIVE;
      bint_normalize (c);
      return c;
    }


  if (unlikely((a->sign == NEGATIVE) & (b->sign == POSITIVE)))
    {
      a->sign = POSITIVE;
      c = bint_add (a, b, c);
      a->sign = NEGATIVE;
      c->sign = NEGATIVE;
      bint_normalize (c);
      return c;
    }
  if (bint_cmp (a, b) == SECOND_GREATER)
    {
      temp = a;
      a = b;
      b = temp;
      swapped = 1;
    }
  //bint_debug(a,"x");
  //bint_debug(b,"y");
  bbak = bint_alloc (a->len + 1, POSITIVE);
  bbak->len = a->len + 1;
  bint_copy (bbak, b);
  bbak->len = a->len;
/*
    bint_debug(b,"b");
    bint_debug(bbak,"b2");
    */
/*
  ahl = (int *) a->digits;
  bhl = (int *) bbak->digits;
  chl = (int *) c->digits;
*/
  for (i = 0; i < a->len ; i++)
    {
       c->digits[i] = a->digits[i] - bbak->digits[i] - cf;
       //printf("[%016lX] - [%016lX] - [%lX] = %016lX\t",a->digits[i],bbak->digits[i],cf,c->digits[i]);
       if((a->digits[i] < (bbak->digits[i] + cf)) | (a->digits[i] < bbak->digits[i])) 
       cf = 1;
       else
       cf = 0;
     //  printf("CARRY=%d\n",cf);
    }
    c->digits[i] = cf;
  c->len = a->len;
  bint_free (bbak);
  /* Regresamos los punteros a la normalidad si estos fueron volteados pero con el
   *  resultado flagueado como negativo*/
  bint_normalize (c);
  if (swapped)
    {
      temp = a;
      a = b;
      b = temp;
      c->sign = NEGATIVE;
    }
  if (c->len < 1)
    {
      c->len = 1;
      c->digits[0] = 0;
    }
  bint_normalize (c);
 // bint_debug(c,"z");
 // printf("x-y-z\n");
  return c;
}
