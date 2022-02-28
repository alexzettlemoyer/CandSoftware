wordle: wordle.o lexicon.o history.o io.o
	gcc wordle.o lexicon.o history.o io.o -o wordle

wordle.o: wordle.c lexicon.h history.h io.h
	gcc -Wall -std=c99 -c -o wordle.o wordle.c

lexicon.o: lexicon.c lexicon.h io.h
	gcc -g -Wall -std=c99 -c -o lexicon.o lexicon.c

io.o: io.c io.h
	gcc -g -Wall -std=c99 -c -o io.o io.c
	
history.o: history.c history.h
	gcc -g -Wall -std=c99 -c -o history.o history.c

clean:
	rm -f wordle.o history.o io.o lexicon.o
	rm -f wordle history io lexicon
	rm -f stderr.txt output.txt scores.txt