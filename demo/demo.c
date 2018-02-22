/*
 * This demo source demonstrates how lightmp works with 
 * basic arithmetic operations , see documentation for more functions
 * and extended euclidean algorithm
 * compile
 * gcc -m64 demo.c -o demo -llightmp -llecc
 * Run:
 * $ ./demo STRING1 STRING2
 * Eduardo Ruiz Duarte
 * toorandom@gmail.com
 */


#include <lightmp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc , char **argv) {
bint *a,*b,*c,*r,*s,*t;
if(argc<3 ) {
	fprintf(stderr,"Need to specify two strings in argv\n");
	exit(EXIT_FAILURE);
}

a = bint_alloc(strlen(argv[1])*sizeof(_long)+10,POSITIVE);
b = bint_alloc(strlen(argv[2])*sizeof(_long)+10,POSITIVE);
c = bint_alloc(strlen(argv[1])*sizeof(_long)*20,POSITIVE);
r = bint_alloc(strlen(argv[2])*sizeof(_long)+10,POSITIVE);
s = bint_alloc(strlen(argv[2])*sizeof(_long)+10,POSITIVE);
t = bint_alloc(strlen(argv[2])*sizeof(_long)+10,POSITIVE);


a = atobint(argv[1],strlen(argv[1]),POSITIVE,a);
b = atobint(argv[2],strlen(argv[2]),POSITIVE,b);

c = bint_add(a,b,c);
bint_debug(a,"a");
bint_debug(b,"b");
bint_debug(c,"a+b");



/*
printf("a+b-c\n");
*/
c = bint_mul(a,b,c);
bint_debug(a,"a");
bint_debug(b,"b");
bint_debug(c,"a*b");
/*
printf("(a*b)-c\n");
*/

bint_clean(r);
bint_clean(c);
c = bint_div(a,b,c,r);
bint_debug(a,"a");
bint_debug(b,"b");
bint_debug(c,"a/b");
bint_debug(r,"a mod b");
/*
printf("(a/b)-c\n");
printf("(a%%b)-r\n");
*/


bint_egcd(a,b,s,t,r);
bint_debug(s,"s");
bint_debug(t,"t");
bint_debug(r,"gcd(a,b)");
printf("This is a*s+b*t = gcd(a,b)\n");
bint_free(a);
bint_free(b);
bint_free(c);
bint_free(r);

return 0;

}
