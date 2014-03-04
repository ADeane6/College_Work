#include <iostream>

using std::cout;

class CDDate
{
	public:
		CDDate(int d, int m);
		CDDate();
		void output();
	private:
		int day;
		int month;
};

int main()
{
        // a lovely day ;)
        CDDate date(17, 3); // Paddy's day
        CDDate dayEile; // Whate date is this
	date.output();
	dayEile.output();
}

CDDate::CDDate(int d, int m)
{
	day = d;
	month = m;
}

// Why is this called the default constructor
CDDate::CDDate()
{
	day = 1;
	month = 1;
}

void CDDate::output()
{
	cout << "CDDate(" << day << ", " << month << ")\n";
}
