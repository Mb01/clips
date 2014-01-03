
//factored in from all the source files into one
//why did I not create a folder?

//this program breaks an xor stream cipher (sometimes) if the allignment and charset is known
//e.g. each method starts at the same position

#ifndef TEXTS_H_INCLUDED
#define TEXTS_H_INCLUDED

#include <vector>
#include <string>
#include <set>
using namespace std;


class Texts{

    private:

        vector< vector<int> >   texts;
        vector< set<int> >      col;
        string                  filename;
        int                     maxLength;
        int                     numLines;



        //part of constructor
        int                     asciiToHex(char input);

        //vector<int>           makeArray(string input); WHY CAN'T I UNCOMMENT THIS!?
        void                    makeCol();


    public:

        Texts( string filename );

        //getSet
        vector< vector<int> >   getTexts();
        vector< set<int> >      getByCols();
        int                     getMaxLength();
        int                     getNumLines();
        vector<string>          getLinesAsString();

        //debug
        void                    printAll();
        void                    printByCol();

};


#endif // TEXTS_H_INCLUDED


//functions used by constructor
int asciiToHex(char input){ //takes an ASCII value REPRESENTING HEX and puts it into an INT !lowercase only!

    return (input > 0x60? input - 0x57 : input - 0x30);

}
vector<int> makeArray( string input ){//makes string representing hex into an array of those values byte by byte
    vector<int> result;

    for(unsigned int x = 0; x < input.length(); x+=2)
    {
        int high = asciiToHex(input[x]);
        int low = asciiToHex(input[x+1]);
        result.push_back( (high * 0x10) + low );
    }
    return result;
}

void Texts::makeCol(){
    vector< vector<int> >::iterator vvi;
    vector<int>::iterator vi;

    this->col.resize(maxLength);


    for(vvi = this->texts.begin(); vvi < this->texts.end(); ++vvi){
        //iterating through texts
        int x = 0;
        for(vi = vvi->begin(); vi < vvi->end(); ++vi){
            //iterating through each text
            this->col[x].insert(*vi);
            x++;
        }
    }
}


/*//-------------
*   -constructor-
*///-------------
Texts::Texts( string filename ){//makes ascii textfile into integers in byte length
    this->numLines = 0;
    fstream file;
    file.open(filename.c_str(), ios::in);
    string fileLine;

    while(file.good())
    {
        file >> fileLine;
        this->texts.push_back( makeArray(fileLine ) );
    }
    //find maxLength, numLines
    vector< vector<int> >::iterator it;
    this->maxLength = 0;
    for(it = this->texts.begin(); it < this->texts.end(); ++it)
    {
        if((*it).size() > maxLength)
        {
            maxLength = (*it).size();
        }
        this->numLines++;
    }
    //copy that is indexed by column
    makeCol();


}




//get and set members
vector< vector<int> > Texts::getTexts(){
    return this->texts;
}
int Texts::getMaxLength(){

    return this->maxLength;
}
int Texts::getNumLines(){
    return this->numLines;
}
vector< set<int> > Texts::getByCols(){
    return this->col;
}

//debug
void Texts::printAll(){
    vector< vector<int> >::iterator it;
    for(it = this->texts.begin(); it < this->texts.end(); it++)
    {
        vector<int>::iterator itt;
        for(itt = (*it).begin(); itt!= (*it).end(); itt++)
        {
            cout << hex << (*itt);
        }
        cout << endl;
        cout << endl;
    }
}
void Texts::printByCol(){
    vector< set<int> >::iterator vsi;
    set<int>::iterator si;

    for(vsi = this->col.begin(); vsi < this->col.end(); ++vsi)
    {
        //iterating through columns
        for(si = vsi->begin(); si != vsi->end(); ++si)
        {
            cout << hex << (*si) << " ";
        }
        cout << endl;
    }
}

