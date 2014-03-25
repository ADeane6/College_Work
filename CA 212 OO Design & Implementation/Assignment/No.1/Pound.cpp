#include "Pound.h"
#include <iostream>
#include <iomanip>
using namespace std;

Pound::Pound(int poundVal, int shillingVal) : pound(poundVal), shilling(shillingVal)
{
	pound += shilling/20;
	shilling = shilling%20;
}

Pound::Pound()
{
	pound = 0;
	shilling = 0;
}

void Pound::output()
{
	cout << setfill(' ') << setw(2) << pound << ":";
	cout << setfill('0') << setw(2) << shilling << endl;
}

Pound operator +(Pound& p1, Pound& p2)
{
	int p = p1.pound + p2.pound;
	int shil = p1.shilling + p2.shilling;
	p += shil/20;
	shil = shil%20;

	return Pound(p, shil);
}