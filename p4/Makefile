agency: agency.o database.o input.o
	gcc agency.o database.o input.o -o agency
	
agency.o: agency.c database.c input.c
	gcc -g -Wall -std=c99 -c -o agency.o agency.c

database.o: database.c database.h input.h
	gcc -g -Wall -std=c99 -c -o database.o database.c

input.o: input.c input.h
	gcc -g -Wall -std=c99 -c -o input.o input.c

clean:
	rm -f agency.o database.o input.o
	rm -f agency database input
	rm -f output.txt