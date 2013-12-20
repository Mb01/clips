#!/usr/bin/env python

import sys
import string
import re
import math


#    Pi        Pi number
#    e         Euler's number
#    sqrt()    Square root
#    cos()     Cosine
#    sin()     Sine
#    tan()     Tangent
#    lg()      Decimal logarithm
#    ln()      Natural logarithm
#1   ()        Brackets
#2   ||        Absolute value, e.g. |-5 - 10|
#3   !         Factorial
#4   -         Unary minus
#5   ^         Exponent
#6   mod       Modulus divide, e.g. 5 mod 2 = 1 (only integers will be supplied here)
#7   *, /      Multiply, Divide (left-to-right precedence)
#8   +, -      Add, Subtract (left-to-right precedence)


DIGITS = string.digits + '.'
# here we have Root, Cos, Sin, Tan, lG, Ln, Mod so one char lexer can be reused
OPERATORS = 'rcstglm||!()^*/+-'

def lex( s ):
    """ add things to the tree, only process parens """
    s.replace( 'Pi'   , str(math.pi) )
    s.replace( 'e'    , str(math.e)  )
    s.replace( 'sqrt' , 'r'  )
    s.replace( 'sin'  , 's'  )
    s.replace( 'tan'  , 't'  )
    s.replace( 'lg'   , 'g'  )
    s.replace( 'ln'   , 'l'  )
    s.replace( 'mod'  , 'm'  )

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






class Node(object):

    def __init__(self, data, parent=None):
        self.data = data
        self.parent = parent

    def addChild(self, data):
        # we can think of everything is children
        child = Node(data, self)
        self.data.append(child)
        return child

    def getTree(self):
        """list version of the tree"""
        result = []
        for child in self.data:
            if type(child) == Node:
                result.append(child.getTree())
            else:
                result.append(child)
        return result

#    sqrt()    Square root
#    cos()     Cosine
#    sin()     Sine
#    tan()     Tangent
#    lg()      Decimal logarithm
#    ln()      Natural logarithm
# here we have Root, Cos, Sin, Tan, lG, Ln, Mod so one char lexer can be reused

# here is where () are processed so functions should also happen here
# find value of each node with brute_parce() if it has no children, bottom up from left
def recurse( node ):
    if not node.data:
        return

    for d in node.data:
        if type(d) == Node:
            recurse( d )

    # pull children up
    for x,d in enumerate(node.data):
        if type(d) == Node:
            node.data[x] = d.data[0]
        if type(d) 
            

    # reduce the data
    node.data = brute_parce(node.data)

# build a tree of parenthesis and call a recursive function
def parse( line ):
    root = Node([])
    pos = root

    for x in line:
        if x == '(':
            pos = pos.addChild([])

        elif x == ')':
            pos = pos.parent

        else:    
            pos.data.append(x)

    recurse(root)
    return root.data[0]


def roun( num ):
    integerPart = ""
    decimalApprox = ""
    afterDot = False
    #break into parts
    for x in str(num): # note that number not made into a string here
        if afterDot == True:
            decimalApprox += x            
        elif x == '.':
            afterDot = True
        elif not afterDot:
            integerPart += x
    #eliminate trailing zereos
    while True:
        if not decimalApprox:
            break
        if decimalApprox[-1] == '0':
            decimalApprox = decimalApprox[:-1]
        else:
            break
    #round
    if len(decimalApprox) > 5:
        trunc = decimalApprox[:5]
        nex = decimalApprox[5]
        # must hold onto left zereos
        lefts = 0
        for x in trunc:
            if x == '0':
                lefts += 1
            else:
                break
        if int(nex) > 4:
            decimalApprox = decimalApprox = str(int(trunc) + 1)
        else:
            decimalApprox = str(int(trunc))
        # put zeroes back
        for x in range(lefts):
            decimalApprox = '0' + decimalApprox
    #put together
    if decimalApprox:
        return integerPart + '.' + decimalApprox
    return integerPart


f = open(sys.argv[1], 'r')
lines = [x.replace( '\n', '') for x in f if x != '\n']

for lin in lines:
    if not lin or lin == '\n':
        continue
    answer = parse( lex( lin ) )
    print roun(answer)

