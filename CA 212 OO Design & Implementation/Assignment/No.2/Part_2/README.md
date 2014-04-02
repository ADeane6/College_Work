This is my version of Sneaky Hangman

it includes four files

-hangman.cpp
	 
	Which is the class hangman and all its methods for playing the game
-hangman.h
	 
	This holds all the headers for the hangman class
-main.cpp
	 
	This is the main program that sets up the game and plays it through
-dictionary.txt
	 
	This is a txt doc that holds a sample dictionary allowing you to play the game

The password for debug mode is: pa$$w0rd
 
	while in debug mode it will give you an idea of how the word is chosen

The main algorithm for the game is located in the findBestPos() method
it finds the position of the guessed character thus keeping as many words
still viable to be the solution.
