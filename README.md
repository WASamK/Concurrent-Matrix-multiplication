# CS4532-Concurrent-Programming-Lab4-5


Tasks
1. Write a sequential program to perform matrix-matrix multiplication
 Dimensions of each matrix is n×n and elements/values of the matrix are of type Double.
 Populate each matrix with randomly generated Double values.
 Add necessary code to measure the time taken by the matrix-matrix multiplication. Do not
measure the time to create matrixes and populate them with values.
 The program should be written in C++ targeting the Linux environment.
2. Identify a suitable library for C++ and Linux environment that supports “parallel for” loops.
3. Write another C++ program to perform the matrix-matrix multiplication using a “parallel for”
loop.
4. Run both sequential and parallel-for versions of your program while changing the matrix size n
from 100 to 1,000 in steps of 100.
[10 marks]
 Record the time to perform matrix-matrix multiplication for each execution.
 Collect sufficient number of samples for each configuration of n, while making sure your
performance results are within an accuracy of ±5% and 95% confidence level.
 Plot the matrix-matrix multiplication time against increasing n.
 Plot speed up against increasing n.
5. Find out about the architecture of the CPU that you used for the evaluation.
[5 marks]
 Find out CPU model, no of cores, no of hardware-level threads, cache hierarchy, hardware
optimizations, etc.
 Can you justify the gained speed up knowing the architecture of the CPU?
 Discuss your observations in detail while relating the observed behavior in graphs to the
architecture of the CPU.
6. Find out at least two ways to optimize matrix-matrix multiplication.
 Briefly describe a possible technique(s) while giving references.
7. Write another C++ program to perform the matrix-matrix multiplication using a “parallel for” loop
and a suitable optimization techniques.
[10 marks]
8. Run the new program and plot the results as described in Step 4.
9. Describe your observations in relation to the optimization technique(s) you selected and CPU
architecture as in Step 5.
