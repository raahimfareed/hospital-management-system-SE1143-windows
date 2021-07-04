#pragma once
#include <iostream>

class Budget
{
public:
	Budget();
	Budget(double amount);

	double getAmount() const;

	void operator+=(double amount);
	double operator+(double amount);
	void operator-=(double amount);
	double operator-(double amount);
	void operator=(double amount);
	double operator/(double amount);
	double operator*(double amount);
	bool operator<=(double amount);
	bool operator<(double amount);
	bool operator>=(double amount);
	bool operator>(double amount);
	friend std::ostream& operator<<(std::ostream& out, const Budget& b);
	friend std::istream& operator>>(std::istream& in, Budget& b);

private:
	double mAmount;
};
