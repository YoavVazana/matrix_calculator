mainmat: mainmat.o mymat.o check_comman.o
	gcc -g -Wall -pedantic -ansi mainmat.o mymat.o check_comman.o -o mainmat -lm
mainmat.o: mainmat.c mymat.h
	gcc -c -g -Wall -pedantic -ansi mainmat.c -o mainmat.o -lm
mymat.o: mymat.c mymat.h
	gcc -c -g -Wall -pedantic -ansi mymat.c -o mymat.o -lm
check_comman.o: check_comman.c mymat.h
	gcc -c -g -Wall -pedantic -ansi check_comman.c -o check_comman.o -lm
