#include "PuntuationHolder.hpp"

PuntuationHolder::PuntuationHolder(int initialAmount, int initialMultiplier)
{
	points = initialAmount;
	multiplier = initialMultiplier;
}

int PuntuationHolder::GetPuntuation() const
{
	return points;
}

void PuntuationHolder::ModifyPuntutation(int amount)
{
	points += amount * multiplier;
}

void PuntuationHolder::SetPuntutation(int value)
{
	points = value;
}

int PuntuationHolder::GetMultiplier() const
{
	return multiplier;
}

void PuntuationHolder::SetMultiplier(int value)
{
	multiplier = value;
}
