#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  char trans[256];
  int i = 0;
  for( i=0; i<256; i++)
    trans[i] = i;
  char *a = argv[2];
  char *p = argv[1];
  for(i = 0; ; i++)
    {
      if(!*(p+i) && !*(a+i))
	break;
      if( (*(p+i) && !*(a+i)) || (*(a+i) && !*(p+i)))
        {
	  perror("Not operands of same length");
	  exit(1);
        }
    }
  int j = 0;
  for( i = 0; *(p+i);i++)
    {
      for(j = i+1; *(p+j); j++)
        {
	  if(*(p+i) == *(p+j))
            {
	      perror("Duplicated characters in from");
	      exit(1);
            }
        }
    }
  char *w = argv[2];
  char *b = argv[1];
  for(; *b; b++) {
    trans[(unsigned int)*b] = *w;
    if (*(w+1)) w++;
  }
  char reader;
  char ini;
  while(read(0,&reader,1)>0) {
    ini =trans[reader];
    write(1,&ini,1);
  }
  return 0;
}
