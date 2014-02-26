#include <iostream>
using namespace std;
#include <windows.h> 

inline void Wait(int seconds)
{
    Sleep(seconds * 1000);
}

void test(int &x)
{
	x += 4;
}

int main()
{

	int x = 3;
	test(x);
	cout << "x = " << x << endl;

	Wait(50);
}
