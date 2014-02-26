
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int a[] = {10, 20, 30, 40};

int main()
{
	int x = 25;
	// Can use a variable in array definition.
	int numbers[4];

	int y = 45;

	for(int i = 0; i < 4; i++)
		numbers[i] = a[i];

	cout << "x = " << x << endl;
	for(int i = 0; i < 4; i++)
		cout << "numbers[" << i << "] = " << numbers[i] << ", ";

	numbers[4] = -1;	// Note over the bounds of the array
	numbers[-1] = -2;	// Note over the bounds of the array
	numbers[-2] = -3;	// Note over the bounds of the array
	cout << endl;
	for(int i = 0; i < 4; i++)
		cout << "numbers[" << i << "] = " << numbers[i] << ", ";
	cout << endl;
	cout << "y = " << y << endl;
}
