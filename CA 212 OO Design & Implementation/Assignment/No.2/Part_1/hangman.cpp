#include "hangman.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <time.h> 
using namespace std;




//two stub methods---------------------------------------------------------
void hangman::removeWord(int a, int b)
{
}
//removes all words from vector Words with the guess char in it

bool hangman::bestPos()
{
  return false;
}
//leaves only the best family of words (most with guess char in same position)
//-----------------------------------------------------------------------





void hangman::userLength()
{
  int a = 0;
  while(a>12||a<4)
  {
    cout << "Welcome to a friendly game of hangman" << endl;
    cout << "Please enter a length for the word (4-12): ";
    cin  >> a;
  }
  wordLength = a;
  wordP.assign(wordLength, '_');

}
//function to take user input for the length of word

void hangman::guessAmount()
{
  while(remGuesses<1)
  {
    cout << endl << "How many guesses would you like: ";
    cin >> remGuesses;
    cout << endl;
  }
}
//get the user to input the amount of guesses allowed

void hangman::debug()
{
  string password;
  cout << "Input password for debug mode: ";
  cin >> password;
  if (password == "pa$$w0rd")
    debugMode = true;
  else debugMode = false;
}
//enable debug mode if password is correct

bool hangman::getGuess()
{
  cout << "Please make a guess: ";
  cin  >> guess;
  if (!contains(guesses))
  {
    guesses.push_back(guess);
    return false;
  }
  return true;
}
//function to get the guess from the user

bool hangman::update()
{
  cout << "Guessed letters: ";
  for (int i = 0; i < guesses.size(); i++)
  {
    cout << guesses[i] <<" ";
  }
  cout << endl;
  cout << "Guesses remaining: " << remGuesses << endl << "|" << endl;
  if (remGuesses == 0)
  {
    cout << "Hard luck, Game Over" << endl;
    return false;
  }
  return true;
}
//function to print the update after guessing and returns amount of guesses left

void hangman::wordList(int x)
{
  ifstream dictionary ("dictionary.txt");
  string word;
  if (dictionary.is_open())
  {
    while (getline(dictionary,word))
    {
      if(word.length() == x)
        Words.push_back(word);
    }
    dictionary.close();
  }
}
//function to create a vector of all words with length x

void hangman::remaining()
{
  for(int i = 0; i < Words.size(); i++)
  {
    cout << i << ": " << Words[i];
  }
}
//A debug function to print the vector of words

void hangman::pickWord()
{
  srand(time(NULL));
  word = Words[rand() % Words.size()+1];
}


bool hangman::contains(vector<char> word)
{
  for (int i = 0; i < word.size(); i++)
  {
    if(word[i] == guess)
      return true;
  }
  return false;
}