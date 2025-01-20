#ifndef player_hpp
#define player_hpp
#include <iostream>
using namespace std;

class player{
public:

//constructors
player();
player(string characterName, int characterStrength, int characterStamina, int characterWisdom);

//getters
string getName() const;
int getStrength() const;
int getStamina() const;
int getWisdom() const;
int getPridePoints() const;
int getAge() const;
int getAdvisor() const;
int getPathTaken() const;
int getPlayerPosition() const;
bool getPlayersTurn() const;
int getAdvisorPowerUps() const;
bool getPoweredUpPlayer() const;
int getNumberOfTurnsTaken() const;
bool getLionBirthday() const;
bool getUsedConversion() const;

//setters
void setName(string newName);
void setStrength(int newStrength);
void setStamina(int newStamina);
void setWisdom(int newWisdom);
void setPridePoints(int newPridePoints);
void setAge(int newAge);
void setAdvisor(int newAdvisor);
void setPathSelected(int pathTaken);
void setPlayerPosition(int newPosition);
void setPlayersTurn(bool trueOrFalse);
void setAdvisorPowerUps(int numberOfPowerUps);
void setpoweredUpPlayer(bool trueOrFalse);
void setNumberOfTurnsTaken(int numberOfTurns);
void setLionBirthday(bool trueOrFalse);
void setUsedConversion(bool trueOrFalse);
void makePlayerPositionZero();

//adder functions and conversions
void addPridePoints(int n);
void addPlayerPosition(int n);
void addAdvisorPowerUps(int n);
void addNumberOfTurnsTaken(int n);
void incrementPlayerPosition(int input);
void findLowestStatAndConvert(int lowestLeaderShipStat);
void checkIfAnyStatsAreZero();
void convertStatsToPridePoints(int strengthAmount, int staminaAmount, int wisdomAmount);

//additional functions
//trainCub and toPrideLands determine the stats changes the player expeirences if they take that path
void trainCub(int strength, int stamina, int wisdom);
void toPrideLands();
void printStats();

private:
string _name;
int _strength, _stamina, _wisdom, _pride_points, _age;
int advisor;
int pathSelected;
int position;
bool playersTurn;
int advisorPowerUps; //used to negate the negative effects of specific tiles
bool poweredUpPlayer; 
int numberofTurnsTaken; 
bool lionBirthday; //every 5 turns the player takes they will have a missable birthday event to interact with
bool usedConversion; //each turn the player has an option to convert 1000 of their pride points in 100 points of their lowest stat

};

#endif 