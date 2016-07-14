#
#
#

shuffle.exe :	shuffle.o
	gcc -o shuffle.exe shuffle.o -s

shuffle.o :	shuffle.c
	gcc -c -O2 shuffle.c -o shuffle.o -s

