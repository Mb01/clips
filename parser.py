#!/usr/bin/env python

import sys
import string

#1   ()       Brackets
#2   -        Unary minus
#3   ^        Exponent
#4   *, /     Multiply, Divide (left-to-right precedence)
#5   +, -     Add, Subtract (left-to-right precedence)

# ((-2 + 3) * -3 + 5)

# Make a tree like this
#                               (   )
#                               /
#                              +
#                             / \ 
#                            *   5
#                           / \
#                         ( ) -3   
#                         /      
#                        +   
#                       / \     
#                     -2   3  
#                     
# If we just add, backing up at ')' we get this 
#                               R
#                             ( )
#                            /  \
#                           ()  * 
#                          -   -
#                         2   3
#                        +   +
#                       5   5


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

def operatorUp( pos ):
    if pos.isRightChild():
        parleft = pos.parent.left
        parleft.remove()
        parleft.appendTo(pos)

def lex( s ):
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
        if x in '^*-+':
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



a = lex("2345345-345331")
[[2345345.0, ['-', [345331.0]]]]
print a.getTree()
a = lex("-2-3")
print a.getTree()
a = lex("2+3*5")
print a.getTree()
a = lex("((-2 + 3 + 4) * -3 + 5)")


print a.getTree()

exit()

f = open(sys.argv[1], 'r')
lines = [x.replace( '\n', '') for x in f if x != '\n']

for lin in lines:
    if not lin or lin == '\n':
        continue
    parse( lin )
