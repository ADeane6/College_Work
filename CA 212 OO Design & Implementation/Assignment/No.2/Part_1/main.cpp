#include "hangman.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h> 
using namespace std;




void printVec(vector<char> word)
{
	for(int i = 0; i < word.size(); i++)
	{
		cout << word[i] << " ";
	}
	cout << endl << "|" << endl;
}
//prints the vector argument with spaces in between


void printMan(int i)
{
	if (i == 0)
	{
		cout << "______" << endl << "|   |" << endl << "|   O" << endl << "|  /|\\" << endl << "|  / \\" << endl << "|" << endl << "~~~~~~~~" << endl;
	}
	else
		cout << endl << "  O" << endl << " /|\\" << endl << " / \\" << endl << "~~~~~~~" << endl;
}
//prints the stick man at the end


int main()
{
//-----------------Setup-----------------//
	hangman game;
	char cguess;
	int complete = 0;

	//get user input
	game.userLength();
	game.guessAmount();

	//fill list
	game.wordList(game.wordLength);

	//get a random word
	game.pickWord();
	vector<char> wordC (game.word.begin(), game.word.end());

	//checking for dev password
	game.debug();
	if(game.debugMode)
		cout << game.word << endl;



//-----------------Main Game-----------------//
	//while loop to play normal hangman
	while (complete < game.wordLength)
	{
		//get user guess
		//check if they already guessed that char
		if(game.getGuess())
		{
			cout << "please use new letter!!!" << endl;
			game.remGuesses--;
		}

		//continue if guess is new
		else
		{

			//for version one this is always false
			if(game.bestPos())
			{
				//this will be a word with a certain char in a place
				//game.pickWord();

				//put word into vector
				vector<char> wordC (game.word.begin(), game.word.end());

				//print word
				if(game.debugMode)
					cout << game.word << endl;
			}

			//this will always happen
			if(game.contains(wordC))
			{
				for (int i = 0; i < wordC.size(); i++)
				{
					if(wordC[i] == game.guess)
					{
						game.wordP[i] = game.guess;
						complete++;
					}
				}
			}

			//remove life if wrong
			else
			{
				game.remGuesses--;
			}	
		}

		//print how far player has gotten got
		printVec(game.wordP);

		//if out of guesses
		if(!game.update())
			break;
	}



//-----------------End Game-----------------//
	//check if wplayer Won
	if(game.remGuesses != 0)
	{
		cout << "Well done you Won" << endl;
		printMan(1);
	}
	//if player lost
	else
		printMan(0);

	cout << "the word was: " << game.word << endl;
}

