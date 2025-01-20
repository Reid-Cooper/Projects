#ifndef Tiles_hpp
#define Tiles_hpp
#include "player.hpp"
#include <iostream>
using namespace std;

class Tile{
public:

Tile();

//getters
char getTileColor();
string getTypeOfTiile();
int getTilePosition();
int getTimesTileLandedOn(); //possible future addition of having different effects if the tile has been landed on before

//setters
void setTileColor(char input);
void setTypeOfTile(string input);
void setTilePosition(int input);
void setTimesTileLandedOn(int input);

private:
char color;
string tileType;
int tilePosition;
int timesTileLandedOn;

};
#endif //tiles_hpp