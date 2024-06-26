# Refactor Practice

## Problem description

NTU Judge Girl problem 32. 

Given a string, output the longest substring such that it is consist of AB, where A and B are palindromes.

## Solution

By Manacher's Algorithm, we can find the longest palindrome in a string in O(n) time and O(1) space.

Then, we record the longest palindrome starting and ending with every position in the string.

After that, we can find the longest AB substring by enumerating all the possible ending positions of A.

## Refactor Progress

For exact code modification, please refer to commit history of main.cpp.

0. Initial solution written in 2021
1. Remove all global variables and swiched to 0-based array
2. Turn similar code into a function
   - I found that the code to find the longest palindrome starting with every position in the string is very similar to the code to find the longest palindrome ending with every position in the string.
   - Knowing that finding the longest palindrome ending with every position is euqal to finding the longest palindrome starting with every position with the reversed string, I decided to turn the code to find the longest palindrome starting with every position into a function.
3. Wrap answer generation into a function
   - Originally, I did answer generation in the main function.
   - I found that it is better to wrap the answer generation into a function for better readability.
4. Remove everything but io in the main function
   - Wrap everything into functions.
   - I only need to call find longest two palindrome function in the main function to get the answer.
   - What I have to do is input and output in the main function.
5. Slight modification to the manacher's algorithm
   - Reuse the length of manacher array, which is 2 * n + 1.
6. Wrap functions into classes and define public/private variables and functions.
   - Object-oriented program principle
   - More organized and encapsulated code.