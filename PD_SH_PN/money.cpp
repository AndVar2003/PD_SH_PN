#include "money.h"
#include <exception>
long long R;
void money::setD(long aX, long aY, double aZ, long long sum)
{
	if ((abs(aX) > 1000000000) || (abs(aX) == 1000000000 && (aY > 0 || aZ > 0)))
	{
		throw std::exception("Error! Your emount of money > billion pounds");
	}
	if (aY >= 20 || (aX != 0 && aY < 0))
	{
		throw std::exception("Error! Invalid shilling input");
	}
	if (aZ >= 12 || ((aX != 0 || aX == 0) && aY != 0 && aZ < 0) || (int(aZ * 2) != (aZ * 2)))
	{
		throw std::exception("Error! Invalid pens input");
	}
	if (aX < 0 || aY < 0 || aZ < 0)
		poly_pens = -(((abs((long long)aX) * 20 + abs((long long)aY)) * 24) + 2 * fabs(aZ));
	else
		poly_pens = ((abs((long long)aX) * 20 + abs((long long)aY)) * 24) + 2 * fabs(aZ);
}
double money::getD() const
{
	return poly_pens;
}

money::money(long aX, long aY, double aZ, long long sum)
{
	setD(aX, aY, aZ, sum);
}

double Perevod(long* pa, long* pb, double* pc, long long Sum)
{
	if (abs(Sum) > 4.8e11)
		throw 1;
	if (Sum >= 0)
	{

		(*pa) = Sum / 480;
		(*pb) = (Sum % 480) / 24;
		(*pc) = (double)((Sum % 480) % 24) / 2;
	}
	else
	{
		if (abs(Sum) >= 480)
		{
			(*pa) = Sum / 480;
			(*pb) = -(Sum % 480) / 24;
			(*pc) = -(double)((Sum % 480) % 24) / 2;
		}
		if (abs(Sum) < 480 && (abs(Sum) >= 24))
		{
			(*pb) = (Sum % 480) / 24;
			(*pc) = -(double)(Sum % 24) / 2;
		}
		if (abs(Sum) < 24)
		{
			(*pc) = (double)Sum / 2;
		}
	}
}

bool money::operator == (const money& p) const
{
	return (poly_pens == p.poly_pens);
}
bool money::operator != (const money& p) const
{
	return (!this ->operator==(p));
}

bool money::operator>(const money& p) const
{
	return (poly_pens > p.poly_pens);
}

bool money::operator<(const money& p) const
{
	return (poly_pens < p.poly_pens);
}

std::ostream& operator << (std::ostream& s, const money& p)
{
	long pound = 0;
	long shilling = 0;
	double pens = 0;
	Perevod(&pound, &shilling, &pens, p.poly_pens);
	if (pound != 0)
		s << pound << "pd.";
	if (shilling != 0)
		s << shilling << "sh.";
	if (pens != 0 || (pound == 0 && shilling == 0 && pens == 0))
		s << pens << "p.";
	return s;
}

money money::operator-() const
{
	return money(0, 0, 0, -poly_pens);
}
money money::operator+(const money& p) const
{
	long pound = 0;
	long shilling = 0;
	double pens = 0;
	R = poly_pens + p.poly_pens;
	Perevod(&pound, &shilling, &pens, R);
	return money(pound, shilling, pens, R);
}

money money::operator-(const money& p) const
{
	long pound = 0;
	long shilling = 0;
	double pens = 0;
	R = poly_pens - p.poly_pens;
	Perevod(&pound, &shilling, &pens, R);
	return money(pound, shilling, pens, R);
}

money money::operator+=(const money& p)
{
	money m(*this);
	poly_pens += p.poly_pens;
	return *this;
}

money money::operator-=(const money& p)
{
	money m(*this);
	poly_pens -= p.poly_pens;
	return *this;
}
