/*

	This shows how structures are copied as parameters
*/

#include <iostream>

using std::cout;
using std::endl;

struct testStruct
{
	int x;
	double y;

};

void printStruct(testStruct& ts)
{
	cout << "Address = " << &ts << ", Data = (" << ts.x << ", " << ts.y << ")" << endl;	
}

// How would this differ if we passed by reference?
// Would it use more memory?
// Would it produce the same output. Explain the answer.
testStruct func(testStruct& ts)  // function receives a copy!
{
	cout << "In func\n";
	testStruct newTS = ts;  // Complete copy of the structure.

	ts.x += 3;

	printStruct(ts);
	newTS.y += 4;
	printStruct(newTS);

	cout << "Ex func\n";

	return newTS;
}

int main()
{
	cout << "In Main\n";
	struct testStruct ts;
	ts.x = 2;
	ts.y = 5;

	printStruct(ts);
	func(ts);	// ignore return value
	printStruct(ts);	// Has ts changed

	testStruct retTestStruct = func(ts);

	printStruct(ts);	// Has ts changed
	printStruct(retTestStruct);	// Has ts changed
}
