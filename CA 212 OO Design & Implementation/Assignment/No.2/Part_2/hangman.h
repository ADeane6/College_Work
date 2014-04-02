#include <string>
#include <vector>
using namespace std;

class hangman
{
public:
  vector<string> Words; //vector of avalible words
  vector<char> guesses; //vector of guessed letters
  int remGuesses;       //number of remaining guesses
  int wordLength;       //length of chossen word
  char guess;           //current guess
  string word;          //current word holder
  vector<int> charLoc;  //locations of chars in vector Words
  bool debugMode;       //Debug mode
  vector<char> wordP;     //vector to store progress
  int familyNo;


  bool attemptRemoveIncWord();
  bool attemptRemoveExWord(int a);
  void removeIncWord();
  void removeExWord(int a);
  //removes all words from vector Words with the guess in it

  bool bestPos();
  //leaves only the best family of words (most with guess in same position)

  void userLength();
  //function to take user input for the length of word

  void guessAmount();
  //get the user to input the amount of guesses allowed

  void debug();
  //Enable debug mode if pa$$w0rd is right

  bool getGuess();
  //function to get the guess from the user

  bool update();
  //function to print the update after guessing and returns amount of guesses left

  void wordList(int x);
  //function to create a vector of all words with length x

  void pickWord();
  //function to pick a random word from vector Words --- only needed for normal hangman

  bool contains(vector<char> word);
  //return true if guess is in vector word

private:
  void remaining();
  //A debug function to print the vector of words
};