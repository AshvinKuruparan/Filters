#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Filter
{
protected:
  string _name;
public:  
  Filter(const string& name) : _name(name) {}
  virtual ~Filter() {};
  virtual string apply(const string& input) = 0;
  string get_name() { return _name; }
};

class Capitalize : public Filter
{
    public:
    Capitalize() : Filter("Capitalize"){};//Basic constructor
    ~Capitalize(){}//Deconstructor
    string apply(const string& input){//Overriden apply function
        string capital = input;
        //Check if the letter is capitalized and if not make it a capital
        for ( int i =0; i < input.size(); i++){
            if(islower(capital[i])){
                capital[i] = toupper(capital[i]);
            }
        }
        return capital;
    }
};

class CapitalizeFirstLetter : public Filter
{
    public:
        CapitalizeFirstLetter():Filter("CapFirstLetter"){};//Basic constructor
        ~CapitalizeFirstLetter(){}//Deconstructor
        string apply(const string& input){//Overriden apply function
            string capFirst = input;
            //Capitalizes the first letter
            capFirst[0] = toupper(capFirst[0]);
            return capFirst;
        }
};

class CapitalizeFirstLetterOfEveryWord : public Filter
{
    public:
        CapitalizeFirstLetterOfEveryWord():Filter("CapitalizeFirstLetterOfEveryWord"){};//Basic constructor
        ~CapitalizeFirstLetterOfEveryWord(){}//Deconstructor
        string apply(const string& input){//Overriden apply function
            string capFirst = input;
            //Capitalize the first letter
            capFirst [0] = toupper(capFirst[0]);
            for (int i = 0; i < input.size(); i++){//Loop through all the space and capitalize the next letter
                if(capFirst[i] == ' '){
                    capFirst[i+1] = toupper(capFirst[i+1]);
                }
            }
            return capFirst;
        }

};

class Obenglobish : public Filter
{
    public:
        Obenglobish():Filter("Obenglobish"){}//Basic constructor
        ~Obenglobish(){}//Deconstructor
        bool isVowel(char x){//Checks for a vowel
            if(x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u'){
                return true;
            }
            return false;
        }
        string apply(const string& input){//Overriden apply function
            string obeng;
            for (int i = 0; i < input.size(); i++){
                char letter = input[i];
                if (isVowel(tolower(letter))){//check for vowel
                    if (isVowel(tolower(input[i-1]))){//check if the previous letter is a vowel
                        obeng += letter;
                    }
                    else{
                        obeng = obeng + "ob" + letter;
                    }
                }
                else{
                    obeng += letter;
                }
            }
            return obeng;
        }
};

class ReverseString : public Filter
{
    public:
        ReverseString():Filter("ReverseString"){}//Basic constructor
        ~ReverseString(){}//Deconstructor
        string apply (const string& input){//Overriden apply function
            string reverseStr;
            string temp = input;
            //Loop through the letters in reverse and add them to a string
            for(int i = input.size()-1; i >= 0; i--){
                reverseStr += temp[i];
            }
            return reverseStr;
        }
};

class ToSmall : public Filter
{
    public:
        ToSmall() : Filter("ToSmall"){}//Basic constructor
        ~ToSmall(){}//Deconstructor
        string apply(const string& input){//Overriden apply function
            string tosmall = input;
            //loops through all characters and turn all capitals into lower case
            for (int i = 0; i < input.size(); i++){
                if(isupper(tosmall[i])){
                    tosmall[i] = tolower(tosmall[i]);
                }
            }
            return tosmall;
        }
};

class Randomize : public Filter
{
    public:
        Randomize():Filter("Randomize"){}//Basic constructor
        ~Randomize(){}//Deconstructor
        string apply(const string& input){//Overriden apply function
            string random = input;
            //Randomly asigns the letters to a string
            srand(time(0));
            for(int i = input.size()-1; i>=0; i--){
                int randomNum = rand()%input.size();
                char temp = random[i];
                random[i] = random[randomNum];
                random[randomNum] = temp;
            }
            return random;
        }
};

int main (){

    const int num_filters = 7;
    Filter* filters[num_filters];

    filters[0] = new Capitalize();
    filters[1] = new CapitalizeFirstLetter();
    filters[2] = new CapitalizeFirstLetterOfEveryWord();
    filters[3] = new Obenglobish();
    filters[4] = new ReverseString();
    filters[5] = new ToSmall();
    filters[6] = new Randomize();
  
    string input;
    cout << "Enter srring: ";  getline(cin, input);
  
    cout << "Input string: " << input << endl;
    for (int i=0; i<num_filters; ++i) {
        cout << "Filter name:  " << filters[i]->get_name() << endl;
        cout << "Output:       " << filters[i]->apply(input) << endl; 
    }

    for (int i=0; i<num_filters; ++i) delete filters[i];
    
    return  0;
}