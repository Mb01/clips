int asciiToHex(char input) //takes an ASCII value REPRESENTING HEX and puts it into an INT !lowercase only!
{
    int result = input;
    result = (result > 0x60? result - 0x57 : result - 0x30);
    return result;
}

//rewrite as

int asToHex(char input){//takes an ASCII value REPRESENTING HEX and puts it into an INT !lowercase only!
{
  return int((input > 0x60? input - 0x57 : input - 0x30));
}
