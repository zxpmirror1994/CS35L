CC=gcc

all: libadd.so dlopen_example

libadd.so: libadd.c
	$(CC) libadd.c -shared -fPIC -o libadd.so

dlopen_example: dlopen_example.c
	$(CC) dlopen_example.c -ldl -Wl,-rpath=. -o dlopen_example
clean:
	rm -f libadd.so dlopen_example 
