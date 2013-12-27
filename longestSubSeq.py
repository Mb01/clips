#!/usr/bin/env python

import sys
import math

"""
Longest Common Subsequence
Challenge Description:

You are given two sequences. Write a program to determine the longest common subsequence between the two strings (each string can have a maximum length of 50 characters). NOTE: This subsequence need not be contiguous. The input file may contain empty lines, these need to be ignored.

Input sample:

The first argument will be a path to a filename that contains two strings per line, semicolon delimited. You can assume that there is only one unique subsequence per test case. E.g.

XMJYAUZ;MZJAWXU

Output sample:

The longest common subsequence. Ensure that there are no trailing empty spaces on each line you print. E.g.

MJAU
"""

# brute force doesn't work becuase it's 2**n
# so we use dynamic programming 

f = open(sys.argv[1], 'r')
# lines becomes a list of strings representing each line with the newline removed
lines = [x.replace('\n', '') for x in f if x != '\n']

def dynSubSeq( le, ri ):
    
    table = [[0 for x in range(len(ri)+1)] for y in range(len(le)+1)]# note to self No!: table = [[None]*(len(ri)+1)]* (len(le)+1) 

    for x in range(len(le)+1):

        for y in range(len(ri)+1):
            # zero items = zero possibilities
            if x == 0 or y == 0:
                table[x][y] = 0
            # include the item?
            elif le[x-1] == ri[y-1]:
                table[x][y] = 1 + table[x-1][y-1]
            # which was better?
            else:              
                table[x][y] = max(table[x-1][y], table[x][y-1])
    return table

def readBack( table, le, ri ):
    result = ""
    x, y = len(le), len(ri) # we have to read backwords 
    while x != 0 and y != 0:

        if table[x][y] == table[x-1][y]:
            # nothing changed and left was better
            x -= 1
        elif table[x][y] == table[x][y-1]:
            # nothing changed and up was better    
            y -= 1
        else:
            # we included the item at elif le[x-1] == ri[y-1]:
            result = le[x-1] + result
            x -= 1
            y -= 1
    return result

for lin in lines:
    if lin == "\n":
        continue
    le, ri = lin.split(';')
    table = dynSubSeq(le,ri)
    print readBack(table, le, ri)
