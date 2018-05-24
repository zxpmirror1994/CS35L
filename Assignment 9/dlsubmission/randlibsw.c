#include <randlib.h>
#include <cpuid.h>
#include <errno.h>
#include <immintrin.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/* Software implementation.  */
__attribute__ ((__constructor__))
void pre_func(void) {
  //      printf("pre_func\n");
}

__attribute__ ((__destructor__))
void post_func(void) {
  //  printf("post_func\n");
}


/* Input stream containing random bytes.  */
static  FILE *urandstream;

/* Initialize the software rand64 implementation.  */
extern  void
software_rand64_init (void)
{
    urandstream = fopen ("/dev/urandom", "r");
    if (! urandstream)
        abort ();
}

/* Return a random value, using software operations.  */
extern  unsigned long long
 software_rand64 (void)
{
    unsigned long long int x;
    if (fread (&x, sizeof x, 1, urandstream) != 1)
        abort ();
    return x;
}

/* Finalize the software rand64 implementation.  */
extern  void
software_rand64_fini (void)
{
    fclose (urandstream);
}
