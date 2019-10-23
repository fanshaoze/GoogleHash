2 OPTION 1: Hashing ( 134 points)
We are asking you to implement a Lexicon structure realized by Google in 1997-1998 to store words (aka
arbitrarily long strings of characters) in main memory. Lexicon L uses a Hash Table T structure along with
an Array A of NULL separated strings . In our case words are going to be English character words only
(upper-case or lower case). Table T will be organized as a hash-table using collision-resolution by openaddressing as specified in class. You are going to use quadratic probing for h(k;i) and keep the choice of
the quadratic function simple: i2 so that h(k;i) = (h0(k)+ i2) mod m. The keys that you will hash are going
to be English words. Thus function h0(k) is also going to be kept simple: the sum of the ASCII/Unicode
values of the characters mod m, where m is the slot-size of the hash table. Thus ’alex’ (the string is between
the quotation marks) is mapped to 97 + 108 + 101 + 120 mod m whatever m is. In the example below, for
m = 11, h(alex;0) = 8. Table T however won’t store key values k in it. This is because the keys are strings
of arbitrary length. Instead, T will store pointers/references in the form of an index to another array A. The
second table, array A will be a character array and will store the words maintained in T separated by NUL
values \0. This is not 2 characters a backslash followed by a zero. It is 1B (ASCII), 2B (UNICODE) whose
all bits are set to 0, the NUL value. If you don’t know what B is, it is a byte; never use b for a bit, write
instead bit or bits i.e. read Handout 3.
An insertion operation affects T and A. A word w is hashed, an available slot in T is computed and
let that slot be t. In T[t] we store an index to table A. This index is the first location that stores the first
character of w. The ending location is the \0 following w in A. New words that do not exist (never inserted,
or inserted but subsequently deleted) are appended in A. Thus originally you need to be wise enough in
choosing the appropriate size of A. If at some point you run-out of space, you need to increase the size of
A accordingly, even if T remains the same. Doubling it, is an option. Likewise the size of T might also
have to be increased. This causes more problems that you also need to attend to. A deletion will modify T
as needed but will not erase w from A. Let it be there. So A might get dirty (i.e. it contains garbage) after
several deletions. If several operations later you end up inserting w after deleting it previously, you do it the
insertion way and you reinsert w, even if a dirty copy of it might still be around. You DO NOT DO a linear
search to find out if it exists arleady in A; it is inefficient. There is not much to say for a search.
You need to support few more operations: Print , Create, Empty/Full/Batch with the last of those
Testing utilizes HashBatch. Its argument filename, an arbitrary filename contains several operations
that are executed in batch mode. Operation 10 is Insert, Operation 11 is Deletion, and Operation 12 is
Search. Operation 13 is Print, Operation 14 is Create. Operation 15 is Comment; the rest of the line is
ignored. (Create accepts as its second parameter and that of HashCreate, an integer value next to its code 14;
this becomes m.) The HashBatch accepts an arbitrary filename such as command.txt or file.txt that contains
a sequence of operations.
% java mplexicon filearbitrary.txt
% ./mplexicon file.txt
14 11
10 alex
10 tom
10 jerry
15 ready-to-print CAUTION: 15 is a comment string (chars,numbers,-)
13 operation 15 is skipped/ignored
The six-line batch file above will print the following. The T entries for 0, 5, 9 are the indexes (first position)
for alex, tom, jerry respectively. Note that the ASCII values for ’alex’ mod 11 give an 8, but for ’tom’
and ’jerry’ give 6, i.e. a collision occurs. A minimal output for Print is available below.
T A: alex\tom\jerry\
0: CAUTION: \ means \0
1: \t is not a tab character !!!
2:
3:
4:
5:
6: 5
7: 9
8: 0
9:
10:
If the following lines were added to the file
12 alex
12 tom
12 jerry
12 mary
11 tom
13
they will generate in addition on screen
alex found at slot 8
tom found at slot 6
jerry found at slot 7
mary not found
tom deleted from slot 6
T A: alex\***\jerry\
0:
1:
2:
3:
4:
5:
6:
7: 9
8: 0
9:
10:
checking for an empty or full table/array and a mechanism to perform multiple operations in batch form.
Print prints nicely T and its contents i.e. index values to A. In addition it prints nicely (linear-wise in one
line) the contents of A. (For a \0 you will do the SEMI obvious: print a backslash but not its zero). The
intent of Print is to assist the grader. Print however does not print the words of A for deleted words. It
prints stars for every character of a deleted word instead. (An alternative is that during deletion each such
character has already been turned into a star.) Function Create creates T with m slots, and A with 15m chars
and initializes A to spaces. The following is a suggested minimal interface (we try to be language agnostic).
We call the class that supports and realizes A and T a lexicon: L is one instance of a lexicon.
HashCreate (lexicon L, int m); // Create T, A. T will have m slots; A should be 15m
HashEmpty (lexicon L); // Check if L is empty
HashFull (lexicon L); // Check if L can maintain more words
HashPrint (lexicon L); // Print of L
HashInsert (lexicon L, word w); //Insert w into L (and T and A)
HashDelete (lexicon L, word w); //Delete w from L (but not necessarily from A)
HashSearch (lexicon L, word w); //Search for string in L (and this means T)
HashBatch (lexicon L, file filename)
