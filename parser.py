#!/usr/bin/env python

import sys
import string

#1 () Brackets
#2 - Unary minus
#3 ^ Exponent
#4 *, / Multiply, Divide (left-to-right precedence)
#5 +, - Add, Subtract (left-to-right precedence)


# I started with a tree based approach like this

class Node(object):
    def __init__(self):
        self.left = None
        self.right = None
        self.data = None
        self.parent = None

    def addChild(self, data):
        if not self.left:
            self.left = Node()
            self.left.parent = self
            self.left.data = data
            return self.left
        elif not self.right:
            self.right = Node()
            self.right.parent = self
            self.right.data = data
            return self.right
        else:
            raise Exception

    def isRightChild(self):
        if not self.parent:
            return False
        if not self.parent.right == self:
            return False
        return True
    
    def swap(self, other):
        """swaps the whole branch"""
        # 1 swap selfs left/right and 2 swap others left/right
        # 3 swap self and 4 swap others parents
        #1
        if self.isRightChild():
            self.parent.right = other
        else:
            self.parent.left = other
        #2
        if other.isRightChild():
            other.parent.right = self
        else:
            other.parent.left = self
        #3
        temp = self.parent
        self.parent = other.parent
        #4
        other.parent = temp.parent
    
    def remove(self):
        """removes the whole branch"""
        if self.isRightChild():
            self.parent.right = None
        else:
            self.parent.left = None
        self.parent = None

    def appendTo(self, parent):
        """appends the whole branch"""
        self.parent = parent
        if not self.parent.left:
            self.parent.left = self
            return
        if not self.parent.right:
            self.parent.right = self
            return
        raise Exception

    def printAll(self):
        """prints the subtree from node from left"""
        if self.data:
            print self.data
        if self.left:
            self.left.getTree()
        if self.right:
            self.right.getTree()

    def getTree(self):
        """list version of the tree"""
        result = []
        if self.data:
            result.append(self.data)
        if self.left:
            result.append(self.left.getTree())
        if self.right:
            result.append(self.right.getTree())
        return result

DIGITS = string.digits + '.'
OPERATORS = '^*/+-'#here we leave out () to proc seperately

def old_lex( s ):
    """ add things to the tree, only process parens """
    root = Node()
    pos = root
    #temp for digits
    temp = ""
    for x in s:
        # Is there any way to make reading digits more straightforward while forloop is for x in s?
        if x in DIGITS:
            temp += x
            continue
        # first not in digits and there are digits to add
        elif temp:
            # but this way we have to flush at the end to catch a digit at the end
            pos = pos.addChild(float(temp))# should we look
            temp = ""
        if x == ' ':
            continue
        if x in OPERATORS:
            pos = pos.addChild(x)
        if x == '(':
            pos = pos.addChild('(')
            continue
        if x == ')':
            while pos.data != '(':
                pos = pos.parent
                if pos.parent == None:
                    raise Exception("unmatched closing paren")
            # so we can check for unclosed parens
            pos.data = ')'
    if temp:
        pos.addChild(float(temp))
    # root always only has a left child so do we need it?
    return root.left


#
#
#
# but I have a list based solution that should work and is easier to code
# for this example

DIGITS = string.digits + '.'
OPERATORS = '()^*/+-'

def lex( s ):
    """ add things to the tree, only process parens """
    result = []
    #temp for digits
    temp = ""
    for x in s:
        # Is there any way to make reading digits more straightforward while forloop is for x in s?
        if x in DIGITS:
            temp += x
            continue
        # first not in digits and there are digits to add
        elif temp:
            # but this way we have to flush at the end to catch a digit at the end
            result.append(float(temp))
            temp = ""
        if x == ' ':
            continue
        if x in OPERATORS:
            result.append(x)
    if temp:
        result.append(float(temp))
    # root always only has a left child so do we need it?
    return result

def brute_parce( line ): 

    # process unary minus
    for x in range(len(line)):
        # error to check if float in string although I'd like it to return False here... could write function that does that
        if line[x] == '-' and (x == 0 or type(line[x - 1]) != float):
            line[x+1] = -line[x+1]
            line[x] = None

    line = [x for x in line if x != None]

    # process exponent
    for x in range(len(line)):
        if line[x] == '^':
            line[x+1] = line[x-1] ** line[x+1]
            line[x], line[x-1] = None, None

    line = [x for x in line if x != None]

    # proccess */
    for x in range(len(line)):
        if line[x] == '*':
            print line
            line[x+1] = line[x-1] * line[x+1]
            line[x], line[x-1] = None, None
        elif line[x] == '/':
            line[x+1] = line[x-1] / line[x+1]
            line[x], line[x-1] = None, None
    
    line = [x for x in line if x != None]
    
    # proccess +-
    for x in range(len(line)):
        if line[x] == '+':
            line[x+1] = line[x-1] + line[x+1]
            line[x], line[x-1] = None, None
        elif line[x] == '-':
            line[x+1] = line[x-1] - line[x+1]
            line[x], line[x-1] = None, None

    line = [x for x in line if x != None]

    return line

def parse( line ):
    root = Node()
    pos = root
    for x in line:
    if x == '(':
            pos = pos.addChild('(')
            continue
        if x == ')':
            pos = pos.parent

a = lex("-2-3")
print parse(a)
a = lex("2+3*5")
print parse(a)
a = lex("((-2 + 3 + 4) * -3 + 5)")
print parse(a)
#print a

exit()

f = open(sys.argv[1], 'r')
lines = [x.replace( '\n', '') for x in f if x != '\n']

for lin in lines:
    if not lin or lin == '\n':
        continue
    parse( lin )
