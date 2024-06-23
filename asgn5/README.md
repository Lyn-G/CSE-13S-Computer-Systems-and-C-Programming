### Description of the Assignment

We are to create a key generator, an encryptor, and a decryptor.
This is along with an RSA library and a numerical library that holds many functions needed for the above.


### How I Built It

For the numerical library, I followed the pseudocode provided to us.
For modular exponentiation, I had to perform exponentiation by squaring and reducing the results by the modulo.
For modular inverse, we must divide multiple variables various times before reaching an if-statement for the conclusion if they are inverse or if they are not.
GCD's function was relatively easy to build using the pseudocode.
I had to do modulus for the inputs passed through to us, which would then be checked in the loop's condition if they were to continue.
The function to check if a number was prime was the most complicated to code. 
We are to return a boolean of either true or false depending if the number passed through is prime or not.
We must first hard-code the smaller prime numbers so that it will be checked.
We must set various mpz_t variables for small operations, such as n - 1 or s - 1.
We will compare the passed-in number to see if it's modular value is satisfactory to the loop's conditions.
Then there's the function for making a prime integer.
Inside this function, we need to test using is_prime()'s function using the iterations specified for us.
The number of bits must be the amount-of-bits-given-to-us long.
The while-loop will continue running until the boolean is changed to true.
The only way for the boolean to be changed to true would be if the number is prime and the bits for that value is satisfactory.

For RSA's library, I followed the instructions in the assignment document.
For the first function, rsa_make_pub(), we must create prime numbers for p and q. 
The range for p's bits is nbits/4,(3×nbits)/4) inclusive.
All remaining bits will be given to q.
We need to use random() function for this formula.
Then we need to compute the least common multiple of (p-1)(q-1).
This is done using our GCD function.
Now we use another random function, called mpz_urandomb().
This is to generate the exponent.
The function for making the private is similar, however we need to do multiplication and modular inverse for (p-1)(q-1).
For all the writing and reading the public and private files, that was done with gmp_fprintf() and gmp_fscanf() for all the necessary variables.
RSA encryption and decryption require that we use our power modular function.
This is the same case for our user signature.
In rsa_verify(), we check if out output matches the output of power modular.
If it does, it returns the boolean associated with that.
Now for actually encrypting the file, we must set variables for both the message and the cypher. 
The block size must be calculated using the given function.
We will need to dynamically allocate memory for this, just in case.
Set the zeroth byte to 0xFF.
Since all strings end with '\0', we will set the last byte to be that value for termination.
Create a while-loop that goes through the entire file.
Read the blocks in the file while also putting in a newline after each block.
Then we can convert the read bytes into an mpz_t m.
This leads to encrypting m with our rsa_encrypt(), then writing the encrypted number to our outputting file as a hexstring following by a trailing newline.
Our decrypting file works using almost the same procedure, but uses the decrypting methods instead.

For our key generator, we use getopt() to parse through the command-line options and handling them accordingly.
Using fopen(), we will print a helpful error and exit the program.
Using fchmod() and fileno(), we will need to set the private key files to 0600.
Initialize the random state using randstate_init(), using the set seed.
Make the public and private keys using rsa_make_pub() and rsa_make_priv(), respectively.
Get the current user’s name as a string. You will want to use getenv().
Convert the username into an mpz_t with mpz_set_str(), specifying the base as 62. Then, use rsa_sign() to compute the signature of the username.
Write the computed public and private key to their respective files.
Write out the verbose if user has specified so.

For our encryptor, we use getopt() to parse through the command-line options and handling them accordingly.
Open the public key file using fopen(). Print a helpful error and exit the program in the event of failure.
Read the public key from the opened public key file.
Print out the verbose is specified.
Convert the username that was read in to an mpz_t.
Verify the signature using rsa_verify(), reporting an error and exiting the program if the signature couldn’t be verified.
Encrypt the file and close the public key file.

For our decryptor, we use getopt() to parse through the command-line options and handling them accordingly.
Open the private key file using fopen(). Print a helpful error and exit the program in the event of failure.
Read the private key from the opened private key file.
Print out the verbose if the user specified.
Decrypt the file and close the private key.


### How to Run It

1. Compile the assignment files.
2. Run keygen along with any of the option commands:
	-b: specifies the minimum bits needed for the public modulus n(default: 1024).
	-i: specifies the number of Miller-Rabin iterations for testing primes (default: 50).
	-n pbfile: specifies the public key file (default: rsa.pub).
	-d pvfile: specifies the private key file (default: rsa.priv).
	-s: specifies the random seed for the random state initialization (default: the seconds since the UN I X epoch, given by time(NULL)).
	-v: enables verbose output.
	-h: displays program synopsis and usage.
3. Then run encryptor along with any of the option commands:
	i: specifies the input file to encrypt (default: stdin).
	-o: specifies the output file to encrypt (default: stdout).
	-n: specifies the file containing the public key (default: rsa.pub).
	-v: enables verbose output.
	-h: displays program synopsis and usage.
4. Then run decryptor along with any of the option commands:
	-i: specifies the input file to decrypt (default: stdin).
	-o: specifies the output file to decrypt (default: stdout).
	-n: specifies the file containing the private key (default: rsa.priv).
	-v: enables verbose output.
	-h: displays program synopsis and usage.


### Bugs

I did not encounter any bugs, lest we count my own errors.


### Cite Sources

Resources that I used:
I used this [resource](https://www.w3resource.com/c-programming/c-printf-statement.php) to help me remember printing formats. 

Though it was given to us in the assignment document, I shall still cite it [here](https://gmplib.org/manual/).

I used this [link](https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm) to read the file.

I used this [link](https://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm) to understand how seeking in files work.

I used the [link](https://www.tutorialspoint.com/c_standard_library/c_function_ftell.htm) to help me figure out the size of the files, specifically the bytes.

I used the [link](https://www.tutorialspoint.com/c_standard_library/c_function_rewind.htm) to figure out how to reset back to the beginning of the file after going through it.

I used this [link](https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html) to figure out how to set file permissions.

I used this [link](https://www.tutorialspoint.com/c_standard_library/c_function_feof.htm) to learn about end-of-file indicator for the given stream..

