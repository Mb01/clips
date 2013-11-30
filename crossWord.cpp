#include <iostream>
#include <vector>
#include <stack>
#include <fstream>


int PUZZLE_SIZE = 15;
std::vector<char> BASEPUZZLE; // keep these out of classes so we can refactor!

struct MoveOrder{
    int number; // which square numbering left to right top to bottom
    bool across;// false is down
};

class Dictionary{
private:
    std::vector<std::string> words;
public:
    Dictionary();
    std::vector<std::string>::iterator findFirst(std::string toMatch);
    std::vector<std::string>::iterator findLast(std::string toMatch);

}DICTIONARY;

Dictionary::Dictionary(){
    std::string line;
    std::fstream inFile;
    inFile.open("CROSSWD.TXT");
    while(!inFile.eof()){
        inFile >> line;
        words.push_back(line);
    }
}
std::vector<std::string>::iterator Dictionary::findFirst(std::string toMatch){
    std::vector<std::string>::iterator eov = words.end();
    std::vector<std::string>::iterator it = words.begin();
    while(it < eov){
        if(it->find(toMatch) == 0){
            return it;
        }else{++it;}
    }
    return words.end();
}
std::vector<std::string>::iterator Dictionary::findLast(std::string toMatch){
    std::vector<std::string>::iterator sov = words.begin();
    std::vector<std::string>::iterator it = words.end() - 1;
    while(it > sov){
        if(it->find(toMatch) == 0){
            return it;
        }else{--it;}
    }
    return words.end();
}



class Node{
private:
    std::vector<char>                           puzzle;
    std::vector<std::string>::iterator          from;//first in dictionary
    std::vector<std::string>::iterator          to;//last in dictionary
    bool                                        dead;
    bool                                        isRoot;

public:
    Node                                        (bool root);
    void                                        findMatches(std::string toMatch);
    std::vector<std::vector<char>::iterator>    getColumnIt(int colNumber);
    std::vector<std::vector<char>::iterator>    getRowIt(int rowNumber);
    void                                        addWord(std::vector<std::vector<char>::iterator>::iterator toChange, int pos, std::string word);
    std::vector<char>                           getPuzzle(){return puzzle;}
    void                                        copyPuzzle(Node parent){puzzle = parent.getPuzzle();}
    void                                        setIsRoot(bool arg){isRoot = arg;}
    bool                                        getIsRoot(){return isRoot;}
    bool                                        getDead(){return dead;}
};

Node::Node(bool root){
    dead = false;
    isRoot = root;
}
std::vector<std::vector<char>::iterator> Node::getColumnIt(int colNumber){
    std::vector<std::vector<char>::iterator> result;
    int cnt =0;
    for(std::vector<char>::iterator it = puzzle.begin(); it < puzzle.end(); it++)
    {
        if(cnt%PUZZLE_SIZE == colNumber){
            result.push_back(it);
        }
        ++cnt;
    }
    return result;
}
std::vector<std::vector<char>::iterator> Node::getRowIt(int rowNumber){
    std::vector<std::vector<char>::iterator> result;
    int cnt =0;
    int first = PUZZLE_SIZE * rowNumber;
    int last = first + PUZZLE_SIZE - 1;
    for(std::vector<char>::iterator it = puzzle.begin(); it < puzzle.end(); it++){
        if(cnt >= first && cnt <= last){
            result.push_back(it);
        }
        ++cnt;
    }
    return result;
}
void Node::findMatches(std::string toMatch){
    from = DICTIONARY.findFirst(toMatch);
    to = DICTIONARY.findLast(toMatch);
}
void Node::addWord(std::vector<std::vector<char>::iterator>::iterator toChange, int pos, std::string word){

    std::vector<std::vector<char>::iterator>::iterator temp = toChange;
    toChange += pos;

    for(std::string::iterator it = word.begin(); it < word.end(); it++, toChange++){
        **toChange = *it;
    }
}



//what I want is a member of decisionTree that tries to add a word to a node and if it can't add any, pop the node and go back
//if it can, than the stack is popped back to the last node, each node keeps track of what words it is on, it gets popped when
//it exhausts all options

class DecisionTree{
private:
    std::stack<Node>            tree;
    std::vector<MoveOrder>      order;
    void                        practicalDecideMoveOrder(std::vector<char> puzzle);
    std::vector<std::string>    wordsAdded;
public:
    std::vector<char> makePuzzle(std::vector<char> puzzle);

};


std::vector<char> DecisionTree::makePuzzle(std::vector<char> puzzle){
    practicalDecideMoveOrder(puzzle);
    std::vector<char> answer;
    Node rootNode = Node(true);

    return answer;
}

void DecisionTree::practicalDecideMoveOrder(std::vector<char> puzzle){  //so I'm going to find all across and all down and interleave all of them
                                                //this should give us a much better than random move order
    //find all across we want to find top leftmost remaining


}





int main()
{



DecisionTree tree;
std::vector<char> answer = tree.makePuzzle(BASEPUZZLE);
int cnt = 0;
for (std::vector<char>::iterator it = answer.begin(); it < answer.end(); it++){
    if(cnt%15 == 0 && cnt != 0){std::cout << '\n';}
    std::cout << *it << ' ';
    cnt++;
}
}
