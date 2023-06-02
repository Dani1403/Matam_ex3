#include "HealthPoints.h"

HealthPoints::HealthPoints(int maxHp) {
	if (maxHp <= 0)
	{
		throw HealthPoints::InvalidArgument();
	}
	this->m_maxHealthPoints = maxHp;
	this->m_healthPoints = maxHp;
}

/* Arithmetic Operators */

HealthPoints& HealthPoints::operator+=(const int hpToAdd)
{
	if (this->getHealthPoints() + hpToAdd > this->getMaxHealthPoints())
	{
		this->setHealthPoints(this->getMaxHealthPoints());
	}
	else
	{
		this->setHealthPoints(this->getHealthPoints() + hpToAdd);
	}
	return *this;
}

HealthPoints& HealthPoints::operator-=(const int hpToSubtract)
{
	if (this->getHealthPoints() - hpToSubtract < 0)
	{
		this->setHealthPoints(0);
	}
	else
	{
		this->setHealthPoints(this->getHealthPoints() - hpToSubtract);
	}
	return *this;	
}

HealthPoints operator+(const HealthPoints& hp, const int hpToAdd)
{
	HealthPoints result = hp;
	result += hpToAdd;
	return result;
}

HealthPoints operator+(const int hpToAdd, const HealthPoints& hp)
{
	return hp + hpToAdd;
}

HealthPoints operator-(const HealthPoints& hp, const int hpToSubtract)
{
	HealthPoints result = hp;
	result -= hpToSubtract;
	return result;
}

HealthPoints operator-(const int hpToSubtract, const HealthPoints& hp)
{
	return hp - hpToSubtract;
}

/* Boolean Operators */

bool operator==(const HealthPoints& hp1, const HealthPoints& hp2)
{
	return hp1.getHealthPoints() == hp2.getHealthPoints();
}

bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2)
{
	return !(hp1 == hp2);
}

bool operator<(const HealthPoints& hp1, const HealthPoints& hp2)
{
	return hp1.getHealthPoints() < hp2.getHealthPoints();
}

bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2)
{
	return !(hp1 < hp2);
}

bool operator>(const HealthPoints& hp1, const HealthPoints& hp2)
{
	return hp2 < hp1;
}

bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2)
{
	return !(hp1 > hp2);
}

/* Stream Operator */
std::ostream& operator<<(std::ostream& os, const HealthPoints& hp)
{
	os << hp.getHealthPoints() << "(" << hp.getMaxHealthPoints() << ")";
	return os;
}


int main()
{
	bool comparisonResult;
	HealthPoints healthPoints1(100);
	HealthPoints healthPoints2 = 100; /* 100 points out of 100 */
	comparisonResult = (healthPoints1 == healthPoints2); /* returns true */
	healthPoints2 = HealthPoints(150); /* has 150 points out of 150 */
	comparisonResult = (healthPoints1 == healthPoints2); /* returns false */
	healthPoints2 -= 50; /* now has 100 points out of 150 */
	comparisonResult = (100 == healthPoints2); /* returns true */
	comparisonResult = (healthPoints1 < healthPoints2); /* returns false */
	healthPoints1 -= 50; /* now has 50 points out of 100 */
	comparisonResult = (healthPoints1 < healthPoints2); /* returns true */
	std::cout << healthPoints1 << ", " << healthPoints2; /* output is "50(100), 100(150)" */
}