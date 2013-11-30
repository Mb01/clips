int asciiToHex(char input) //takes an ASCII value REPRESENTING HEX and puts it into an INT !lowercase only!
{
    int result = input;
    result = (result > 0x60? result - 0x57 : result - 0x30);
    return result;
}

//rewrite as

int asToHex(char input)//takes an ASCII value REPRESENTING HEX and puts it into an INT !lowercase only!
{
  return (input > 0x60? input - 0x57 : input - 0x30);
}


int* makeArray(string input)//makes string representing hex into an array of those values byte by byte
{
    int* result = new int[input.length() / 2];
    for(unsigned int x = 0; x < input.length() / 2; x += 1)
    {
        int high = asciiToHex(input[x*2]);
        int low = asciiToHex(input[x*2+1]);
        result[x] = (high * 0x10) + low;
    }
    return result;
}
