/*
This program can print three different things.
What can be printed and what input causes these things to be printed?
*/
#include <iostream>
#include <windows.h> 

inline void Wait(int seconds)
{
    Sleep(seconds * 1000);
}

bool test1(int age)
{
	std::cout << "In test1\n";
	return age <= 12;
}

bool test2(int age)
{
	std::cout << "In test2\n";
	return age > 19;
}

int main()
{

	// Test
	int age;
	std::cout << "Enter your age: ";
	std::cin >> age;
	bool isTeenager = ! (test1(age) || test2(age));

	if(isTeenager)
		std::cout << "You are a teenager\n";
	else
		std::cout << "You not are a teenager\n";
	Wait(50);
}