vector<string> Texts::getLinesAsString(){//returns lines in a vector as !!ASCII
    vector<string> result;
    vector<vector<int> > local = this->texts;
    vector<vector<int> >::iterator vvi;
    while(!local.empty())
    {

    }
    return result;
}


class Key{

    private:

    vector<int>             key;
    vector< set<int> >      candidates;

    public:
    /*constructor*/         Key(int length);
    void                    setKey(vector<int>);
    vector<int>             getKey();



};

void Key::setKey(vector<int> x){
    this->key = x;
}
vector<int>     Key::getKey(){
    return this->key;
}


Key::Key(int length)
{

    this->key.resize(length);

}

class Deducer{

    private:
    string              filename;
    Texts*              p_texts;
    Key*                p_key;
    vector< set<int> >  candidates;


    public:
    Deducer( string );


    void                findCandidates();//access of erase() for now
    //debug
    void                printCandidates();
    void                test();
};



void Deducer::findCandidates(){
    vector< set<int> > cols = this->p_texts->getByCols();
    vector< set<int> >::iterator vsi_col;//thats Vector Set Int COLumns
    set<int>::iterator si_col;//thats Set Int COLumns

    vector< set<int> > can = this->candidates;
    vector< set<int> >::iterator vsi_can;//Vector Set Int CANdidates
    set<int>::iterator si_can;//thats Set int CANdidates

    for(vsi_col = cols.begin(), vsi_can = can.begin(); vsi_col < cols.end(); ++vsi_col,++vsi_can ){
        //iterating through vector of sets holding columns AND vector of sets holding possibilities "candidates"
        for(si_col = vsi_col->begin(); si_col != vsi_col->end();++si_col){
            //iterating set holding a column
            for(si_can = vsi_can->begin(); si_can != vsi_can->end(); /*!*/0){
            //iterating through set of possibilities for a column "candidates"
                int test = (*si_col) ^ (*si_can);
                if((test < 0x1f) || (test > 0x7a)  ||  //if not in range
                   ((test > 0x20) && (test < 0x27))  ||// !"#$%&
                   ((test > 0x2a) && (test < 0x41))  ||// 0 to 9 and :;<=>?@
                   ((test > 0x5a) && (test < 0x61))  // [/]^_`
                  )
                {
                    int val = (*si_can);
                    ++si_can;
                    (*vsi_can).erase(val);
                }//endif
                else
                {
                    ++si_can;
                }
            }//end candidate loop
        }//end column loop
    }//end loops
    this->candidates = can;
}

Deducer::Deducer( string fname ){
    this->filename = fname;
    this->p_texts = new Texts(filename);
    int length = this->p_texts->getMaxLength();
    this->p_key = new Key(length);
    this->candidates.resize(length);
    vector< set<int> >::iterator vsi;
    for(vsi = this->candidates.begin(); vsi < this->candidates.end(); ++vsi)
    {
        for(int x = 0; x < 256; x++)
        {
            (*vsi).insert(x);
        }
    }
    findCandidates();//narrows candidates... timing is optional
}












//debug
void Deducer::test()
{
    //cout << "Max length is: " << this->p_texts->getMaxLength();
    //cout << "Numlines is: " << this->p_texts->getNumLines();
    //cout << "Text is: " << endl;
    //this->p_texts->printAll();
    //cout << endl;
    //cout << "all columns are:" << endl;
    //this->p_texts->printByCol();
    //cout << endl;
    //cout << "candidates are:" << endl;
    this->printCandidates();
    this->p_texts->getLinesAsString();
}

//gives us the candidates for the answer, if each position has one candidate the problem is solved
void Deducer::printCandidates(){
    vector< set<int> >::iterator vsi;
    set<int>::iterator si;

    for(vsi = this->candidates.begin(); vsi < this->candidates.end(); ++vsi)
    {
        //iterating through columns
        for(si = vsi->begin(); si != vsi->end(); ++si)
        {
            cout << hex << (*si) << " ";
        }
        cout << endl;
        cout << endl;
    }
}
