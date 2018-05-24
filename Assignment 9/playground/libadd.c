#include <stdio.h>


__attribute__ ((__constructor__)) 
void pre_func(void) {
	printf("pre_func\n");
}

__attribute__ ((__destructor__)) 
void post_func(void) {
	printf("post_func\n");
}


int add(int a, int b) {
	return a + b;
}
