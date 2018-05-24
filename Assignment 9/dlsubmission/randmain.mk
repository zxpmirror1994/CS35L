#!/bin/bash
CC=gcc
dir=$PWD
all: randmain randlibhw.so randlibsw.so
randcpuid.o: randcpuid.c
	$(CC) -I . -c randcpuid.c 
randlibhw.o: randlibhw.c
	$(CC) -I . -fPIC -c randlibhw.c -o randlibhw.o
randlibsw.o: randlibsw.c
	$(CC) -I . -fPIC -c randlibsw.c -o randlibsw.o
randlibhw.so: randlibhw.o
	$(CC) -shared randlibhw.o -o randlibhw.so
randlibsw.so: randlibsw.o
	$(CC) -shared randlibsw.o -o randlibsw.so
randmain: randmain.o randcpuid.o randlibhw.so randlibsw.so
	$(CC) randmain.o randcpuid.o -ldl -Wl,-rpath=dir -o randmain
randmain.o: randmain.c
	$(CC) -I . -c randmain.c
