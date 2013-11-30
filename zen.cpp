#ifndef MY_STRUCTS_H_INCLUDED
#define MY_STRUCTS_H_INCLUDED




struct node
{
  std::string name;
  std::string content;
  std::string** attributes;
  int numberAttr;
  node* parent;
  node** children;
  bool hasParent;
  int numberChildren;
};

#endif // MY_STRUCTS_H_INCLUDED


#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

node* parse( std::string input );

#endif // PARSER_H_INCLUDED

#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

void printContent( node* node);
void printOriginal( node* node );

#endif // TEST_H_INCLUDED


/* Main.cpp */

#include <iostream>
#include <string>
#include <fstream>
#include "my_structs.h"
#include "parser.h"
#include "test.h"

using namespace std;


string readFile( string filename)
{
    fstream file;
    file.open(filename.c_str(), ios::in);
    string result;
    char c;
    while(file.good())
    {
        c = file.get();
        if(file.good())
            {result += c;}
    }
    return result;
}

//hacked this out in five hours
//what was I bragging about?

int main()
{
    string input = readFile("input.txt");
    node* tree = parse( input );
    printContent( tree );
    printOriginal( tree );
    return 0;
}

/* parser.cpp */

#include <iostream>
#include <string>
#include "my_structs.h"


//big caveat position of children in content not preserved... could be easily done leaving some symbol in the content to mark the place
//order of children will be preserved
//max children 100, max attributes = 10... until I implement some vectors

using namespace std;


node* makeChild( string input, long int &pos, node* parent){
    node* w = new node;
    w->hasParent = true;
    w->parent = parent;
    w->children = new node*[100];//warning danger;
    w->numberChildren = 0;
    w->content = "";
    w->attributes = new string*[10];//danger!
    w->numberAttr = 0;
    return w;
}
node* makeBase(){
    node* w = new node;
    w->hasParent = false;
    w->parent = 0;
    w->numberChildren = 0;
    w->children = new node*[1000];//warning danger!
    w->attributes = new string*[10];//danger!
    w->numberAttr = 0;
    w->content = "";
  return w;
}

void readTag( string &input, long int &pos, node* w ){//start at '<' end at '>'+1
    //get name
    pos++;
    while( input[pos] != '>' && input[pos] != ' ')
    {
        w->name += input[pos];
        pos++;
    }
    while( input[pos] != '>')
    {
        w->numberAttr += 1;
        w->attributes[w->numberAttr -1] = new string;
        pos++;
        while( input[pos] != ' ' && input[pos] != '>')
        {
            *(w->attributes[w->numberAttr -1]) += input[pos];
            pos++;
        }
    }
    pos++;
}




void recurse( string &input, long int &pos, node* w){
    readTag( input, pos, w);
    while(true){
        while(input[pos] != '<'){
            w->content += input[pos];
            pos++;
        }
        if(input[pos+1] == '/'){
            pos += w->name.length()+3; //+3 to skip tag cars "</>"
            return;
        }
        else{
            node* child = makeChild( input, pos, w);
            w->numberChildren += 1;
            w->children[ w->numberChildren -1] = child;
            recurse( input, pos, child);
        }
    }
}

node* parse( string input ){

    long int pos = 0;
    node* base = makeBase( );
    recurse(input, pos, base);

    return base;
}

/* test.cpp */
#include <iostream>
#include <string>
#include <fstream>
#include "my_structs.h"
#include "parser.h"

using namespace std;



void printContent( node* node ){
    if(node->content.length() > 0)
    {
        cout << node->content << endl;
    }
    for(int x = 0; x < node->numberChildren; x++)
    {
        printContent(node->children[x]);
    }
    return;
}

void printOriginal( node* node )
{
    cout << '<' << node->name;
    for(int x = 0; x < node->numberAttr;x++)
    {
        cout << ' ' << *node->attributes[x];
    }
    cout << '>';
    if(node->content.length() > 0)
    {
        cout << node->content;
    }
    for(int x = 0; x < node->numberChildren; x++)
    {
        printOriginal(node->children[x]);
    }
    cout << "</" << node->name << '>';
    return;
}

