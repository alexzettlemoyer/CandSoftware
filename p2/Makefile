calc10: calc.o number10.o operation.o
	gcc calc.o number10.o -o calc.c

calc.o: calc.c number.h operation.h
	gcc -Wall -std=c99 -c calc.c

number10.o: number10.c number.h
	gcc -Wall -std=c99 -c number10.c

operation.o: operation.c operation.h
	gcc -Wall -std=c99 -c operation.c