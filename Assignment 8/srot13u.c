#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int cmp_count = 0;
int rot13cmp(const char* a, const char* b)
{
    cmp_count++;
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
    struct stat st;
    fstat(0, &st);
    int buffer_size = 512;
    char* c;

    int thischar;
    int blank = 1;
    int i = 0;
    int numOfLines = 0;
    
    if (S_ISREG(st.st_mode))
    {
        int buffer_cap = st.st_size;
        if (buffer_cap == 0)
        {
            fprintf(stderr, "Number of comparisons: %d\n", 0);
            return 0;
        }
        else
        {
            c = (char*)malloc(sizeof(char) * buffer_cap);
            if (c == NULL)
            {
                fprintf(stderr, "Unable to allocate memory");
                exit(1);
            }
            for (;;)
            {
                fstat(0, &st);
                if (st.st_size != buffer_cap)
                {
                    buffer_cap = st.st_size;
                    c = (char*)realloc(c, sizeof(char) * buffer_cap);
                    if (c == NULL)
                    {
                        fprintf(stderr, "Unable to allocate memory");
                        exit(1);
                    }
                }
                if (read(0, &thischar, 1) <= 0)
                {
                    break;
                }
                if (thischar == 10)
                {
                    numOfLines++;
                }
                *(c + i) = thischar;
                i++;
                blank = 0;
            }
        }
    }
    else
    {
        c = (char*)malloc(sizeof(char) * buffer_size);
        if (c == NULL)
        {
            fprintf(stderr, "Unable to allocate memory");
            exit(1);
        }
        for (;;)
        {
            if (read(0, &thischar, 1) <= 0)
            {
                break;
            }
            if (thischar == 10)
            {
                numOfLines++;
            }
            *(c + i) = thischar;
            i++;
            blank = 0;
            if (i == buffer_size)
            {
                buffer_size *= 2;
                c = (char*)realloc(c, sizeof(char) * buffer_size);
                if (c == NULL)
                {
                    fprintf(stderr, "Unable to allocate memory");
                    exit(1);
                }
            }
        }
    }

    if (blank)
    {
        fprintf(stderr, "Blank file");
        exit(1);
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
            write(1, &space[k][m], 1);
            m++;
        }
        write(1, &space[k][m], 1);
    }
    fprintf(stderr, "Number of comparisions: %d\n", cmp_count);
    free(c);
    free(space);
    return 0;
}



