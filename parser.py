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
    s = s.replace( 'Pi'   , str(math.pi) )
    s = s.replace( 'e'    , str(math.e)  )
    s = s.replace( 'sqrt' , 'r'  )
    s = s.replace( 'cos'  , 'c'  )
    s = s.replace( 'sin'  , 's'  )
    s = s.replace( 'tan'  , 't'  )
    s = s.replace( 'lg'   , 'g'  )
    s = s.replace( 'ln'   , 'l'  )
    s = s.replace( 'mod'  , 'm'  )

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
    
    n = len(line)    

    # TODO write a function that does a binary operation to reduce repitive code
    # process factorial a unary operator written after 
    x = 0
    while x < n:
        if line[x] == '!':
            line[x - 1] = math.factorial( x - 1 )
            line.pop(x)
            n -= 1
        else:
            x += 1

    # process unary minus
    x = 0
    while x < n:
        # error to check if float in string although I'd like it to return False here... could write function that does that
        if line[x] == '-' and (x == 0 or type(line[x - 1]) != float):
            line[x+1] = -line[x+1]
            line.pop(x)
            n -= 1
        else:
            x += 1

    # process exponent
    x = 0
    while x < n:
        if line[x] == '^':
            line[x+1] = line[x-1] ** line[x+1]
            line.pop(x)
            line.pop(x -1)
            n -= 2
        else:
            x += 1

    # proccess mod 
    x = 0
    while x < n:
        if line[x] == 'm':
            line[x+1] = line[x-1] % line[x+1]
            line.pop(x)
            line.pop(x - 1)
            n -= 2
        else:
            x += 1

    # proccess */
    x = 0
    while x < n:
        if line[x] == '*':
            line[x+1] = line[x-1] * line[x+1]
            line.pop(x)
            line.pop(x - 1)
            n -= 2
        elif line[x] == '/':
            line[x+1] = line[x-1] / line[x+1]
            line.pop(x)
            line.pop(x - 1)
            n -= 2
        else:
            x += 1
    # proccess +-
    x = 0
    while x < n:
        if line[x] == '+':
            line[x+1] = line[x-1] + line[x+1]
            line.pop(x)
            line.pop(x - 1)
            n -= 2
        elif line[x] == '-':
            line[x+1] = line[x-1] - line[x+1]
            line.pop(x)
            line.pop(x - 1)
            n -= 2
        else:
            x += 1
    return line








class Node(object):
    
    def __init__(self, data, parent=None, absval=False):
        self.data = data
        self.parent = parent
        self.absval = absval

    def addChild(self, data, absval=False):
        # we can think of everything is children
        child = Node(data, self, absval=absval)
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

def log10(x):
    return math.log(x,10)

ops = {
    'r' : math.sqrt,
    'c' : math.cos,
    's' : math.sin,
    't' : math.tan,
    'g' : log10,
    'l' : math.log,
    }


# recursive function to be called by parse
# look at a node, if it has a node in its data, call recurse on that
# after that process all remaining operators with brute_parse
def recurse( node ):
    if not node.data:
        return

    for d in node.data:
        if type(d) == Node:
            recurse( d )

    # pull children up
    for x,d in enumerate(node.data):

        if type(d) == Node:
            if d.absval == True:
                node.data[x] = abs(d.data[0])            
            else:
                node.data[x] = d.data[0]
            
        # if a function is called on something perform it        
        if type(node.data[x-1]) == str and node.data[x-1] in 'rcstgl':
            # we replace what the function has been called on with the return value
            node.data[x] = ops[ node.data[x-1] ](d.data[0])# <- this is a function call
            # remove the function call operator from the list
            node.data.pop(x-1)
    # reduce the data
    node.data = brute_parce(node.data)

# build a tree of parenthesis and call and pass to recurse
def parse( line ):
    root = Node([])
    pos = root    
    opening_abs = []

    for n, x in enumerate(line):
        if x == '(':
            pos = pos.addChild([])

        elif x == ')':
            pos = pos.parent

        # since abs open and close are both '|'
        # and they are nested in the test suite, this gives us a tricky problem
        # I guess we have to look at the operators for a hint
        # ex. ||2.24 / (-99)| + 29|
        # niave is ()2.24 / -99( + 29)
        # I'm sure its ((2.24 / -99) + 29) that is meant
        # here we see that if something comes before operator such as "a | + b", than it should be closing
        #  
        # this really breaks our analyze parens before operators first approach
        # reasonable behavior:
        #     first '|' is opening and last '|' is closing
        #     if there is a number or '(' or another '|' after an _OPENING_ '|', or  then it is opening
        #     otherwise it is closing 
        #     must check for unary minus

        
        elif x == '|':
            # last operation of '|' is closing
            if n == len(line) -1 or '|' not in line[n+1:]:
                pos = pos.parent
                continue
            # first | is always opening and if the preceding is an opening, note: empty '||' can break the parser
            elif not opening_abs or (n - 1) in opening_abs:
                pos = pos.addChild([], absval=True)
                opening_abs.append(n)
                continue    
            # check if there is another character and some
            elif n+1 < len(line) and n - 1 >= 0:
                # check for unary minus after the '|'
                if line[n + 1] == '-' and ( type(line[n - 1]) == float or line[ n - 1] == ')' ):
                    # then we check for a left val
                    # if the value on the left is a number or ')' then it is binary '-' and therefore '|' is closing
                    pos = pos.parent
                    continue
            else:
                pos = pos.addChild([], absval=True)
                opening_abs.append(n)
                continue  
            
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
    # In real life put in try blocks but I want errors now
    answer = parse( lex( lin ) )
    print roun(answer)
