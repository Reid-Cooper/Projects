#include "player.hpp"
#include <iostream>
using namespace std;

//constructors
player :: player(){

_name = "";
_age = 1;
_strength = 100;
_stamina = 100;
_wisdom = 100;
_pride_points = 0;
advisor = 0;
position = 0;
playersTurn = false;
advisorPowerUps = 0;
poweredUpPlayer = false;
numberofTurnsTaken = 0;
lionBirthday = false;
usedConversion = false;

}

player :: player(string characterName, int characterStrength, int characterStamina, int characterWisdom){

//strength check
if(characterStrength > 1000){
    characterStrength = 1000;
}
if(characterStrength < 100){
    characterStrength = 100;
}

//stamina check
if(characterStamina > 1000){
    characterStamina = 1000;
}
if(characterStamina < 100){
    characterStamina = 100;
}

//wisdom check
if(characterWisdom > 1000){
    characterWisdom = 1000;
}
if(characterWisdom < 100){
    characterWisdom = 100;
}

_name = characterName;
_age = 1;
_strength = characterStrength;
_stamina = characterStrength;
_wisdom = characterWisdom;
_pride_points = 0;
advisor = 0;
position = 0;
playersTurn = false;
advisorPowerUps = 0;
poweredUpPlayer = false;
numberofTurnsTaken = 0;
lionBirthday = false;
usedConversion = false;

}

//getters
string player :: getName() const{
    return _name;
}

int player :: getStrength() const{
    return _strength;
}

int player :: getStamina() const{
    return _stamina;
}

int player :: getWisdom() const{
    return _wisdom;
}

int player :: getPridePoints() const{
    return _pride_points;
}

int player :: getAge() const{
    return _age;
}

int player :: getAdvisor() const{
    return advisor;
}

int player :: getPathTaken() const{
    return pathSelected;
}

int player :: getPlayerPosition() const{
    return position;
}

bool player :: getPlayersTurn() const{
    return playersTurn;
}

int player :: getAdvisorPowerUps() const{
    return advisorPowerUps;
}

bool player :: getPoweredUpPlayer() const{
    return poweredUpPlayer;
}

int player :: getNumberOfTurnsTaken() const{
    return numberofTurnsTaken;
}

bool player :: getLionBirthday() const{
    return lionBirthday;
}

bool player :: getUsedConversion() const{
    return usedConversion;
}

//setters
void player :: setName(string newName){
    _name = newName;
}

void player :: setStrength(int newStrength){
if(newStrength < 0){
    newStrength = 0;
}
_strength = newStrength;
}

void player :: setStamina(int newStamina){
if(newStamina < 0){
    newStamina = 0;
}
_stamina = newStamina;
}

void player :: setWisdom(int newWisdom){
if(newWisdom < 0){
    newWisdom = 0;
}
_wisdom = newWisdom;
}

void player :: setPridePoints(int newPridePoints){
if(newPridePoints < 0){
    newPridePoints = 0;
}
_pride_points = newPridePoints;
}

void player :: setAge(int newAge){
    _age = newAge;
}

void player :: setAdvisor(int newAdvisor){
    advisor = newAdvisor;
}

void player :: setAdvisorPowerUps(int amountOfPowerUps){
    advisorPowerUps = amountOfPowerUps;
}

void player :: setPathSelected(int pathTaken){
    pathSelected = pathTaken;
}

void player :: setPlayerPosition(int newPosition){
    if(newPosition <= 0){
        newPosition = 0;
    }
    else{
    position = newPosition;
    }
}

void player :: setPlayersTurn(bool trueOrFalse){
    playersTurn = trueOrFalse;
}

void player :: setpoweredUpPlayer(bool truuOrFalse){
    poweredUpPlayer = truuOrFalse;
}

void player :: setNumberOfTurnsTaken(int turnsTaken){
    numberofTurnsTaken = turnsTaken;
}

void player :: setLionBirthday(bool trueOrFalse){
    lionBirthday = trueOrFalse;
}

void player :: setUsedConversion(bool trueOrFalse){
    usedConversion = trueOrFalse;
}

void player :: makePlayerPositionZero(){
    position = 0;
}

