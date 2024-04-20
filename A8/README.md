# Assignment 8: Finding Anagrams with Hashtables

1. The result is in the res_anagrams.txt
$  make all && ./main

2. Pass googletest
$ make test_suite
$ ./test_suite

[==========] Running 8 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 8 tests from Hashtable
[ RUN      ] Hashtable.Create
[       OK ] Hashtable.Create (0 ms)
[ RUN      ] Hashtable.AddOneRemoveOne
--0x159e07ac0 672807365 valueForAddOneRemoveOne
head: 0x159e07ac0
tail: 0x159e07ac0
element: 1
ptr: 0x159e07ac0
Remove HEAD
[       OK ] Hashtable.AddOneRemoveOne (0 ms)
[ RUN      ] Hashtable.AddOneElemDestroy
[       OK ] Hashtable.AddOneElemDestroy (0 ms)
[ RUN      ] Hashtable.AddOneElemTwoTimes
[       OK ] Hashtable.AddOneElemTwoTimes (0 ms)
[ RUN      ] Hashtable.AddOneRemoveTwice
head: 0x159e07910
tail: 0x159e07910
element: 1
ptr: 0x159e07910
Remove HEAD
[       OK ] Hashtable.AddOneRemoveTwice (0 ms)
[ RUN      ] Hashtable.AddMultipleItems
[       OK ] Hashtable.AddMultipleItems (0 ms)
[ RUN      ] Hashtable.LookupInHashtable
[       OK ] Hashtable.LookupInHashtable (0 ms)
[ RUN      ] Hashtable.TwoElemsOneBucket
[       OK ] Hashtable.TwoElemsOneBucket (0 ms)
[----------] 8 tests from Hashtable (0 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 8 tests.


# ###########################################################################

Details are in the write-up on Canvas. 

Provided files: 

* ```words.txt```: The word file you need to read in to find anagrams with. 
* ```Hashtable_easy.h```: A starting point to structuring your hashtable that 
stores strings (```char*```s). **IF** you want to use it. 
* ```Hashtable.h```: **IF** you want, you can use this to start structuring 
and building your hashtable. 
* ```Hashtable.c```: Stub file for your hashtable code, contains FNV Hash function. 
* ```LinkedList.c```: Placeholder file. Please replace with your version of LinkedList.c
* ```LinkedList_easy.h```: Contains API for a LinkedList that holds strings. It's an easier 
implementation than the other LinkedList. Feel free to replace with your own version if the signatures do not align.
* ```LinkedList.h```: Contains API for a generic LinkedList implementation that you can 
use for your Hashtable implementation, if you'd like.
* ```Makefile```: Generic starting Makefile
* ```test_hashtable.cc```: A starting test file for you to use to test your hashtable implementation. 


## Easier versus More Challenging Approach: 

This week, you can choose whether to take a more challenging or less challenging 
approach to doing the assignment. Here are some pointers for whichever path you take: 

### To use the starting code to make it easier: 

* Utilize ```LinkedList_easy.h``` and ```Hashtable_easy.h``` to implement your linked list. 
* Review the functions declared in the header file. Implement the basics to get 
started (Create, Destroy, Insert), and then implement the other functions if/when 
you get to a point where you think they will be helpful. 
* When you read in the file, be sure to malloc every word. 
* Use the resources below to see how to read in a file line by line. 

### Using the starting code for more challenge: 

* Use the Hashtable/LinkedList files that aren't marked "easy", OR write your own. These 
files have 2 main differences from the "easy" files, and the differences 
allow the LinkedList and Hashtable to hold any type of data, rather than 
a specific type, such as a ```char*``` or ```int```. This generic type 
is specified with a ```void*```. When doing this, we also utilize **function pointers** 
to Destroy and Compare payloads. 



# Resources: 

* https://medium.com/basecs/hashing-out-hash-functions-ea5dd8beb4dd (Hash Functions)
* https://medium.com/basecs/taking-hash-tables-off-the-shelf-139cbf4752f0?source=---------17----------------------- (Hash Tables, generally)
* http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html#hashTables (Hashtables in C)
* http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html#File_IO  (Reading a file in C)
* http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html#functionPointers (Function Pointers, for more challenge)
