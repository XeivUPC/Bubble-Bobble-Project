#include "PuntuationManager.hpp"

PuntuationManager::PuntuationManager(int* p1, int* p2, int* highScore,SystemCalls* calls, TextUI* UI)
{
	_calls = calls;
	_UI = UI;
	_p1 = p1;
	_p2 = p2;
	_highScore = highScore;

	_calls->updateCall.push_back(this);
}

void PuntuationManager::Update()
{
    if (_highScore < _p1 || _highScore < _p2)
    {
        if (_p1 < _p2)
            _highScore = _p2;
        else
            _highScore = _p1;
    }

    /// ToDO --> newClass
    int playerPoints = *_p1;
    if (playerPoints < 10) {
        int numTile = FromNumberToTile(0);

        _UI->UI[6] = numTile;
    }
    for (size_t i = 7; i >= 0; i--)
    {

        int num = playerPoints % 10;

        int numTile = FromNumberToTile(num);

        _UI->UI[i] = numTile;

        playerPoints -= num;
        playerPoints /= 10;
        if (playerPoints < 1)
            break;
    }

    playerPoints = *_p2;
    if (playerPoints < 10) {
        int numTile = FromNumberToTile(0);

        _UI->UI[27] = numTile;
    }
    for (size_t i = 28; i >= 0; i--)
    {

        int num = playerPoints % 10;

        int numTile = FromNumberToTile(num);

        _UI->UI[i] = numTile;

        playerPoints -= num;
        playerPoints /= 10;
        if (playerPoints < 1)
            break;
    }

    playerPoints = *_highScore;
    if (playerPoints < 10) {
        int numTile = FromNumberToTile(0);

        _UI->UI[17] = numTile;
    }
    for (size_t i = 18; i >= 0; i--)
    {

        int num = playerPoints % 10;

        int numTile = FromNumberToTile(num);

        _UI->UI[i] = numTile;

        playerPoints -= num;
        playerPoints /= 10;
        if (playerPoints < 1)
            break;
    }
}

int PuntuationManager::FromNumberToTile(int num)
{
    switch (num)
    {
    case 0:
        return 199;
    case 1:
        return 200;
    case 2:
        return 201;
    case 3:
        return 202;
    case 4:
        return 203;
    case 5:
        return 204;
    case 6:
        return 205;
    case 7:
        return 206;
    case 8:
        return 207;
    case 9:
        return 208;
    default:
        break;
    }
}
