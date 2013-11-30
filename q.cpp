string q(string x)//add quotes
{x = "\"" + x + "\"";return x;}

int main(){
    //demonstrates how a program prints itself
    string d[] =    {"string d[] = {", ", " , "};" ,
                    "cout << d[0] + q(d[0]) + d[1] + q(d[1]) + d[1] + q(d[2]) + d[1] + q(d[3]) + d[2] + d[3];"
                    };
    cout << d[0] + q(d[0]) + d[1] + q(d[1]) + d[1] + q(d[2]) + d[1] + q(d[3]) + d[2] + d[3];
}




int main(){
    int d[] =    {3,2,4,2,5,2,2,6,2,8,2,7,2,0,1,0,0,10,2,0,1,1,0,10,2,0,1,11,0,10,2,0,3,0,10,2,
                  0,4,0,10,2,0,5,0,10,2,0,6,0,10,2,0,7,0,10,2,0,8,0,10,2,0,9,0,10,2,0,10,0,10,2,0,11,0,10,2,0,12,0,10,2,0,13,0,2,9,2,13,12
                  };
    string meta[] = {
        "\"", //0
        "\\", //1
        "\n",//2
        "#include <iostream>",//3
        "#include <string>",//4
        "using namespace std;",//5
        "int main(){",//6
        "string meta[] = {",//7
        "int d[] = {"/*numbers go here*/,//8
        "};",//9
        ",",//10
        "n",//11
        "}",//12
        "for(int x = 0; x < (sizeof(d)/sizeof(d[0]));x++){cout << meta[d[x]];}"//13
        };
    for(int x = 0; x < (sizeof(d)/sizeof(d[0]));x++){cout << meta[d[x]];}
}
