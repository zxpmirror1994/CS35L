#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    /* Initialization */
    const char* from = argv[1];
    const char* to = argv[2];
    char tr[256];
    int i = 0;
    for (; i < 256; i++)
    {
        tr[i] = i;
    }
    
    /* Check duplicates in "from" */
    i = 0;
    for (; *(from + i); i++)
    {
        int j = i + 1;
        for (; *(from + j); j++)
        {
            if (from[i] == from[j])
            {
                fprintf(stderr, "'from' has duplicate bytes.\n");
                exit(1);
            }
        }
    }
    
    /* Check if sizes of "from" and "to" match */
    i = 0;
    while( *(from + i))
    {
        i++;
    }
    int k = 0;
    while( *(to + k))
    {
        k++;
    }
    if(i != k)
    {
        fprintf(stderr, "Operands have different sizes.\n");
        exit(1);
    }
   
    
    /* Transliteration */
    char c;
    i = 0;
    for (; *(from + i); i++)
    {
        tr[(int)from[i]] = to[i];
    }
    while ((c = getchar()) != EOF)
    {
            putchar(tr[c]);
    }
    return 0;
}
