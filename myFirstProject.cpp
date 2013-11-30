#include <iostream>
#include <string>

using namespace std;

int CMove; //computers move
int PMove; //players move
int Cwins = 0; //number of computer wins
int Pins = 0; //number of player wins


int PMoves[10000]; // the last 10000 player moves

int generateTables(){

//generate number of times 0 is followed by 0 and so on
for(int x = 0; x > 10000; x++){



}






}
int strategy(){}




int main()
{
    int quit = 0;
    int PMove =0;
while(PMove != 9){

    cout << " Enter '1' for 'rock', '2' for 'paper', '3' for scissors, and '9' to quit: " << endl;
    cin >> PMove;
    if((PMove > 3 || PMove < 1) && PMove != 9){
        cout << PMove << " is out of range." << endl;
    cout << "enter '1' for 'rock', '2' for 'paper', '3' for scissors, and '9' to quit: "<< endl;
    cin >> PMove;
        if((PMove > 3 || PMove < 1) && PMove != 9){
        cout <<" Enter 4, 5, 6, 7, 8, or 9 to quit" << endl;
        cin >> PMove;
            if((PMove > 3 || PMove < 1) && PMove != 9){
            PMove=9;
            }
        }







    }// everything we need to repeat needs to be inside this while statement

    generateTables();//generates statatistcs on player moves
    CMove = strategy();

}
    return 0;
}

