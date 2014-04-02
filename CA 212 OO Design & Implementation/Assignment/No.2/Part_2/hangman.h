#include <string>
#include <vector>
using namespace std;

class hangman
{
public:
  vector<string> Words; //vector of avalible words
  int remGuesses;       //number of remaining guesses
  int wordLength;       //length of chossen word
  char guess;           //current guess
  string word;          //current word holder
  bool debugMode;       //Debug mode
  vector<char> wordP;   //vector to store progress


  bool attemptRemoveIncWord();
  bool attemptRemoveExWord(int a);
  void removeIncWord();
  void removeExWord(int a);
  
  bool findBestPos();

  void userSetup();

  bool getGuess();

  bool outputUpdate();

  void fillWordList();

  void pickRandWord();

  bool contains(vector<char> word);

private:
  vector<char> guesses; //vector of guessed letters
  vector<int> charLoc;  //locations of chars in vector Words

  void remaining();
  void removeKeep(vector<string> &Temp, int a);
  void removeGen(vector<string> &Temp, int a);
};