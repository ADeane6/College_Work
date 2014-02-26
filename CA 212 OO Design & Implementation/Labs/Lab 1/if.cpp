
#include <iostream>
using namespace std;
#include <windows.h> 

inline void Wait(int seconds)
{
    Sleep(seconds * 1000);
}

int main()
{
	int age;
	cout << "Enter your Age: ";
	cin >> age;
	if (0 < age && age < 10) //works but if its 0 < age < 10 it cuts if first half is correct
	{
		cout << "Teen";
	}
	else
		cout << "Not Teen";

	Wait(50);
}