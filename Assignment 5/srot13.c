#include <stdio.h>
#include <stdlib.h>

int rot13cmp(const char* a, const char* b)
{
    
  for(;;)
  {
      int aval = (int)(*a);
      int bval = (int)(*b);
     
      if ((aval >= 65 && aval <= 77) || (aval >= 97 && aval <= 109))
	      aval += 13;
      else if ((aval >= 78 && aval <= 90) || (aval >= 110 && aval <= 122))
	      aval -= 13;
      
      if ((bval >= 65 && bval <= 77) || (bval >= 97 && bval <= 109))
          bval += 13;
      else if ((bval >= 78 && bval <= 90) || (bval >= 110 && bval <= 122))
          bval -= 13;
      
      if (aval == '\n' && bval == '\n')
          return 0;
      else if (aval == '\n')
          return -1;
      else if (bval == '\n')
          return 1;

      
      if (aval == bval)
      {
          a++;
          b++;
      }
      else
      {
          return (aval - bval);
      }
    }
}

int rot13cmpptr(const void* s1, const void* s2)
{
  return rot13cmp(*(const char**)s1, *(const char**)s2);
}

int main()
{
    int size = 2048;
    char* c = (char*)malloc(sizeof(char) * size);
    if (c == NULL)
    {
        fprintf(stderr, "Unable to allocate memory");
        exit(1);
    }
    
    int thischar;
    int i = 0;
    int numOfLines = 0;
    
    for (;;)
    {
        thischar = getchar();
        if (thischar == EOF)
        {
            break;
        }
        
        c[i] = thischar;
        i++;
        if (i == size)
        {
            size += 2048;
            c = (char*)realloc(c, size);
            if (c == NULL)
            {
                fprintf(stderr, "Unable to allocate memory");
                exit(1);
            }
        }
    }
    
    
    
    if (i == 0)
    {
        fprintf(stderr, "Blank file");
        exit(1);
    }
    
    int jk = 0;
    for(;jk<i; jk++)
    {
        if (c[jk]== '\n')
        {
            numOfLines++;
        }
    }
   
    
    if (*(c + i - 1) != '\n')
    {
        *(c + i) = '\n';
        i++;
        numOfLines++;
    }

    char** space = (char**)malloc(sizeof(char*) * numOfLines);
    if (space == NULL)
    {
        fprintf(stderr, "Unable to allocate memory");
        exit(1);
    }
    
    int j = 0;
    char* cnew = c;
    while (j < numOfLines)
    {
        
        space[j] = cnew;
        for(;*cnew != '\n';cnew++)
        {}
        cnew++;
        j++;
    }
    qsort(space, numOfLines, sizeof(char*), rot13cmpptr);
    int k = 0;
    for (; k < numOfLines; k++)
    {
        int m = 0;
        while (space[k][m] != '\n')
        {
            putchar(space[k][m]);
            m++;
        }
        putchar(space[k][m]);
    }
    free(c);
    free(space);
    return 0;
}



