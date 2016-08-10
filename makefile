truncatable: truncatable.o
	gcc -o truncatable -g truncatable.o
truncatable.o: truncatable.c
	gcc -g -c -Wall truncatable.c
clean:
	rm -f *.o truncatable  
