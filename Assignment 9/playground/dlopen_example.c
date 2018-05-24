#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char **argv) {
	void *h = dlopen("libadd.so", RTLD_NOW);
	if (h == NULL) {
		fprintf(stderr, "cannot open .so\n");
		return 1;
	}
	int (*add)(int, int) = dlsym(h, "add");
	if (add != NULL) {
		printf("%d + %d = %d\n", 1, 2, add(1, 2));
	}
	dlclose(h);
}
