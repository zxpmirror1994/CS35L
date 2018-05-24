#include <dlfcn.h>
#include <cpuid.h>
#include <errno.h>
#include <immintrin.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <randcpuid.h>

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
    /* Check arguments.  */
    bool valid = false;
    long long nbytes;
    if (argc == 2)
    {
        char *endptr;
        errno = 0;
        nbytes = strtoll (argv[1], &endptr, 10);
        if (errno)
            perror (argv[1]);
        else
            valid = !*endptr && 0 <= nbytes;
    }
    if (!valid)
    {
        fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
        return 1;
    }
    
    /* If there's no work to do, don't worry about which library to use.  */
    if (nbytes == 0)
        return 0;
    
    /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
    void (*initialize) (void);
    unsigned long long (*rand64) (void);
    void (*finalize) (void);
    void* lib1;
    void* lib2;
    void* lib3;
    if (rdrand_supported ())
    {
        lib1 = dlopen("randlibhw.so", RLTD_NOW);
        if (lib1 == NULL)
        {
            fprintf(stderr, "fail to open randlibhw.so.\n");
            return 1;
        }
        void (*hardware_rand64_init)(void) = dlsym(lib1, "hardware_rand64_init");
        if (hardware_rand64_init != NULL)
        {
            initialize = hardware_rand64_init;
        }
        
        lib2 = dlopen("randlibhw.so", RLTD_NOW);
        if (lib2 == NULL)
        {
            fprintf(stderr, "fail to open randlibhw.so.\n");
            return 1;
        }
        unsigned long long (*hardware_rand64)(void) = dlsym(lib2, "hardware_rand64");
        if (hardware_rand64 != NULL)
        {
            rand64 = hardware_rand64;
        }
        
        lib3 = dlopen("randlibhw.so", RLTD_NOW);
        if (lib3 == NULL)
        {
            fprintf(stderr, "fail to open randlibhw.so.\n");
            return 1;
        }
        void (*hardware_rand64_fini)(void) = dlsym(lib3, "hardware_rand64_fini");
        if (hardware_rand64_fini != NULL)
        {
            finalize = hardware_rand64_fini;
        }
    }
    else
    {
        lib1 = dlopen("randlibsw.so", RLTD_NOW);
        if (lib1 == NULL)
        {
            fprintf(stderr, "fail to open randlibsw.so.\n");
            return 1;
        }
        void (*software_rand64_init)(void) = dlsym(lib1, "software_rand64_init");
        if (software_rand64_init != NULL)
        {
            initialize = software_rand64_init;
        }
        
        lib2 = dlopen("randlibsw.so", RLTD_NOW);
        if (lib2 == NULL)
        {
            fprintf(stderr, "fail to open randlibsw.so.\n");
            return 1;
        }
        unsigned long long (*software_rand64)(void) = dlsym(lib2, "software_rand64");
        if (software_rand64 != NULL)
        {
            rand64 = software_rand64;
        }
        
        lib3 = dlopen("randlibsw.so", RLTD_NOW);
        if (lib3 == NULL)
        {
            fprintf(stderr, "fail to open randlibsw.so.\n");
            return 1;
        }
        void (*software_rand64_fini)(void) = dlsym(lib3, "software_rand64_fini");
        if (software_rand64_fini != NULL)
        {
            finalize = software_rand64_fini;
        }
    }
    
    initialize ();
    int wordsize = sizeof rand64 ();
    int output_errno = 0;
    
    do
    {
        unsigned long long x = rand64 ();
        size_t outbytes = nbytes < wordsize ? nbytes : wordsize;
        if (fwrite (&x, 1, outbytes, stdout) != outbytes)
        {
            output_errno = errno;
            break;
        }
        nbytes -= outbytes;
    }
    while (0 < nbytes);
    
    if (fclose (stdout) != 0)
        output_errno = errno;
    
    if (output_errno)
    {
        errno = output_errno;
        perror ("output");
        finalize ();
        return 1;
    }
    
    finalize ();
    dlclose(lib1);
    dlclose(lib2);
    dlclose(lib3);
    return 0;
}
