#include "hangman.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <time.h> 
using namespace std;


void hangman::removeWord(int a, int b)
{
  vector <string> temp;

	for(int i = 0; i < Words.size(); i++)
	{
		for(int k = 0; k < wordLength; k++)
		{
			if(b == 0 && Words[i][k] == guess)
      {
        Words.erase(Words.begin()+i);
      }
      else if(Words[i][k] == guess && k == a)
			{
				temp.push_back(Words[i]);
				break;
			}
		}
	}
  if(b == 0)
  {
    Words.resize(temp.size());
    Words.assign(temp.begin(),temp.end());
  }
}
//removes all words from vector Words with the char x in it if there are more then 5 words without x

bool hangman::bestPos()
{
	charLoc.assign (wordLength + 1, 0);
	int family = -1;
  bool contains = false;
	for(int i = 0; i < Words.size(); i++)
	{
		for(int k = 1; k < wordLength + 1; i++)
		{

			if(Words[i][k-1] == guess)
			{
				charLoc[k]++;
        contains = true;
			}
		}
    if(!contains)
    {
      charLoc[0]++;
    }
	}

	for(int i = 0; i < charLoc.size(); i++)
	{
		if(charLoc[i] >= family)
			family = charLoc[i];
	}

  if(family == 0)
  {
    removeWord(10000, family);
  }
  else
  {
    removeWord(family-1);
  }

	return true;

}
//leaves only the best family of words (most with letter X in same position)


void hangman::userLength()
{
  cout << "Welcome to a friendly game of hangman" << endl;
  cout << "Please enter a length for the word (4-8): ";
  cin  >> wordLength;
  wordP.assign(wordLength, '_');

}
//function to take user input for the length of word

void hangman::guessAmount()
{
  cout << endl << "How many guesses would you like: ";
  cin >> remGuesses;
  cout << endl;
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