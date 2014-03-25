class Pound
{
public:
	Pound(int poundVal, int shillingVal);
	//constructer

	Pound();
	//No-args Constructor

	void output();
	//Standard outptu

	friend Pound operator +(Pound& p1, Pound& p2);
	//friend method for operator

private:
	int pound, shilling;
	//Variables
};