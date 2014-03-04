#include <iostream>

using std::cout;
using std::endl;

struct testStruct
{
	int x;
	double y;
} ts;

// Accessing the hidden global variable with :: (i.e. no namespace)

int main()
{
	struct testStruct ts;

	ts.x = 9;
	::ts.y = 20;

	cout << "ts.y = " << ts.y << ", ts.x = " << ts.x << endl;
	cout << "::ts.y = " << ::ts.y << ", ::ts.x = " << ::ts.x << endl;
}
