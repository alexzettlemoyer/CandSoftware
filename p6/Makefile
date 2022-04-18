driver: driver.o input.o map.o integer.o text.o vtype.o
	gcc driver.o map.o vtype.o integer.o text.o input.o -o driver

driver.o: driver.c map.c vtype.c integer.c text.c input.c
	gcc -g -Wall -std=c99 -c -o driver.o driver.c

input.o: input.c input.h
	gcc -g -Wall -std=c99 -c -o input.o input.c

map.o: map.c map.h vtype.h
	gcc -g -Wall -std=c99 -c -o map.o map.c

integer.o: integer.c integer.h vtype.h
	gcc -g -Wall -std=c99 -c -o integer.o integer.c

text.o: text.c text.h vtype.h
	gcc -g -Wall -std=c99 -c -o text.o text.c

vtype.o: vtype.c vtype.h
	gcc -g -Wall -std=c99 -c -o vtype.o vtype.c

clean:
	rm -f driver.o input.o map.o integer.o text.o vtype.o
	rm -f driver
	rm -f output.txt
	