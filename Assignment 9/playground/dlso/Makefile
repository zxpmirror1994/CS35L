CC=gcc

all: libadd.so dlso_example

libadd.so: libadd.c
	$(CC) libadd.c -shared -fPIC -o libadd.so

dlso_example: dlso_example.c
	$(CC) dlso_example.c -L. -Wl,-rpath=. -ladd -o dlso_example

clean:
	rm -f libadd.so dlso_example
