#!/usr/bin/env python

import sys
import string

#1 () Brackets
#2 - Unary minus
#3 ^ Exponent
#4 *, / Multiply, Divide (left-to-right precedence)
#5 +, - Add, Subtract (left-to-right precedence)


class Node(object):

    def __init__(self, data):
        self.data = data
        self.parent = None
        self.children = []

    def addChild(self, data):
        child = Node(data)
        self.children.append(child)
        return child

    def getTree(self):
        """list version of the tree"""
        result = []
        if self.data:
            result.append(self.data)

        for child in children:
            result.append(child.getTree())
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
    root.data = []
    pos = root
    # go down the path
    for x in line:
        if x == '(':
            pos = pos.addChild([])
            continue
        if x == ')':
            pos = pos.parent
            continue
        pos.data.append(x)
    
        

a = lex( "(1) + (2) + (3)" )
print parse(a)
#a = lex("-2-3")
#print parse(a)
a = lex("2+3*5")
print parse(a)

a = lex("(2+3)*5")
print parse(a)
exit()
#a = lex("((-2 + 3 + 4) * -3 + 5)")
#print parse(a)
#print a

exit()

f = open(sys.argv[1], 'r')
lines = [x.replace( '\n', '') for x in f if x != '\n']

for lin in lines:
    if not lin or lin == '\n':
        continue
    parse( lin )
