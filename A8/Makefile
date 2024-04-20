all: run

run: Hashtable.o LinkedList.o
	gcc -w -g Hashtable.c LinkedList.c Main.c -o main


### This builds the hashtable library. Change the filenames accordingly. 
Hashtable.o: LinkedList.o
	gcc -w -c -Wall -g Hashtable.c -o Hashtable.o

LinkedList.c:
	gcc -w -g LinkedList_easy.h LinkedList.c

## Builds the LinkedList library, if you're using it. 
LinkedList.o: LinkedList.c LinkedList_easy.h 
	gcc -w -c -Wall -g LinkedList.c -o LinkedList.o


## Compiles your hashtable tests.
test_hashtable.o : test_hashtable.cc
	g++ -w -std=c++20 -c -Wall -I ./googletest/googletest/include test_hashtable.cc \
		-o test_hashtable.o

## Puts it all together. 
test_suite: clean $(GOOGLE_TEST_LIB) test_hashtable.o Hashtable.o LinkedList.o
	g++ -w -std=c++20 -o test_suite test_hashtable.o Hashtable.o LinkedList.o\
		 -L ./googletest/build/lib -lgtest -lpthread
	@echo -e "\033[38;5;198m===================================="
	@echo Run tests by running ./test_suite
	@echo -e "====================================\033[0m"

clean: 
	rm *.o
	rm -rf *~ main
