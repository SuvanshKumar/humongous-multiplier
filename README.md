# Humongous Multiplier
Multiplication of two 1-million digit numbers, exploring the usage of multi-threading

# Names of Input Files-
        input1.txt
        input2.txt 

# Output File name-
        single_multiplied.txt
        multithreaded_multiplied.txt

Some Details for Input and Output files for Results are also provided in description.txt

# How to use the code:
        Compile:
                gcc prog1.c -o prog1.out
                gcc prog2.c -o prog2.out -lpthread
        Run :
                ./timeit.sh

# Error Checking:
        If the thread count less than 0 and greater than 100. Provide Default thread count to 8

# Results and Conclusions:
        The code was tested on different files from 1 digit to 1 million digits multiplication.
        For example for multiplication of A (10^5 digit number) X B(10^5 digit number) took time of 900 seconds in single thread and in multi threading it took approximately 820 seconds.
        In another example run, multiplication of A (10^6 digit number) X B(10^6 digit number) took time of 2 hours 27 minutes in single thread and with multi threading it took aapproximately 2 hours 23 minutes.

        Hardware specifications of the machine on which the testing was done:
                CPU: Intel© Core™ i5-4210U CPU @ 1.70GHz × 2 (Dual core)
                Memory: 3.8 GB
                Hard Drive: 973.3 GB
                Operating System: Linux Mint 19.1 Cinnamon