#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct IntArray{
    int* begin;
    int length;
};

int* makeArray(int length){
    int* array = new int[length];
    for(int x = 0; x < length;x++){
        array[x] = 0;
    }
    return array;
}

int* makeOneToX(int length){
    int* array = makeArray(length);
    for(int x = 0; x < length; x++)
    {
        array[x] = x;
    }
    return array;
}

void printArray(int* array, int length){
    for(int x = 0; x < length; x++)
    {
        cout << array[x] << ' ';
    }
}

int* count(int*array, int length, int maxSize){
    int* hash = makeArray(maxSize);
    for(int x = 0; x < length; x++)
    {
        hash[array[x]]++;
    }
    return hash;
}

vector<string> split(string s,char d){
    vector<string> result;
    int p1 = 0;
    int p2 = 0;
    while( p2 < s.length() ){
        if(s[p2] == d){
            result.push_back(s.substr(p1, p2-p1));
            p1 = ++p2;
        }else{
            ++p2;
        }
    }
    //get the last element
    result.push_back(s.substr(p1, p2-p1));
    return result;
}

void printV( vector<string> vs ){
    for( vector<string>::iterator it = vs.begin(); it < vs.end(); it++ ){
        cout << *it << ' ';
    }
}

int charToInt(char c){
    string index = "0123456789";
    return index.find(c);
    //or c - 0x30
}

int stringToInt(string s){
    int powTen = 1;
    int result = 0;
    for(int x = 0; x < s.length();x++){
        result += charToInt(s[s.length() - x - 1]) * powTen;
        powTen *= 10;
    }
    return result;
}

bool bitsMatch(vector<string> vs){
    vector<string>::iterator it = vs.begin();
    int n = stringToInt(*it);
    it++;
    int p1 = stringToInt(*it);
    it++;
    int p2 = stringToInt(*it);
    bool a = (n >> (p1-1))%2;
    bool b = (n >> (p2-1))%2;
    return (a == b);
}

void qsort(int* array, int length){
    if(length < 2){ return; }
    int partition = array[length / 2];
    int* left = array;
    int* right = array + length -1;
    while(left <= right){
        if(*left < partition){
            left++;
            continue;
        }
        if(*right > partition){
            right--;
            continue;
        }
        int temp = *left;
        *left++ = *right;
        *right-- = temp;
    }
        qsort(array, right - array + 1);
        qsort(left, array + length - left);
}

//finds first member of array1 not in array2 from the left
int findNotInOther(int* array1, int length1, int* array2, int length2, int maxSize){
    int* hash = count(array2, length2, maxSize);
    for(int x = 0; x < length1; x++){
        if(hash[array1[x]] < 1)
        {
            return array1[x];
        }
    }
}

//finds and prints all duplicates. Made it easy to change to return an array of duplicates.
void findAllDuplicates(int* array, int length, int maxSize){
    int* hash = count(array, length, maxSize);
    int resultLength = 0;
    for(int x = 0; x < maxSize; x++){
        if(hash[x] > 1){
            resultLength++;
        }
    }
    int iter = 0;
    int* result = makeArray(resultLength);
    for(int x = 0; iter < resultLength; x++)//!make note of iter in comparison!
    {
        if(hash[x] > 1){
            result[iter++] = x;
        }
    }
    printArray(result, resultLength);
}

//finds first missing number from the left
int findMissing(int* array, int length, int maxSize){
    int* hash = count(array, length, maxSize);
    for(int x = 0; x < maxSize; x++){
        if(hash[x] < 1)
        {
            return x;
        }
    }
    return -1;
}

//finds first diplicate number from the left
int findDuplicate(int* array, int length, int maxSize){
    int* hash = count(array, length, maxSize);
    for(int x = 0; x < maxSize; x++){
        if(hash[x] > 1)
        {
            return x;
        }
    }
    return -1;
}

int asToHex(char input)//takes an ASCII value REPRESENTING HEX and puts it into an INT !lowercase only!
{
  return (input > 0x60? input - 0x57 : input - 0x30);
}


int main (int argc, char ** argv){

if(argc < 2){cout << "missing argument"; return 0;}
int ctr = 0;
ifstream file;
file.open(argv[1]);
    while (!file.eof()){
        if(ctr < 0){ cout << '\n';}
        string lineBuffer;
        getline(file, lineBuffer);
        if (lineBuffer.length() == 0){
           continue; //ignore all empty lines
        }
        else{


        }

    }

}
