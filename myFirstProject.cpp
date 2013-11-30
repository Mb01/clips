#include <iostream>
/*  for moves
*   1 is rock
*   2 is scissors
*   3 is paper
*probably could use enums or mod
*
*   0 for loss of human player
*   1 for draw ''
*   2 for win  ''
*
*Stats and they are global for now... all from human players perspective
*/

int wins = 0;               //total number of
int draws = 0;              // ''
int losses = 0;             // ''

int gameNumber = 0;         //the current trial number we are on, note starts at zero for array combatability
int lastPlayerMove = 0;     //retains the player move from the last trial
int lastComputerMove = 0;   //retains the last computer move

int sameMoveIndex = 0;   //how likely the player is to choose the same move twice in a row
int copyMoveIndex = 0;   //how likely the player is to copy the move of the computer
int adaptiveMoveIndex = 0; //how likely the player is to chose the move that beats the last computer move

int weightRock = 0;         //how many times they pick rock (for now)
int weightScissors = 0;
int weightPaper = 0;

/*
end stats
*/
using namespace std;

int resolve(int moveA, int moveB){ //takes 2 moves and returns 0 1 or 2 for loss/draw/win. moves are 1 2 or 3 for rock scissors paper ... now it takes(PMove, CMove)
int result = 0;//0 for human player loss, 1 for draw, and 2 for win
if(moveA == moveB)
{
    return 1;
}
result = (moveB == (moveA+1) || (moveA == 3 && moveB == 1)) ? 2 : 0;

return result;
}
int moveGen(){// must return a valid computer move

int move =1;//equals one for now so the computer has a valid move on the first try

if(gameNumber != 0){
    if(sameMoveIndex >= copyMoveIndex && sameMoveIndex >= adaptiveMoveIndex){
        if(lastPlayerMove == 1){
        move = 3;
        }
        else if(lastPlayerMove == 2){
        move = 1;
        }
        else if(lastPlayerMove == 3){
        move = 2;
    }
    else if(copyMoveIndex >= adaptiveMoveIndex && copyMoveIndex >= sameMoveIndex){
        if(lastComputerMove == 1){
        move = 3;
        }
        else if(lastComputerMove == 2){
        move = 1;
        }
        else if(lastComputerMove == 3){
        move = 2;
        }
    }
    else {//adaptive move index could go here
        if(lastComputerMove == 1){
        move = 2;
        }
        else if(lastComputerMove == 2){
        move = 3;
        }
        else if(lastComputerMove == 3){
        move = 1;
        }

    }

    }
}
return move; //must be 1 2 or 3
}
void printResult(int a){ //prints the results of the trial
if(a == 0){
cout << "YOU LOSE" << endl;
}
if(a == 1){
cout << "It's a draw" << endl;
}
if(a == 2){
cout << "YOU WIN" << endl;
}
}
void updateStats(int result){ //updates WINS AND LOSSES
if(result == 0){
    losses +=1;
}
if(result == 1){
    draws +=1;
}
if(result == 2){
    wins +=1;
}
}
void printStats(){// prints out wins draws and losses
cout << "wins: " << wins << " draws: " << draws << " losses: " << losses << endl;
}
void statistics(int MoveA, int MoveB){//these stats for computer "thinking" (player_move,computer_move) IMPORTANT the barrier between iterations is here now
                                // so the meaning of this trail and last trial are transitioned here... sequence is important
if(gameNumber != 0){
sameMoveIndex += (MoveA == lastPlayerMove) ? 1 : -1;
copyMoveIndex += (MoveA == lastComputerMove) ? 1 : -1;
adaptiveMoveIndex +=((lastComputerMove == MoveA+1)|| ((lastComputerMove == 1) && (MoveA == 3))) ? 1 : -1;
cout <<"same move index is: " <<sameMoveIndex << endl;
cout <<"copy move index is: " <<copyMoveIndex << endl;
cout <<"adaptive move index is: " <<adaptiveMoveIndex << endl;
}
//set up next round
//all calculations should be above this...
lastPlayerMove = MoveA;
lastComputerMove = MoveB;
gameNumber++;
cout << endl << endl;
}



int main()
{
int PMove = 0;
int CMove = 0;
int result= 0;

while(PMove != 9){

cout << "1 for rock, 2 for scissors, 3 for paper, 9 to quit: " <<endl;
cin >> PMove;
if(PMove !=9){
    CMove = moveGen();
    cout <<"Computer Move is: " << CMove << endl;
    result = resolve(PMove, CMove);
    printResult(result);
    updateStats(result);
    printStats();//wins and losses
    statistics(PMove, CMove);






    }//won't happen if player enters 9
}//everything that happens before the player presses 9 goes here

    return 0;
}
