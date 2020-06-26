#include "../headers/calculation_health.hpp"

CalculationHealth::CalculationHealth(int healthBarSize, int healthPersonSize):_healthBarSize(healthBarSize),
																				_healthPersonSize(healthPersonSize){}

float CalculationHealth::get_value(float value)
{
	return (this->_healthBarSize * ((value / this->_healthPersonSize) * 100)) / 100;
}