//adders
void player :: incrementPlayerPosition(int input){
    setPlayerPosition(getPlayerPosition() + input);
}

void player :: addPridePoints(int n){

setPridePoints(getPridePoints() + n);

}

void player :: addAdvisorPowerUps(int n){
    setAdvisorPowerUps(getAdvisorPowerUps() + n);
}

void player :: addPlayerPosition(int n){
    setPlayerPosition(getPlayerPosition() + n);
}

void player :: addNumberOfTurnsTaken(int n){
    setNumberOfTurnsTaken(getNumberOfTurnsTaken() + n);
}

//additonal functions
void player :: trainCub(int strength, int stamina, int wisdom){

setStrength(getStrength() + strength);
setStamina(getStamina() + stamina);
setWisdom(getWisdom() + wisdom);
setPridePoints(getPridePoints() - 5000);
advisor = true;

}

void player :: toPrideLands(){

setStrength(getStrength() - 250);
setStamina(getStamina() - 250);
setWisdom(getWisdom() - 300);
setPridePoints(getPridePoints() + 5000);
advisor = false;

}

void player :: convertStatsToPridePoints(int strengthAmount, int staminaAmount, int wisdomAmount){

int strengthMultipleFactor = strengthAmount / 100;
int staminaMultipleFactor = staminaAmount / 100;
int wisdomMultipleFactor = wisdomAmount / 100;
int totalMultiple = strengthMultipleFactor + staminaMultipleFactor + wisdomMultipleFactor;

addPridePoints(totalMultiple * 1000);

}

void player :: findLowestStatAndConvert(int lowestLeaderShipStat){
    
//cout << lowestLeaderShipStat << endl;

//whichever is the lowest stat will gain 100 points at the cost of 1000 pride points
if(getWisdom() == lowestLeaderShipStat){
    addPridePoints(-1000);
    setWisdom(getWisdom() + 100);
    cout << "Exchange successful! You have gained 100 Wisdom!" << endl;
}

else if(getStamina() == lowestLeaderShipStat){
    addPridePoints(-1000);
    setStamina(getStamina() + 100);
    cout << "Exchange successful! You have gained 100 Stamina" << endl;
}

else if(getWisdom() == lowestLeaderShipStat){
    addPridePoints(-1000);
    setStrength(getStrength() + 100);
    cout << "Exchange successful! You have gained 100 Strength!" << endl;
}

}

void player :: checkIfAnyStatsAreZero(){

if(getStrength() == 0 || getStamina() == 0 || getWisdom() == 0){
    cout << "YOU ATTEMPTED TO TAKE A TURN WITH ONE OF YOUR LEADERSHIP STATS AT ZERO (0). IN ORDER TO RECOVER 100 POINTS OF THE STAT YOUR CHARACTER LOOSES 5000 PRIDE POINTS." << endl;

    //The player looses 5000 pride points and gains 100 points of whichever stat fell to zero
    addPridePoints(-5000);
    if(getStrength() == 0){
        setStrength(getStrength() + 100);
    }
    if(getStamina() == 0){
        setStamina(getStamina() + 100);
    }
    if(getWisdom() == 0){
        setWisdom(getWisdom() + 100);
    }
cout << endl;
}

}

void player :: printStats(){

cout << getName() << "'s stats:" << endl;
cout << "Age: " << getAge() << endl;
cout << "Strength: " << getStrength() << endl;
cout << "Stamina: " << getStamina() << endl;
cout << "Wisdom: " << getWisdom() << endl;
cout << "Pride Points: " << getPridePoints() << endl;

if(advisor == 0){
    cout << "Advisor: No Advisor" << endl; 
}
if(advisor == 1){
    cout << "Advisor: Rafiki (invisibility)" << endl;
}
if(advisor == 2){
    cout << "Advisor: Nala (night vision)" << endl;
}
if(advisor == 3){
    cout << "Advisor: Sarabi (energy manipulation)" << endl;
}
if(advisor == 4){
    cout << "Advisor: Zazu (weather control)" << endl;
}
if(advisor == 5){
    cout << "Advisor: Sarafina (super speed)" << endl;
}

cout << "Number of Turns Taken: " << numberofTurnsTaken << endl;
cout << "----------------------------------------------" << endl;
}