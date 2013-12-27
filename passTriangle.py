#!/usr/bin/env python

import sys
"""
Challenge Description:

By starting at the top of the triangle and moving to adjacent numbers on the row below, the maximum total from top to bottom is 27.

   5
  9 6
 4 6 8
0 7 1 5

5 + 9 + 6 + 7 = 27

Input sample:

Your program should accept as its first argument a path to a filename. Input example is the following

5
9 6
4 6 8
0 7 1 5

You make also check full input file which will be used for your code evaluation.

Output sample:

The correct output is the maximum sum for the triangle. So for the given example the correct answer would be

27
"""

#   a
#  b c
# d e f

# we know we start at a
# then we know the best path to b is a b and c is a c

# then we know abd is the best to d and acf is the best to f but...

# we can look at b and c to see which path is the best to e


class Node:
    """special triangle tree Node"""
    def __init__(self,value):
        self.value  = int(value)
        
        self.right_parent = None
        self.left_parent  = None
        
        self.left   = None
        self.right  = None
        
        self.best_path = None
        self.best_value = None

    def addToPath(self, parent):
        self.best_path = parent.best_path[:]
        self.best_path.append(self)
        self.best_value = parent.best_value + self.value
        
    def calcBestPath(self):
        # compare both parents to see which one is best, add that one
        if self.left_parent and self.right_parent:
            if self.left_parent.best_value >= self.right_parent.best_value:
                self.addToPath(self.left_parent)
                return
            if self.left_parent.best_value < self.right_parent.best_value:
                self.addToPath(self.right_parent)
                return
        if self.left_parent:
            self.addToPath(self.left_parent)
            return
        if self.right_parent:
            self.addToPath(self.right_parent)
            return
        # else it's root
        return

def findPath( root ):
    # initialize root
    root.best_path = [root]
    root.best_value = root.value
    next = [root.left, root.right]
    # do for each level in the triangle
    while True:
        temp = set()
        for x in next:
            x.calcBestPath()
            temp.add(x.right)
            temp.add(x.left)
        
        if None in temp:
            return next
            
        next = list(temp)

# setup the data structure
last = []
root = None
data = open(sys.argv[1], 'r')
for line in data:
    line = line.replace('\n', '')
    if not line:
        continue
    line = line.strip()
    line = line.split(' ')
    # case: first, than we need to initialize the triangle tree
    if not last:
        root = Node(line[0])
        last.append(root)
        continue
    # build a list of elements to add
    for x, el in enumerate(line):
       line[x] = Node(el)
    # no hook them together
    for x, parent in enumerate(last):
        parent.left = line[x]
        parent.right = line[x+1]
        parent.left.right_parent = parent
        parent.right.left_parent = parent
    # setup for next iteration
    last = line
    
last_row = findPath(root)
last_row = [x.best_value for x in last_row]

answer = max(last_row)
print answer

data.close()
