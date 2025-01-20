#include "Tiles.hpp"
#include <iostream>
using namespace std;

//constructor(s)
Tile :: Tile(){
    color = 'Y';
}

//getters
char Tile :: getTileColor(){
    return color;
}

string Tile :: getTypeOfTiile(){
    return tileType;
}

int Tile :: getTilePosition(){
    return tilePosition;
}

int Tile :: getTimesTileLandedOn(){
    return timesTileLandedOn;
}

//setters
void Tile :: setTileColor(char input){
    color = input;
}

void Tile :: setTypeOfTile(string input){
    tileType = input;
}

void Tile :: setTilePosition(int input){
    tilePosition = input;
}

void Tile :: setTimesTileLandedOn(int input){
    timesTileLandedOn = input;
}