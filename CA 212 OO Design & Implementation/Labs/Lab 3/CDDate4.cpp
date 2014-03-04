// Add a constructor

#include <iostream>

using std::cout;

class CDDate
{
	public:
		CDDate(int d, int m);
		//CDDate();
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

CDDate::CDDate(int d, int m)
{
	day = d;
	month = m;
}

/*
CDDate::CDDate()
{
	day = 0;
	month = 0;
}
*/

void CDDate::output()
{
	cout << "CDDate(" << day << ", " << month << ")\n";
}
