#include "Tournament.h"


Tournament::Tournament(string firstPlaceName1, string firstPlaceName2, int firstPlaceScore,string secondPlaceName1, string secondPlaceName2, int secondPlaceScore,string thirdPlaceName1, string thirdPlaceName2, int thirdPlaceScore)
{
    this->firstPlaceName1 = firstPlaceName1;
    this->firstPlaceName2 = firstPlaceName2;
    this->firstPlaceScore = firstPlaceScore;

    this->secondPlaceName1 = secondPlaceName1;
    this->secondPlaceName2 = secondPlaceName2;
    this->secondPlaceScore = secondPlaceScore;

    this->thirdPlaceName1 = thirdPlaceName1;
    this->thirdPlaceName2 = thirdPlaceName2;
    this->thirdPlaceScore = thirdPlaceScore;
}