#funcs for decrypt
#

#
#
def devide_into_parts( input_string ):# "61626364" -> ["61","62","63","64"]
	result = []
	i = 0
	while i < len( input_string ):
		result.append(input_string[i:i+2])
		i += 2
		
	return result# like -> ["61", "6a","63"]

def makeString( input_list ):#turn list of numbers into hex strings
	result = []
	for x in range( 0,len(input_list) ):
		result.append( hex(input_list[x]) )
	return result #should be in form [ string, string, string, ... ]

def formatString( input_list ):# remove the '0x' and the L at the end, break into chunks of two
	result = []
	
	for element in input_list:# element = "0x616a63L" result = [ ["61","6a","63"] ]
		element = element[2:-1]
		
		element = devide_into_parts( element )
		
		result.append( element )
	return result

def repCon( oneChar ):# "a" -> 10
	oneChar = ord(oneChar)
	if oneChar > 96:
		oneChar -= 87
	else:
		oneChar -= 48
	return oneChar

def make_integer( input_list ):# [["34", "6a", ...], ...] -> [[0x34,0x6a,...],...]
	result = []
	for element in input_list:#element = ["34","6a",...]
		current_element = []
		for pair in element:#pair = "34"
			
			value = repCon(pair[0])*0x10 + repCon(pair[1])#Could change this to anything...
			
			current_element.append(value)
		result.append(current_element)
	return result
	
def perform_on_all_pairs( function, input_list ):#the function !!MUST!! return the new value
	result = []
	for element in input_list:#element = ["34","6a",...]
		current_element = []
		for pair in element:#pair = "34"
			
			value = function(pair)
			
			current_element.append(value)
		result.append(current_element)
	return result



	
#Preliminary decryption functions

def getColumn( n, ciphers ):#gets the nth byte of each ciphertext
	result = []
	for element in ciphers:
		result.append( element[n] )
	return result
		
def xor_lists(li1, li2):#so far not used
	#gets longer shorter list
	t = (li1,li2)
	long = t[len(t[0]) < len(t[1])]
	short = t[len(t[0]) > len(t[1])]
	result = long
	for x in range(0, len(short)):
		result[x] = short[x] ^ long[x]
	return result

	

def possible_key_at_pos( byte ):#xor value that leads to ascii range
	
	result = []
	for x in range(0,255):
		test = byte ^ x
		if test < 0x7b and ((test == 0x20) or (test > 0x40 and test < 0x5b) or (test > 0x60 and test < 0x7b) or (test == 0x20)):
			result.append(x)
	return result

def possible_key_at_col( column_number, ciphers ):#narrows down possible keys by testing against ascii char range (works only for text and spaces)
	result = [i for i in range(256)]
	result = set(result)
	column = getColumn( column_number, ciphers )
	for element in column:
		possible_for_element = set( possible_key_at_pos( element ) )
		result = result & possible_for_element
	return list(result)

	
	
def find_for_known( val_guess, char_in_question ):#untested
	result = 0
	for x in range(0,255):
		test = char_in_question ^ x
		if test == ord(val_guess):
			return x
	
	
	
#following might be junk

def generateKey( number_of_columns, cipher ):
	result = []
	for x in range(0,number_of_columns):
		result.append ( possible_key_at_col( x, cipher ) )
	return result

def cleanKeyList( keyList ):#to clean and format the results from generateKey()	
	result = []
	for element in keyList:
		if len(element) > 0:
			result.append(element[0])
		else:
			result.append(0)
	return result
	
	
#Real Junk

def print_deduce( cipher ):#test version for first 50 columns of a ciphertext
	result = []
	keyList = cleanKeyList( generateKey( 70, cipher ) )
	
	for x in range(0,70):
		result.append( chr(keyList[x] ^ cipher[0][x]) )
	print result

def print_deduce_eleven_ciphers( cipher ):
	result = []
	keyList = cleanKeyList( generateKey( 70, cipher ) )
	print keyList
	for y in range(0,10):
		result = []
		for x in range(0,70):
			result.append( chr(keyList[x] ^ cipher[y][x]) )
		print result
	return keyList	
