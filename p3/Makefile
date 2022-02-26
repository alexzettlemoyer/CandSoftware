CC: gcc
CFLAGS: -Wall -std=c99

wordle: wordle.o history.o io.o lexicon.o
	history.o io.o lexicon.o -o wordle.o

wordle.o: wordle.c history.h io.h lexicon.h
	gcc -Wall -std=c99 -i -c -o wordle.o wordle.c

lexicon.o: lexicon.c lexicon.h io.h
	gcc -g -Wall -std=c99 -c -o lexicon.o lexicon.c

io.o: io.c io.h
	gcc -g -Wall -std=c99 -o io.o io.c
	
history.o: history.c history.h
	gcc -g -Wall -std=c99 -c -o history.o history.c

clean:
	rm -f wordle.o history.o io.o lexicon.o
	rm -f wordle history io lexicon
	rm -f stderr.txt output.txt