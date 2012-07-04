#****************************************************************************
#* COSC2138/CPT220 - Programming Principles 2A
#* Study Period 2  2010 Assignment #2 - index program
#* Full Name        : EDIT HERE
#* Student Number   : EDIT HERE
#* Course Code      : EDIT HERE
#* Program Code     : EDIT HERE
#* Start up code provided by the CTeach Team
#****************************************************************************/

all: bstring.o index.o index_options.o index_utility.o
	gcc -o indexer bstring.o index.o index_options.o index_utility.o
clean: 
	-rm -rf *.o a.out core
bstring.o: bstring.c bstring.h
	gcc -c -ansi -pedantic -Wall bstring.c
index.o: index.c index.h
	gcc -c -ansi -pedantic -Wall index.c
index_options.o: index_options.c index_options.h index.h
	gcc -c -ansi -pedantic -Wall index_options.c
index_utility.o: index_utility.c index_utility.h bstring.h
	gcc -c -ansi -pedantic -Wall index_utility.c
 
