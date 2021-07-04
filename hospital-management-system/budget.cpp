#include "Budget.hpp"

Budget::Budget()
	:mAmount(0.0)
{}

Budget::Budget(double amount)
	:mAmount(amount)
{}

double Budget::getAmount() const
{
	return mAmount;
}

void Budget::operator+=(double amount)
{
	mAmount += amount;
}

double Budget::operator+(double amount)
{
	return mAmount + amount;
}

void Budget::operator-=(double amount)
{
	mAmount -= amount;
}

double Budget::operator-(double amount)
{
	return mAmount - amount;
}

void Budget::operator=(double amount)
{
	mAmount = amount;
}

double Budget::operator/(double amount)
{
	return mAmount / amount;
}

double Budget::operator*(double amount)
{
	return mAmount * amount;
}

bool Budget::operator<=(double amount)
{
	return mAmount <= amount;
}

bool Budget::operator<(double amount)
{
	return mAmount < amount;
}

bool Budget::operator>=(double amount)
{
	return mAmount >= amount;
}

bool Budget::operator>(double amount)
{
	return mAmount > amount;
}

std::ostream& operator<<(std::ostream& out, const Budget& b)
{
	out << b.mAmount;
	return out;
}

std::istream& operator>>(std::istream& in, Budget& b)
{
	in >> b.mAmount;
	return in;
}
