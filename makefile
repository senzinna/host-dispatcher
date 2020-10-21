all:
	gcc -Wall hostd.c -o hostd
	gcc -Wall sigtrap.c -o process
clean:
	rm hostd
	rm process