// No constructors

#include <iostream>

using std::cout;

class CDDate
{
	public:
		void output();
		int day;
		int month;
};

int main()
{
        // a lovely day ;)
        CDDate date; // Whate date is this
	date.output();

	date.day = date.month = 8;

	date.output();
}

void CDDate::output()
{
	cout << "CDDate(" << day << ", " << month << ")\n";
}
