compile: mem.o
	gcc mem.o

run:
	./a.out

clean:
	-rm -rf ./a.out *.o

mem.o:
	gcc -c mem.c
