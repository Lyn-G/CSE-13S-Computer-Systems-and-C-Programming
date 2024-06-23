### Description of the Assignment

We are to create a program that is a Huffman method of data compression. It can compress and decompress data and retain the information all the same.


### How I Built It

In this section, I will describe all the files that are necessary for Huffman coding. 

###### node.h
This contains all the C declarations and/or macro defiition to be used for node.c

###### node.c
The first ADT we program is node. We had to initialize node and set up its usage for the program. This meant setting up the symbol and initializing the frequency. Then we created a function to delete the node that's passed in. We set the pointer to NULL after freeing the memory. We also create a function that joins two nodes and returns a pointer to a created parent node. Assign the parent's left and right child respectively & set the frequency as left child's frequency plus right child's frequency. Set the parent's symbol to '$'. We will also create a node_print() function that will be used for debugging.

###### pq.h
This contains all the C declarations and/or macro defiition to be used for pq.c

###### pq.c
Another ADT we will implement is priority queue. We will create a constructor for it and define the maximum capacity. We will also create a function to delete the priority queue by setting the pointers to NULL after freeing the memory. We have functions to check if the priority queue is empty, full, or its size. Then we will create functions for enqueuing and dequeuing. This is done with our min heap implementation from assignment 4. We also implement a printing function for debugging.

###### code.h
This contains all the C declarations and/or macro defiition to be used for code.c

###### code.c
We initialize a Code constructor for the Code ADT. We set the top, which is to mimick a stack's top, to 0 and zero out the array of bits. We will create functions to return the Code's size and whether its empty or full. We will check in all upcoming functions if the bit is out of the range. Create functions that will set bit, clear bit, get bit, push bit, and pop bit. We can use a debugging print function to check if it works.

###### io.h
This contains all the C declarations and/or macro defiition to be used for io.c

###### io.c
We will now write out functions for I/O. The first function is reading bytes from an input.We will loop calls to read() until we have read all bytes that were specified or when there are no more left. For writing out bytes, we follow the same logic as reading bytes, but we loop the calls to write(). Loop until we have either written out all the bytes specified or there's no more bytes left to write. In order to read a single bit from a file, we read in a block of bytes at a time and read out each one. Once we reach the end, we select the next block of bytes and start the process over again. Writing out code will have the same logic as the previous function once again. We will use a buffer and an index to buffer a bit in the code into the buffer. Once we fill the buffer, we will write the contents of the buffer. If we have leftover bits, we can use our flush codes function to write out any leftover, buffered bits.

###### stack.h
This contains all the C declarations and/or macro defiition to be used for stack.c

###### stack.c
The next ADT we will have built is a stack. We created a constructor to initialize a stack. We will also create a destructor for a stack. We will also create functions to check the stack's size and whether it's full or empty. In order to truly be a stack, we need to implement pushing and popping a node. We will also create a stack debug print statement.

###### huffman.h
This contains all the C declarations and/or macro defiition to be used for huffman.c

###### huffman.c
For the actual Huffman coding module, we have functions that will construct a Huffman tree given a computed histogram. This function will build the tree and return the root node of the constructed tree. We will also have a function to populate a code table, putting in the symbols into the table, with one index for each possible symbol. Then we will have a dump tree function which will perform a post-order traversal of the Huffman tree rooted at the passed in root. It will write an 'L' followed by the byte of the symbol for each leaf, and then an 'I' for interior nodes. To rebuild the tree, it will reconstruct a Huffman tree given its post-order tree dump stored in the array. Finally, we have the function that will delete the tree.

###### encode.c
We will parse for arguments. Our encoder will read in a file to construct a histogram. Then, we construct a Huffman tree using a priority queue. We construct a code table by traversing the Huffman tree. We construct a header using our header files for what we need to put down. We will write this constructed header to the outfile and write the constructed Huffman tree to outfile. Then, startig at the beginning of infile, we write the corresponding code for each symbol to outfile. When we finish writing, we flush out any remainder bits.

###### decode.c
We will parse for arguments. Our decoder will check if the magic number matches the header from infile's magic number. The permissions field in the header indicates what permissions the outfile should have. Now we will read the dumped tree from infile into an array and reconstruct the Huffman tree. Then we will read one bit at a time from infile.

###### defines.h
This file contains macros that we will need to use throughout the program.

###### header.h
This is what we will use to construct our header.


### How to Run It

1. Compile the assignment files.
2. Run encode and/or decode along with any of these command-line options (if a bad option is inputted, a helpful message will be displayed).<br>
-h: Prints out a help message describing the purpose of the program and the command-line options it accepts, exiting the program afterwards. Refer to the reference program provided to you, for an idea of what to print.<br>
-i infile: Specifies the input file to encode using Huffman coding. The default input should be set as stdin.<br>
-o outfile: Specifies the output file to write the compressed input to. The default output should be set as stdout.<br>
-v: Prints compression statistics to stderr. These statistics include the uncompressed file size, the compressed file size, and space saving.<br>
	
	
### Bugs

I did not encounter any bugs, lest we count my own errors.


### Cite Sources

I used this [link](https://www.programiz.com/c-programming/library-function/ctype.h/iscntrl) to learn about iscntrl().

I used this [link](https://www.tutorialspoint.com/c_standard_library/c_function_tmpfile.htm) to learn about tmpfile().

I used this [link](https://www.programiz.com/c-programming/library-function/ctype.h/isprint) to learn about isprint().

I used this [link](https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/) and their respective man pages to learn about what these system calls do.

I used this [man page](https://man7.org/linux/man-pages/man2/lstat.2.html) to understand fstat().

I used this [link](https://man7.org/linux/man-pages/man3/fseek.3.html) to understand fseek() and lseek().

I used this [link](https://www.w3schools.com/python/ref_file_fileno.asp) to understand fileno.

I used this [man page](https://man7.org/linux/man-pages/man3/stdin.3.html) to help me understand more about STDIN_FILENO.

