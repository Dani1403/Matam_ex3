#ifndef HEALTH_POINTS
#define HEALTH_POINTS 

#include <iostream>
const int DEFAULT_HEALTH_POINTS = 100;

class HealthPoints
{
public :
	/* Constructor */
	HealthPoints(int healthPoints = DEFAULT_HEALTH_POINTS);

	/* Copy Constructor, Destructor and Assignment Operator */
	HealthPoints(const HealthPoints& hp2) = default;
	~HealthPoints() = default;
	HealthPoints& operator=(const HealthPoints& other) = default;

	/* Getter and Setter */
	int getHealthPoints() const { return m_healthPoints; }
	int getMaxHealthPoints() const { return m_maxHealthPoints; }
	void setHealthPoints(int healthPoints) { m_healthPoints = healthPoints; }
	void setMaxHealthPoints(int maxHealthPoints) { m_maxHealthPoints = maxHealthPoints; }

	/* Arithmetic Operator Overloading */
	HealthPoints& operator+=(const int hpToAdd);
	HealthPoints& operator-=(const int hpToSubstract);

	/* Exception Classes */
	class InvalidArgument {};

private:
	int m_healthPoints;
	int m_maxHealthPoints;
};

/* Arithmetic Operator Overloading */
HealthPoints operator+(const HealthPoints& hp, const int hpToAdd);
HealthPoints operator+(const int hpToAdd, const HealthPoints& hp);
HealthPoints operator-(const HealthPoints& hp, const int hpToSubstract);
HealthPoints operator-(const int hpToSubstract, const HealthPoints& hp);

/* Boolean Operator Overloading */
bool operator==(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator<(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator>(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2);
bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2);

/* Stream Operator Overloading */
std::ostream& operator<<(std::ostream& os, const HealthPoints& hp);


#endif //HEALTH_POINTS
