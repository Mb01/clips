import string
import random
import os
import re

def moveToBaseDir():
    drivePrefix = os.path.splitdrive(os.getcwdu())[0]
    os.chdir(drivePrefix+ '\\')
#get the input
moveToBaseDir()
os.chdir("programs")
text = open("input.txt", "r").read().split(' ')

puzzle_size = int(raw_input("dimensions"))
puzzle = []

a_word_too_big = False
for word in text:
    if len(word) > puzzle_size:
        print ' '.join([word, 'is', str(len(word)), 'characters long and the puzzle', str(puzzle_size)])
        a_word_too_big = True
if a_word_too_big:
    print "Aborting process"
    exit()
#None or '' for empty squares? which will require more verbose programming
for x in range(puzzle_size):
    puzzle.append([None for y in range(puzzle_size)])

def getColumn(puzzle, colNumber):
    return [x[colNumber] for x in puzzle]

def getColumns(puzzle):
    return [getColumn(puzzle, x) for x in range(len(puzzle[0]))]

def getAscendingDiagonals(puzzle):#works only for squares
    """-> all ascending diagonals, just rotate 90 to get descending"""
    dimension = len(puzzle[0])
    result = []
    coords = [(x, y) for y in range(dimension) for x in range(dimension)]
    #number of  diagonals is (x - 2) * 2 + 1
    numdiags = (dimension - 2) * 2 + 1
    #sum of ascending diagonals left-right is always the same
    for x in range(1, numdiags+1):
        result.append([a for a in coords if sum(a) == x])
    #pop off the corners which are 1 in length
    result = [x for x in result if len(x) != 1]
    #dereference the coordinates
    for diag in range(len(result)):
        for cell in range(len(result[diag])):
            x,y = result[diag][cell]
            result[diag][cell] = puzzle[x][y]
    return result

def getAllDiagonals(puzzle):
    rotated = getColumns(puzzle)
    rotated.reverse()
    return getAscendingDiagonals(puzzle) + getAscendingDiagonals(rotated)

def maxConsecutiveEmpty(lis):
    """->(endposition, length) in the list of the longest stretch of Nones"""
    high_score = 0
    temp_score = 0
    endpos = 0
    for x in range(len(lis)):
        if not lis[x]:
            temp_score += 1
        else:
            if temp_score > high_score:
                high_score = temp_score
                endpos = x
                temp_score = 0
            else:
                temp_score = 0
    #case: max run at end
    if temp_score > high_score:
        high_score = temp_score
        endpos = len(lis)
    return (endpos, high_score)
    
""" Note to self. I'm going to prototype something that gets
    some of the words into the puzzle so I can experiment with
    the whole process of generating the puzzle"""

text.sort(lambda x,y: cmp(len(x), len(y)))

row = 0
col = 0
while row < puzzle_size:
    try:
        word = text.pop()
    except:
        if len(text) == 0:
            break
    if len(word) > puzzle_size - col:
        row += 1
        col = 0
    else:
        for letter in word:
            print row, col
            puzzle[row][col] = letter
            col += 1

for row in puzzle:
    print row
