#include "hangman.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <time.h> 
using namespace std;

bool hangman::findBestPos()
{
  charLoc.assign (wordLength + 1, 0);
  int family = 0;
  int familyNo = 0;
  bool contains = false;
  for(int i = 0; i < Words.size(); i++)
  {
    for(int k = 0; k < wordLength; k++)
    {

      if(Words[i][k] == guess)
      {
        charLoc[k+1]++;
        contains = true;
      }
    }
    if(!contains)
    {
      charLoc[0]++;
    }
    contains = false;
  }

  for(int i = 0; i < charLoc.size(); i++)
  {
    if(debugMode)
      cout << "Pos: " << i << ": " << charLoc[i] << endl;
    if(charLoc[i] > family)
    {
      familyNo = i;
      family = charLoc[i];
    }
  }
  if(debugMode)
  {
    cout << "Best Position: " << familyNo << endl;
    if(Words.size() <= 10)
      remaining();
  }

  if(Words.size() <= 5)
  {
    if(familyNo == 0)
      return attemptRemoveIncWord();
    else
      return attemptRemoveExWord(familyNo-1);
  }
  else if(familyNo == 0)
    removeIncWord();
  else
    removeExWord(familyNo-1);

  
  return true;

}

void hangman::removeGen(vector<string> &Temp, int a)
{
  for(long i = 0; i < Temp.size(); i++)
  {
    for(int k = 0; k < wordLength; k++)
    {
      if(Temp[i][k] == guess && k != a)
      {
        Temp.erase(Temp.begin()+i);
        i--;
        break;
      }
    }
  }
}

void hangman::removeKeep(vector<string> &Temp, int a)
{
  bool deleteIt;

  for(long i = 0; i < Temp.size(); i++)
  {
    deleteIt = true;
    if(Temp[i][a] == guess)
    {
      deleteIt = false;
    }
    if(deleteIt)
    {
      Temp.erase(Temp.begin()+i);
      i--;
    }  
  }
}

void hangman::removeIncWord()
{
  removeGen(Words, -1);
}

bool hangman::attemptRemoveIncWord()
{
  vector<string> Temp = Words;
  removeGen(Temp, -1);

  if(Temp.size()>0)
  {
    Words.assign(Temp.begin(), Temp.end());
    return true;
  }
  return false;
}

void hangman::removeExWord(int a)
{
  removeGen(Words, a);
  removeKeep(Words, a);
}

bool hangman::attemptRemoveExWord(int a)
{
  vector<string> Temp = Words;
  bool deleteIt;
  
  removeGen(Temp, a);
  removeKeep(Temp, a);

  if(Temp.size()>0)
  {
    Words.assign(Temp.begin(), Temp.end());
    return true;
  }
  return false;
}



void hangman::userSetup()
{
  while(wordLength>10 || wordLength<4)
  {
    cout << "Welcome to a friendly game of hangman" << endl;
    cout << "Please enter a length for the word (4-10): ";
    cin  >> wordLength;
  }
  wordP.assign(wordLength, '_');

  cout << endl << "How many guesses would you like: ";
  cin >> remGuesses;
  cout << endl;

  string password;
  cout << "Input password for debug mode: ";
  cin >> password;
  if (password == "pa$$w0rd")
    debugMode = true;
  else debugMode = false;
}

bool hangman::getGuess()
{
  cout << "Please make a guess: ";
  cin  >> guess;
  if (!contains(guesses))
  {
    guesses.push_back(guess);
    return true;
  }
  return false;
}
//function to get the guess from the user

bool hangman::outputUpdate()
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
    cout << "Hard luck, Game Over" << endl << endl;
    return false;
  }
  return true;
}
//function to print the update after guessing and returns amount of guesses left

void hangman::fillWordList()
{
  ifstream dictionary ("dictionary.txt");
  string word;
  if (dictionary.is_open())
  {
    while (getline(dictionary,word))
    {
      if(word.length() == wordLength)
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
    cout << i << ": " << Words[i] << endl;
  }
}
//A debug function to print the vector of words

void hangman::pickRandWord()
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