### Description of the Assignment

We are to implement shell sort, bubble sort, quick sort, and heap sort algorithms in C using the information from the assignment and the Python pseudocode given to us.
The program will print out, depending on the commands given to it, the sorting algorithm, along with the amount of elements, the amount of moves, and the amount of comparisons it had to do for that array. 


### How I Built It

Since we were given Python pseudocode for all the sorting algorithms, I used those to create my C code. Of course, there were many
changes I had to make since they are two very different languages. We had to allocate memory for our arrays and for the structs
given to us.

For shell sort, there was a generator in the Python code, which is something that C does not have. We have to create our own
function for that. I used an if-statement to create the gaps in sorting procedure. We have to use loops to decrease the iteration
since it needs to compare pairs that are far apart at a time. This iteration will continue until 1 is reached. Our gap begins with
5n/11. We will need to use the swap and compare functions given to use to figure out if values need to be swapped in the array.
We use for-loops and while-loops to run through the array and as indexing variables to access the array.

For bubble sort, we start off by looking at the first element in the array and looking at the one after that. If the first value
is larger than the second, it will be swapped. This continues on until the largest value is at the end of the array. Since we
understand that the last element is the largest, we will do the process again, but stop at the second-last item. For this process,
we must use for-loops as the indexing variable and to run through the array. We will also use a boolean that's set to false
beforehand. If we go through the entire array without swapping, we set the boolean to true, which causes us to break out of the 
loop. This is good so that the loops do not have to go through the entire thing if it's already sorted.

For quick sort, we have to first import our shell sort. This is because we want shell sort to run if the amount of elements in the
array is less than 8. This is for efficiency. We will use many variables to hold indexing variables for the left mark and right
mark, as well as the pivot. These will all be compared with one another to see if the left side is larger or smaller than the
right side. It will also check the array value at those indexes to see if those values do indeed need to be moved. We also need to 
call the function recursively, which is an issue since my approach requires more arguments than the quick sort function given to 
us. This is why we need to create another function that can take in those arguments. This function
will call each other.

For heap sort, we have to create many functions to build, fix, and go up & down the heap. These function provide us with the 
elements and their values. In each one, we will compare the parent and their children. Since we are building a min heap, we want
to check if the parent is smaller than the children. If not, then the children must climb and compare themselves with the other 
nodes to see where they belong on the tree. We need to create two arrays for this, one for the array as it is and the sorted 
array. 


### How to Run It

1. Compile the assignment files.
2. Run ./sorting along with any of the commands for the sorting algorithms. There are also options that can be placed to change
the seed, the amount of elements in the array, and many more. If an invalid option is put down, our program usage help page will
be displayed. 
-a : Employs all sorting algorithms.

-s : Enables Shell Sort.

-b : Enables Bubble Sort.

-q : Enables Quick Sort.

-h : Enables Heap Sort

-r seed : Set the random seed to seed. The default seed should be 13371453.

-n size : Set the number of elements in the array to size. The default size should be 100. The range of valid input is 1 ≤n ≤250, 
000, 000 where n is the size specified.

-p elements : Print out elements number of elements from the array. The default number of elements to print out should be 100. 

-H : Prints out program usage.


### Bugs

I did not encounter any bugs, lest we count my own errors.


### Cite Sources

Resources that I used:
I used this [link](https://www.tutorialspoint.com/cprogramming/c_structures.htm) to help me understand structures in C more.


I used this [link](https://learn.parallax.com/tutorials/language/propeller-c/propeller-c-simple-protocols/spi-example/bit-masks-better-code) to help me understand more about masking and how to do it.

I used this [link](https://www.tutorialspoint.com/c_standard_library/c_function_puts.htm) to teach me about puts, which is a very helpful tool for debugging (so I don’t always have to do printf).

I would like to mention that my other class that I’m currently taking, CSE 30, also goes through different sorting algorithms in Python. I used that knowledge from that class to help me understand the quick sort algorithm in C that I have created. I have linked the [Google Colab](https://colab.research.google.com/drive/1jfk6wrSwB9m7fOYWbtv4MUIqEoDvRd0f?usp=sharing#scrollTo=5GLWg7vlSREC) that my professor uses to teach Python lessons. 

I used [this](https://www.gnu.org/software/gawk/manual/html_node/Getopt-Function.html) to help me learn about opterr and how I use it for this assignment. I ended up not using it, but I shall still cite it here.

