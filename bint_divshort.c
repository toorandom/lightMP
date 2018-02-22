#include "lightmp.h"
 
bint * bint_divshort(bint *u, _ulong v, bint *q, _ulong *r) {
*r = 0;
int i;
const int b = 0x10000;
unsigned long long t;
unsigned short *uh = (unsigned short *)u->digits;
unsigned short *qh = (unsigned short *)q->digits;
bint_clean(q);
for(i=(u->len*4)-1;i>=0;i--) {
t = (unsigned long long)(((unsigned long long)b*((unsigned long long)*r)) + (unsigned long long)uh[i]);
qh[i] += t/v;
*r = t%v;


}




}
