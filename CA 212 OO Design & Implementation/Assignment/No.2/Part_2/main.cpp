#include "hangman.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h> 
using namespace std;



void printVec(vector<string> word)
{
	for(int i = 0; i < word.size(); i++)
	{
		cout << word[i] << " ";
	}
	cout << endl << "|" << endl;
}

void printVec(vector<char> word)
{
	for(int i = 0; i < word.size(); i++)
	{
		cout << word[i] << " ";
	}
	cout << endl << "|" << endl;
}


void printStickMan(string i)
{
	if (i.compare("Lost") == 0)
	{
		cout << "Unfortunately you Lost" << endl;
		cout << "______" << endl << "|   |" << endl << "|   O" << endl << "|  /|\\" << endl << "|  / \\" << endl << "|" << endl << "~~~~~~~~" << endl;
	}
	else
	{
		cout << "Well done you Won" << endl;
		cout << endl << "  O" << endl << " /|\\" << endl << " / \\" << endl << "~~~~~~~" << endl;
	}
}


int main()
{
//-----------------Setup-----------------//
	hangman game;
	char cguess;
	int complete = 0;

	game.userSetup();

	game.fillWordList();
	
	game.pickRandWord();
	vector<char> wordC (game.word.begin(), game.word.end());

	if(game.debugMode)
		cout << game.word << endl;


//-----------------Main Game-----------------//
	//while loop to play normal hangman
	while (complete < game.wordLength)
	{
		if(!game.getGuess())
		{
			cout << "please use new letter!!!" << endl;
			game.remGuesses--;
		}

		else
		{
			
			//for version one this is always false
			if(game.findBestPos())
			{
				game.word = game.Words[0];
				wordC.assign (game.word.begin(), game.word.end());

				//print word
				if(game.debugMode)
					cout << "Current Word: " << game.word << endl;
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
			else
			{
				game.remGuesses--;
			}	
		}
		//print how far player has gotten got
		printVec(game.wordP);

		if(!game.outputUpdate())
			break;
	}



//-----------------End Game-----------------//
	if(game.remGuesses != 0)
		printStickMan("Won");
	else
		printStickMan("Lost");

	cout << "the word was: " << game.word << endl;
}

