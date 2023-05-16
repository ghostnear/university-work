# :computer: Assignment 04 - Problem Solving Methods

## Requirements
- You will have to solve two problem statements from the list below, one using the **backtracking** programming method and one using the **dynamic programming** method.
- For the backtracking problem, implement both an iterative as well as a recursive algorithm (**deadline is week 5**).
- For the dynamic programming problem, implement both the naive, non-optimized version as well as the dynamic programming version (**deadline is week 6**). 
- For the dynamic programming implementation, display the data structure used to memorize the intermediate results and be able to explain how it works. 
- For all implementations understand and be able to explain the computational complexity with regards to runtime.

## Problem Statements
### Backtracking
1. A number of `n` coins are given, with values of a<sub>1</sub>, ..., a<sub>n</sub>  and a value `s`. Display all payment modalities for the sum `s`. If no payment modality exists print a message.

### Dynamic Programming
5. Maximize the profit when selling a rod of length `n`. The rod can be cut into pieces of integer lengths and pieces can be sold individually. The prices are known for each possible length. For example, if rod length `n = 7`, and the price array is `price = [1, 5, 8, 9, 10, 17, 17]` (the price of a piece of length `3` is `8`), the maximum profit is `18`, and is obtained by cutting the rod into 3 pieces, two of length two and one of length 3. Display the profit and the length of rod sections sold to obtain it.