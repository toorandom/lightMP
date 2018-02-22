#include "lightmp.h"
#include "sgprimes.h"
bint *
bint_random (bint * dst, bint * max)
{
  int fd;
  int i;
  int size = max->len * sizeof (_ulong);
  _ulong *buf = calloc (size, sizeof (_ulong));
  fd = open (RAND_DEVICE, O_RDONLY);
  if (fd < 0)
    {
      perror ("fd");
      fprintf (stderr, "Could not open random device at %s\n", RAND_DEVICE);
      exit (EXIT_FAILURE);
    }
  read (fd, buf, size);
  bint_clean (dst);
  dst->len = max->len;
  for (i = 0; i < max->len; i++)
    dst->digits[i] = buf[i];
  sfree (buf);
  close (fd);
  dst->len = max->len + 1;
  bint_normalize (dst);

  while (bint_cmp (dst, max) == FIRST_GREATER) {
printf("Random fue mas grande!\n");
    dst->len--; 
  }

  bint_normalize (dst);
  return dst;
}
