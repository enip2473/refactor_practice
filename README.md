# Refactor Practice

## Problem description

NTU Judge Girl problem 32. 

Given a string, output the longest substring such that it is consist of AB, where A and B are palindromes.

## Solution

By Manacher's Algorithm, we can find the longest palindrome in a string in O(n) time and O(1) space.

Then, we record the longest palindrome starting and ending with every position in the string.

After that, we can find the longest AB substring by enumerating all the possible ending positions of A.

## Refactor Progress

1. Initial solution written in 2021