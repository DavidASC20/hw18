all: hw18.o
	gcc -o hw18 hw18.c

hw18.o: hw18.c
	gcc -c hw18.c

run:
	./hw18