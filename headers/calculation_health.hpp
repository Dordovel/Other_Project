#pragma once

class CalculationHealth
{
	private:
		int _healthBarSize;
		int _healthPersonSize;

	public:
		CalculationHealth(int healthBarSize, int _healthPersonSize);
		float get_value(float value);

		~CalculationHealth() = default;
};

