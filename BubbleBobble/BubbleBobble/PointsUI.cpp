#include "PointsUI.hpp"

PointsUI::PointsUI(PuntuationHolder* points, TilemapController* UI)
{
    this->UI = UI;
    this->points = points;

}

void PointsUI::Update()
{
    /// ToDO --> newClass
    int playerPoints = points->GetPuntuation();
    if (playerPoints < 10) {
        int numTile = FromNumberToTile(0);

        UI->ModifyTile(this->UI->GetDimensions().x-2, numTile);
    }
    for (size_t i = UI->GetDimensions().x - 1; i >= 0; i--)
    {

        int num = playerPoints % 10;

        int numTile = FromNumberToTile(num);

        UI->ModifyTile(i, numTile);

        playerPoints -= num;
        playerPoints /= 10;
        if (playerPoints < 1)
            break;
    }
}

int PointsUI::FromNumberToTile(int num)
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
