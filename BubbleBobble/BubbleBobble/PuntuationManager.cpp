#include "PuntuationManager.hpp"

PuntuationManager::PuntuationManager(GameManager* gameManager, PuntuationHolder* p1, PuntuationHolder* p2, PuntuationHolder* highScore, TextUI* UI)
{
    _gm = gameManager;
	_UI = UI;
	_p1 = p1;
	_p2 = p2;
	_highScore = highScore;

	_gm->calls.updateCall.push_back(this);
}

void PuntuationManager::Update()
{
    if (_highScore->GetPuntuation() < _p1->GetPuntuation() || _highScore->GetPuntuation() < _p2->GetPuntuation())
    {
        if (_p1->GetPuntuation() < _p2->GetPuntuation())
            _highScore->SetPuntutation(_p2->GetPuntuation());
        else
            _highScore = _p1;
    }

    /// ToDO --> newClass
    int playerPoints = _p1->GetPuntuation();
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

    playerPoints = _p2->GetPuntuation();
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

    playerPoints = _highScore->GetPuntuation();
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
        return 208;
    case 1:
        return 209;
    case 2:
        return 210;
    case 3:
        return 211;
    case 4:
        return 212;
    case 5:
        return 213;
    case 6:
        return 214;
    case 7:
        return 215;
    case 8:
        return 216;
    case 9:
        return 217;
    default:
        break;
    }
}
