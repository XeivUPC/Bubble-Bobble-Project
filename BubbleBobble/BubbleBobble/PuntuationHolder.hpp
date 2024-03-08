#pragma once
class PuntuationHolder
{
public:
	PuntuationHolder(int initialAmount, int initialMultiplier);
	int GetPuntuation() const;
	void ModifyPuntutation(int amount);
	void SetPuntutation(int value);
	int GetMultiplier() const;
	void SetMultiplier(int value);
private:
	int points;
	int multiplier;
};

