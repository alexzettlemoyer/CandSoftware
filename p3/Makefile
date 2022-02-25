CC: gcc
CFLAGS: -Wall -std=c99

wordle: wordle.o history.o io.o lexicon.o
	history.o io.o lexicon.o -o wordle.o

wordle.o: wordle.c history.h io.h lexicon.h
	-c -o wordle.o wordle.c

history.o: history.c history.h
	-c -o history.o history.c

io.o: io.c io.h
	-c -o io.o io.c

lexicon.o: lexicon.c lexicon.h io.h
	-c -o lexicon.o lexicon.c

clean:
	rm -f wordle.o history.o io.o lexicon.o
	rm -f wordle history io lexicon
	rm -f stderr.txt output.txt