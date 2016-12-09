#include <iostream>
#include "ScoreCard.hpp"

using namespace std;

ScoreCard::ScoreCard(Dice &dice): _dice(dice) {
	cout << "ScoreCard constructor called" << endl;
	initScoringOptions();
	initPlayerOptions();
}

void ScoreCard::displayScoringOptions(){
	updateOptionsValues();

	auto scoreIt = _scoringOptions.begin();
	auto playerIt = _playerOptions.begin();

	cout << _scoringOptions.size() <<endl;
	while (scoreIt != _scoringOptions.end()){
		cout << scoreIt->first << ". " << scoreIt->second << "  ["
		 		 << playerIt->second.possibleValue << "]"    << endl;

				 scoreIt++;
				 playerIt++;
	}

}

void ScoreCard::updateOptionsValues(){
	// Update all scoring options done by sum of the dice value
 	for (int i = 1; i <= _dice.DICE_AMOUNT; i++){
	 	// The int repesents the scoring option so we can cast it here
	 	ScoreType currScoreType = static_cast<ScoreType>(i);
		_playerOptions[currScoreType].possibleValue  = getValueSum(i);
	}
	int sumOfDice = getSumOfDice();

	_playerOptions[ScoreType::ThreeOfAKind].possibleValue =
							_dice.hasThreeOfAKind() ? sumOfDice : 0;
	_playerOptions[ScoreType::FourOfAKind].possibleValue =
							_dice.hasFourOfAKind() ? sumOfDice : 0;
	_playerOptions[ScoreType::FullHouse].possibleValue =
							_dice.hasFullHouse() ? FULL_HOUSE_VAL : 0;
	_playerOptions[ScoreType::SmallStraight].possibleValue =
							_dice.hasSmallStraight() ? SMALL_STRAIGHT_VAL : 0;
	_playerOptions[ScoreType::LargeStraight].possibleValue =
							_dice.hasLargeStraight() ? LARGE_STRAIGHT_VAL : 0;
	_playerOptions[ScoreType::Yahtzee].possibleValue =
							_dice.hasYahtzee() ? YAHTZEE_VAL : 0;

	_playerOptions[ScoreType::Chance].possibleValue = sumOfDice;
}

int ScoreCard::getValueSum(int value){
	int frequency = _dice.getValueFrequency(value);
	return frequency * value;
}

// could combine this with getValueSum to prevent repeating calls
int ScoreCard::getSumOfDice(){
	int diceSum = 0;

	for (int i = 1; i <= _dice.DICE_AMOUNT; i++){
		diceSum += getValueSum(i);
	}

	return diceSum;
}

// TODO: if the scoring option is in upper section list
// add to that score and check if bonus is hit
// same for upper
void ScoreCard::selectScoringOption(int selection){
	cout << "In selectScoringOption()" << endl;
}

void ScoreCard::initScoringOptions(){
	_scoringOptions[ScoreType::AcesSum] = "Sum of Ones";
	_scoringOptions[ScoreType::TwosSum] = "Sum of Twos";
	_scoringOptions[ScoreType::ThreesSum] = "Sum of Threes";
	_scoringOptions[ScoreType::FoursSum] = "Sum of Fours";
	_scoringOptions[ScoreType::FivesSum] = "Sum of Fives";
	_scoringOptions[ScoreType::SixesSum] = "Sum of Sixes";
	_scoringOptions[ScoreType::ThreeOfAKind] = "Three of a Kind";
	_scoringOptions[ScoreType::FourOfAKind] = "Four of a Kind";
	_scoringOptions[ScoreType::FullHouse] = "Full House";
	_scoringOptions[ScoreType::SmallStraight] = "Small Straight";
	_scoringOptions[ScoreType::LargeStraight] = "Large Straight";
  _scoringOptions[ScoreType::Chance] = "Chance";
	_scoringOptions[ScoreType::Yahtzee] = "Yahtzee";
}

void ScoreCard::initPlayerOptions(){
	// Score values based on certain dice value
	_playerOptions[ScoreType::AcesSum] = {0, -1, false};
	_playerOptions[ScoreType::TwosSum] = {0, -1, false};
	_playerOptions[ScoreType::ThreesSum] = {0, -1, false};
	_playerOptions[ScoreType::FoursSum] = {0, -1, false};
	_playerOptions[ScoreType::FivesSum] = {0, -1, false};
	_playerOptions[ScoreType::SixesSum] = {0, -1, false};
	// Score values based on sum
	_playerOptions[ScoreType::ThreeOfAKind] = {0, -1, false};
	_playerOptions[ScoreType::FourOfAKind] = {0, -1, false};
	_playerOptions[ScoreType::Chance] = {0, -1, false};
	// Constant scoring values
	_playerOptions[ScoreType::FullHouse] = {0, -1, false};
	_playerOptions[ScoreType::SmallStraight] = {0, -1, false};
	_playerOptions[ScoreType::LargeStraight] = {0, -1, false};
	_playerOptions[ScoreType::Yahtzee] = {0, -1, false};
}
