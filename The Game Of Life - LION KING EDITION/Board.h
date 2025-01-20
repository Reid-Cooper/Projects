#ifndef BOARD_H
#define BOARD_H
#include "Tiles.hpp"
#include "player.hpp"

class Board
{
private:

    //static elements
    static const int _BOARD_SIZE = 52;
    Tile _tiles[2][_BOARD_SIZE];
    static const int _MAX_PLAYERS = 2;

    //updating elements
    int _player_count;
    int _player_position[_MAX_PLAYERS];
    player playersArray[2];

    //different path generation functions
    //pride-lands have higher percentages to generate negative tiles, training path contains more positive tiles
    void prideLandsPath(int player_index);
    void cubTrainingPath(int player_index);

    //additonal private funtions
    void displayTile(int player_index, int pos);
    void initializeTiles(int player_index);

    //functions used to check whether the player on the a tile, used in the display tile function as well
    //if the player position and path are both correct then the character is displayed on the resulting tile
    bool isPlayerOneOnTile(int player_index, int pos);
    bool isPlayerTwoOnTile(int player_index, int pos);

public:

    //constructors
    Board();
    Board(int player_count);

    //additional member functions used to make the board the player sees
    void displayTrack(int player_index);
    void initializeBoard();
    void displayBoard();

    //generates a random number between 1 and 6, used to determine how many turns the player will move
    int spinTheWheel();
    bool movePlayer(int playerMoved);
    int getBoardPosition(int player_index) const;

    //Prompts the player(s) to select an pre-configured character and assigns them to the array of player objects given along with the path they wish to take
    void displayPlayerSelection(player Players[]);
    void playerPathSelection(player Players[]);

    //If the player selects cub training or lands on a counseling tile the advisor menu will be displayed allowing players to assign a pre-configured advisor to their character
    void displayAdvisorMenu(int index, player playerSet[]);

    //the menu is what is used to navigate the game on each players turn and is the main source of interaction
    //2 of the 5 menu selections have additional options in them and 1 contains a special event pop up that occurs every 5 turns
    void displayMenu(int activePlayer);

    //at the end of the game use the print stats function in the player class to print the final stats of all players
    //these final stats are then written to an output file
    //once complete all leadership stats are converted to pride points and a winner is declared
    void displayEndGameScreen();
    void writeToEndStatsToFile();

    //functions used to validate if a string is a true integer and split a string into array slots
    int split(string input_string, char separator, string arr[], const int ARR_SIZE);
    bool validateInteger(string input);

    //getters and setters 
    player getPlayersArray(int index);
    string getTileType(int pathNumber, int playerPosition); //determines the tiles "name" based on the color
    void setPlayersArray(player Player[]);
    void setTileEvents(string tileType, int index, int playerPosition); //based on the tiles name the effects of each unique tiles are carried out on the player
};

#endif