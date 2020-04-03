.POSIX:
.SUFFIXES: .o .c
include ../conf.mk

O = \
main.o\

L = libquadtree.a
H = quadtree.h

$L: $O; ar rv $@ $O && ranlib $@

.c.o:; $(CC) -c $(CFLAGS) $< -o $@
main.o: quadtree.h

.c:
%: %.c

lint:; make CFLAGS='-Wall -Wextra -g -O2'
dep:; for i in *.c; do $(CPP) -MM $$i; done > dep.mk

.PHONY: clean lint install
clean:; rm -f -- $O $L
