/* Calculates   q=x/2  and returns x%2 
 * beck@math.co.ro
 */
#include "lightmp.h"
int
bint_div_2 (bint * x, bint * q)
{
  int i;
  unsigned char bit = 0;
  _ulong t;
  unsigned char bits[2] = { 0, 0 };
  bint_copy (q, x);
/*
  if(q->len == 1) {
  q->digits[0] >>= 1;
  return q->digits[0]%2;
  }
*/
  for (i=q->len-1;i >= 0;i--)
  {
         bits[i%2] = (unsigned char)((unsigned char)q->digits[i]&1);
	 q->digits[i] >>= 1;
         q->digits[i] |= (_ulong)((_ulong)bits[(i+1)%2]<<63);
  }

  

  /*
  for (i= q->len-1;i>=1;i--)
  {
   q->digits[i-1] |= (_ulong)((_ulong)bits[i]<<63);
  }
  */
  

  bint_normalize(q);
  return q->digits[0] % 2;
}
