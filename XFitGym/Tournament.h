#pragma once

#include <String>
using namespace std;
class Tournament
{
private:
	// 1st place data
	string firstPlaceName1;
	string firstPlaceName2;
	int firstPlaceScore;


	// Second place data
	string secondPlaceName1;
	string secondPlaceName2;
	int secondPlaceScore;


	// Third place data
	string thirdPlaceName1;
	string thirdPlaceName2;
	int thirdPlaceScore;

public:
	Tournament(string firstPlaceName1, string firstPlaceName2, int firstPlaceScore,string secondPlaceName1, string secondPlaceName2, int secondPlaceScore,string thirdPlaceName1, string thirdPlaceName2, int thirdPlaceScore);


};

