### Description of the Assignment

Create a small numerical library that also comes with a test harness that will be used to test the math functions. We are to implement sin, cos, arcsin, arccos, arctan, and log. We will compare our implemented functions to the ones in the <math.h> library and output them into a table to see the differences.


### How I Built It

Using the formulas for each of the needed functions, I was able to use for-loops and do-while loops to accomplish them.
Some of them didn't need loops to begin with and could use previous functions to find the value.
I had to include functions from class sources for things like square root and exponential function.
I got these from people such as from Professor Long and TAs.

I created the testing harness to output my function's results along with the math library's function's results into a table and
to show the difference between my own and theirs.
A thing to note about the testing harness:
I created a boolean variable for each of the functions, except -a.
I set these all to false.
When they ran through in their own case or in -a's case, the variable would then be set to true.
Since I've put if statements in all cases to check if the boolean is false before proceeding,
this allows only one of the functions to run if -a were put down along with any other of the commands.


### How to Run It

1. Compile the assignment files.
2. Run ./mathlib-test along with any of these commands.
-a: to run all tests.
-s: to run sin tests.
-c: to run cos tests.
-S: to run arcsin tests.
-C: to run arccos tests.
-T: to run arctan tests.
-l: to run log tests.


### Bugs

I did not encounter any bugs, lest we count my own errors.


### Cite Sources

I’d like to cite Professor Long’s absolute value function that he provided from Piazza. I used this for my assignment.

The [square root function](https://piazza.com/class/l8ahj4fji3i4om/post/150) that we can use was shared to us in Piazza as well. 

I also used [this](https://www.javatpoint.com/c-boolean) to figure out how to incorporate Boolean in C.

[This website](https://web.mat.bham.ac.uk/R.W.Kaye/numerics/errors.html) was used to help me understand more about errors in my assignment.
