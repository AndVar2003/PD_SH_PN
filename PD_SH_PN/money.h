#pragma once
#include <ostream>
class money
{
public:
	void setD(long aX, long aY, double aZ, long long sum);
	double getD() const;
	money(long aX = 0, long aY = 0, double aZ = 0, long long sum = 0);
	bool operator == (const money&) const;
	bool operator != (const money&) const;
	bool operator > (const money&) const;
	bool operator < (const money&) const;
	friend std::ostream& operator << (std::ostream&, const money&);
	money operator - () const;
	money operator + (const money&) const;
	money operator - (const money&) const;
	money operator += (const money&);
	money operator -= (const money&);
private:
	long long poly_pens;
};

