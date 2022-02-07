calc10: calc.o number10.o operation.o
	gcc calc.o number10.o operation.o -o calc10

calc.o: calc.c number.h operation.h
	gcc -Wall -std=c99 -c -o calc.o calc.c

number10.o: number10.c number.h
	gcc -c -Wall -std=c99 -g number10.c -o number10.o

operation.o: operation.c operation.h
	gcc -g -Wall -std=c99 -c -o operation.o operation.c