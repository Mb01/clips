#encodes a vigenere cypher


#probably want file input option...

import string

alphabet = list(string.lowercase[:26])

while True:
    plaintext = raw_input('What is the plaintext? ')
    plaintext = plaintext.lower()    
    plaintext = plaintext.replace(' ','')
    key = raw_input('What is the key? ')
    key = key.lower()    
    key = key.replace(' ','')
    plain_positions = []
    
    #first get positions of plaintext letter
    for letter in plaintext:
        plain_positions.append(alphabet.index(letter))
    key_positions = [] 
    for letter in key:
        key_positions.append(alphabet.index(letter))
    #iterate over each
    key_pos = 0
    output = ""
    for plain_position in plain_positions:
        output += alphabet[(key_positions[key_pos] + plain_position) % 26]
        key_pos = (key_pos + 1) % len(key_positions)
    print output
