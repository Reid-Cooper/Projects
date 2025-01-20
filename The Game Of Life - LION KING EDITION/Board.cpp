#include "Board.h"
#include "fstream"
#include "Tiles.hpp"
#include "player.hpp"
#include <string>
#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m"  /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define RESET "\033[0m"

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

//"global functions" used throughout the board class
bool Board :: validateInteger(string input){
bool check = true;
unsigned int i;

//checks if string length is 0
if (input.length() == 0){
    check = false;
    return 0;
}

//check to make sure the string isnt just a - sign as that isn't a negative number
if ((input[0] == '-' || input[0] == '.')&& input.length() == 1){
    check = false;
    return 0;
}

//checks if the first part of the string is not a number and not a - sign 
if ((input[0] < '0' && input [0] != '-') || (input[0] > '9' && input [0] != '-')){
    check = false;
    return 0;
}

if (input[0] == '-' && input[1] == '.'){
    check = false;
    return 0;
}

//if string passes all the tests above it enters the loop below
if((input[0] == '-' && input[1] >= '0' && input[1] <= '9' && input[1] != '.') || ((input[0] >= '0' && input[0] <= '9' && input[0] != '-') && input[1] == '.')){

//assigns a counter to make char c set to every part of the character in the string and see if it is a number
// '' are used because the comparisons are based on ASCII values
for (i = 1; i < input.length(); i++) {
        char c = input[i];

if ((c < '0' || c > '9') && c != '.'){
            check = false;
            break;}}
}
    return check;
}

int Board :: split(string input_string, char separator, string arr[], const int ARR_SIZE){

int sections = 1;
int size = 1;
int arrayPlacement = 0;
int startPosition = 0;
int lengthInBetween = 0;

    for(unsigned int i = 0; i < input_string.length(); i++){

        //if the string at any point is the seperator then up the potential size of the array
        if(input_string[i] == separator){

            size = size + 1;

            //if sections is still less than the size the array is allowed to be enter the loop
            if(sections < ARR_SIZE){

                sections = sections + 1;

                //the array at arrayPlacement is then set to the substring of the input string starting at an origonal position of 0
                //it then runs up to where the seperator was found minus the value of start position to get the area in between
                //the next start position is then set to i + 1 so as not to include the seperator in the "cout"
                arr[arrayPlacement] = input_string.substr(startPosition, i - startPosition);
                startPosition = i + 1;
                lengthInBetween = 0;

                //this for loop deals with assigning the length of which the substring for the last string in the array should be
                for(unsigned int j = i + 1; j < input_string.length(); j++){
                    
                    if(input_string[j] != separator){
                        lengthInBetween = lengthInBetween + 1;
                        }
                    else if(input_string[j] == separator){
                        break;
                    }
                }

                //the string in the last position of the array is filled by assigning it the substring of the newest start position and predetermined length
                arr[arrayPlacement + 1] = input_string.substr(startPosition, lengthInBetween);
                arrayPlacement = arrayPlacement + 1; 
            }
        }
    }

    if(input_string.length() == 0){
        sections = 0;
    }
    if(sections == 1){
        arr[0] = input_string;
    }
    if(size > ARR_SIZE){
        sections = -1;
    }

return sections;

}

//constructors
Board::Board()
{
    _player_count = 1;

    // Initialize player position
    _player_position[0] = 0;

    // Initialize tiles
    initializeBoard();
}

Board::Board(int player_count)
{
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    }
    else
    {
        _player_count = player_count;
    }

    // Initialize player position
    for (int i = 0; i < _player_count; i++)
    {
        _player_position[i] = 0;
    }

    // Initialize tiles

    initializeBoard();
}

//intialization of Board and Tiles objects along with unique path generation
void Board :: initializeBoard()
{
    // Seed random number generator in your main function once
    for (int i = 0; i < 2; i++)
    {
        initializeTiles(i);  // This ensures each lane has a unique tile distribution
    }
}

void Board :: initializeTiles(int player_index)
{
    if(player_index == 0){
        cubTrainingPath(player_index); //top path
    }

    if(player_index == 1){
        prideLandsPath(player_index); //lower path
    }
}

void Board :: displayTile(int player_index, int pos)
{
    // string space = "                                       ";
    string color = "";
    bool player1OnTile = isPlayerOneOnTile(player_index, pos);
    bool player2OnTile = isPlayerTwoOnTile(player_index, pos);

    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>

    // Determine color to display
    if (_tiles[player_index][pos].getTileColor() == 'R')
    {
        color = RED;
    }
    else if (_tiles[player_index][pos].getTileColor() == 'G')
    {
        color = GREEN;
    }
    else if (_tiles[player_index][pos].getTileColor() == 'B')
    {
        color = BLUE;
    }
    else if (_tiles[player_index][pos].getTileColor() == 'U')
    {
        color = PURPLE;
    }
    else if (_tiles[player_index][pos].getTileColor() == 'N')
    {
        color = BROWN;
    }
    else if (_tiles[player_index][pos].getTileColor() == 'P')
    {
        color = PINK;
    }
    else if (_tiles[player_index][pos].getTileColor() == 'O')
    {
        color = ORANGE;
    }
    else if (_tiles[player_index][pos].getTileColor() == 'Y')
    {
        color = GREY;
    }

//display the player symbols accordingly
    if (player1OnTile == true && player2OnTile == true){
        cout << color << "|" << "1&2" << "|" << RESET;
    }
    else if(player1OnTile == true){
        cout << color << "|" << "1" << "|" << RESET; 
    }
    else if(player2OnTile == true){
        cout << color << "|" << "2" << "|" << RESET;  
    }
    else{
        cout << color << "| |" << RESET;
    }
}

void Board :: displayTrack(int player_index)
{
    for (int i = 0; i < _BOARD_SIZE; i++){
        displayTile(player_index, i);
    }
    if(player_index == 0){
        cout << "         TRAINED CUB PATH" << endl;
    }
    else if(player_index == 1){
        cout << "   STRAIGHT TO PRIDE LANDS PATH" << endl;
    }
    else{cout << endl;}
}

void Board :: displayBoard()
{
    for (int i = 0; i < 2; i++)
    {
        displayTrack(i); 
        if (i == 0) {
            cout << endl;
            cout << endl;  // Add an extra line between the two lanes
        }
    }
}

void Board :: cubTrainingPath(int player_index){

Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE; //52
    srand(time(0));

    // Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.setTileColor('O');
        } 
        else if (i == 0) {
            // Set the first tile as Grey for "Start"
            temp.setTileColor('Y');
        } 
        else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
            temp.setTileColor('G');
            green_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
            int color_choice = rand() % 100;

            if(color_choice >= 0 && color_choice < 15){  //15% chance to get an advisor tile (whole game)
                color_choice = 1;
            }

            if(color_choice >= 15 && color_choice < 35){ //20% chance to get a Hyenas tile (whole game)
                color_choice = 2;
            }

            if(color_choice >= 35 && color_choice < 55){ //20% chance to get a Graveyard tile (whole game)
                color_choice = 3;
            }

            if(total_tiles - i >= 26){ //25% chance at Challenge tile in early game
                if(color_choice >= 55 && color_choice < 80){
                    color_choice = 4;
                }
            }
            else if(total_tiles - i < 26){ //10% chance at Challenge tile in late game
                if(color_choice >= 50 && color_choice < 60){
                    color_choice = 4;
                }
            }

            if(total_tiles - i >= 26){ //20% chance at Oasis tile in early game
                if(color_choice >= 80 && color_choice < 100){
                    color_choice = 0;
                }
            }
            else if(total_tiles - i < 26){ //15% chance at Oasis tile in late game
                if(color_choice >= 60 && color_choice < 100){
                    color_choice = 0;
                }
            }

            switch (color_choice)
            {
                case 0:
                    temp.setTileColor('B'); // Blue //Oasis Tile
                    //temp.oasisTile();
                    break;
                case 1:
                    temp.setTileColor('P'); // Pink //Counseling Tile
                    //temp.counselingTile();
                    break;
                case 2:
                    temp.setTileColor('N'); // Brown //Hyenas Tile
                    //temp.hyenasTile();
                    break;
                case 3:
                    temp.setTileColor('R'); // Red //Graveyard Tile
                    //temp.graveyardTile();
                    break;
                case 4:
                    temp.setTileColor('U'); // Purple //Challenge (riddle tile)
                    //temp.challengeTile();
                    break;
            }
        }

        // Assign the tile to the board for the specified lane
        _tiles[player_index][i] = temp;
    }
}

void Board :: prideLandsPath(int player_index){

Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;
    srand(time(0));

    // Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.setTileColor('O');
        } 
        else if (i == 0) {
            // Set the first tile as Grey for "Start"
            temp.setTileColor('Y');
        } 
        else if (green_count < 25 && (rand() % (total_tiles - i) < 25 - green_count)) {
            temp.setTileColor('G');
            green_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
            int color_choice = rand() % 100;
            
            if(color_choice >= 0 && color_choice < 20){ //20% chance to get an advisor tile (whole game)
                color_choice = 1;
            }

            if(color_choice >= 20 && color_choice < 38){ //18% chance at Challenge tile (whole game)
                    color_choice = 4;
            }

            if(color_choice >= 38 && color_choice < 63){ //25% chance of Hyenas tile (whole game)
                color_choice = 2;
            }

            if(color_choice >= 63 && color_choice < 83){ //20% chance of graveyard tile (whole game)
                color_choice = 3;
            }

            if(color_choice >= 83 && color_choice < 100){ //17% chance of oasis (whole game)
                color_choice = 0;
            } 


            switch (color_choice)
            {
                case 0:
                    temp.setTileColor('B'); // Blue
                    break;
                case 1:
                    temp.setTileColor('P'); // Pink
                    break;
                case 2:
                    temp.setTileColor('N'); // Brown
                    break;
                case 3:
                    temp.setTileColor('R'); // Red
                    break;
                case 4:
                    temp.setTileColor('U'); // Purple
                    break;
            }
        }
        // Assign the tile to the board for the specified lane
        _tiles[player_index][i] = temp;
    }

}

//moving the player
bool Board :: movePlayer(int playerMoved)
{
    // Increment player position
    playersArray[playerMoved].setPlayerPosition(playersArray[playerMoved].getPlayerPosition() + 1);
    if (playersArray[playerMoved].getPlayerPosition() >= _BOARD_SIZE - 1)
    {
        //Player reached last tile
        //Keeps player on last tile and doesnt allow the to go over
        playersArray[playerMoved].setPlayerPosition(51);
        return true;
    }
    return false;
}

bool Board :: isPlayerOneOnTile(int player_index, int pos)
{
    if (playersArray[0].getPlayerPosition() == pos && player_index == playersArray[0].getPathTaken()){
        return true;
    }
    return false;

}

bool Board :: isPlayerTwoOnTile(int player_index, int pos)
{
    if (playersArray[1].getPlayerPosition() == pos && player_index == playersArray[1].getPathTaken()){
        return true;
    }
    return false;

}

int Board :: spinTheWheel(){

int moveNumber;
moveNumber = rand() % 6;
moveNumber = moveNumber + 1;
//add additional options based on character decisions or circumstances

return moveNumber;
}

int Board :: getBoardPosition(int player_index) const
{
    if (player_index >= 0 && player_index <= _player_count)
    {
        return _player_position[player_index];
    }
    return -1;
}

//defining what is in the chaacters array for use throughout the game
void Board :: setPlayersArray(player Players[]){

for(int i = 0; i < _MAX_PLAYERS; i++){
    playersArray[i] = Players[i];
}

}

player Board :: getPlayersArray(int index){

    if(index < 0 || index > 1){
        cout << "Error invalid index" << endl;
        return playersArray[0];
    }
return playersArray[index];
}

//all the events that occur on each possible tile
void Board :: setTileEvents(string tileType, int index, int playerPosition){

playersArray[index].addNumberOfTurnsTaken(1);
playersArray[index].checkIfAnyStatsAreZero();

if(tileType == "Start"){
    cout << endl;
    cout << "You're on the start tile!" << endl;
    playersArray[index].setPlayersTurn(false); 
    return;
}

if(tileType == "Grasslands"){
    cout << endl;
    cout << "You landed on a GRASSLANDS tile!" << endl;

    srand(time(0));
    int chanceAtRandomEvent = (rand() % 100) + 1;

    if(chanceAtRandomEvent > 0 && chanceAtRandomEvent <= 50){

        int desiredLine = (rand() % 50) + 1;
        int lineCounter = 0;
        string line;
        const int ARRAYSIZE = 4;
        string storageArray[ARRAYSIZE];
        ifstream randomEvents;
        randomEvents.open("random_events.txt");

        if(randomEvents.fail()){
            cout << "Random events file failed to open please check file path." << endl;
        }
        else{
            while(getline(randomEvents, line) && lineCounter < desiredLine){

                split(line, '|', storageArray, ARRAYSIZE);
                lineCounter++;
                }
            }
        randomEvents.close();

        cout << storageArray[0] << endl;

        if(stoi(storageArray[1]) == 0){

            if(playersArray[index].getAdvisor() == stoi(storageArray[2])){
            cout << "Thanks to your advisors ability & help you were able to adequately handle the situation and avoid loosing any pride points!" << endl;
            }
            else{
            cout << "With no help to handle the situation you pride points take a hit. Player " << index + 1 << " looses " << storageArray[3] << " pride points" << endl;
            cout << "Advisor needed to deal with this event: " << storageArray[2] << "." << endl;
            playersArray[index].setPridePoints(playersArray[index].getPridePoints() + stoi(storageArray[3]));
            }
        }

        if(stoi(storageArray[1]) == 1){
        
        cout << "This good fortune has boosted the your spirits and pride points! Player " << index + 1 << " gains " << storageArray[3] << " pride points" << endl;
        playersArray[index].setPridePoints(playersArray[index].getPridePoints() + stoi(storageArray[3]));
        }
    }

    if(chanceAtRandomEvent > 50 && chanceAtRandomEvent <= 100){
        cout << "The calm wind blows across the savannah, nothing occurs this turn." << endl;
    }

    playersArray[index].setpoweredUpPlayer(false);
    playersArray[index].setPlayersTurn(false);
    return;
}

if(tileType == "Oasis"){
    cout << endl;
    cout << "You landed on an OASIS tile!" << endl;
    cout << "It's time to rests and recharge before moving on." << endl;
    cout << "Player " << index + 1 << " (" << playersArray[index].getName() << ")" << " gains 200 strength, stamina and wisdom; along with an extra turn & advisor power-up!" << endl;
    playersArray[index].setStrength(playersArray[index].getStrength() + 200);
    playersArray[index].setStamina(playersArray[index].getStamina() + 200);
    playersArray[index].setWisdom(playersArray[index].getWisdom() + 200);
    playersArray[index].addAdvisorPowerUps(1);
    playersArray[index].setpoweredUpPlayer(false);
    playersArray[index].setPlayersTurn(true);
    return;
}

if(tileType == "Counseling"){
    cout << endl;
    cout << "You landed on a COUNSELING tile!" << endl;

    if(playersArray[index].getAdvisor() != 0){

        cout << "Right now you change your advisor if you wish to do so. Would you like to change your advisor?" << endl;
        cout << "Enter (1) to keep your current advisor." << endl;
        cout << "Enter (2) to select a new advisor from the advisor menu." << endl;

        string proceedSelection;

        cin >> proceedSelection;
            if(validateInteger(proceedSelection) == false){
                proceedSelection = "3";
            }

            while(stoi(proceedSelection) > 2 || stoi(proceedSelection) < 1){
                cout << "Please input a valid option selection (1 or 2)" << endl;
                cin >> proceedSelection;
                if(validateInteger(proceedSelection) == false){
                proceedSelection = "3";
                }
            }

        int endSelection = stoi(proceedSelection);
        switch(endSelection){

            case 1: 
                cout << endl;
                break;

            case 2:
                displayAdvisorMenu(index, playersArray);
                cout << endl;
                break;         
        }
    }
    else if(playersArray[index].getAdvisor() == 0){
        cout << "Player " << index + 1 << " (" << playersArray[index].getName() << ") now has the opportunity to select there advisor." << endl;
        displayAdvisorMenu(index, playersArray);
    }

    cout << "Player " << index + 1 << " (" << playersArray[index].getName() << ") talks to there advisor gaining insight on the path ahead." << endl;
    cout << "With new found confidence they gain 300 strength, 300 stamina and 400 wisdom along with an advisor power-up!" << endl;

    playersArray[index].setStrength(playersArray[index].getStrength() + 300);
    playersArray[index].setStamina(playersArray[index].getStamina() + 300);
    playersArray[index].setWisdom(playersArray[index].getWisdom() + 400);
    playersArray[index].addAdvisorPowerUps(1);
    playersArray[index].setpoweredUpPlayer(false);
    playersArray[index].setPlayersTurn(false);
    //advisor implementation
    return;
}

if(tileType == "Hyenas"){

    cout << endl;
    cout << "You landed on a HYENAS tile" << endl;

    if(playersArray[index].getPoweredUpPlayer() == true){

    cout << "Your advisors power-up came in handy, easily fending off the beasts." << endl;
    cout << "Player " << index + 1 << " gains 200 wisdom and 100 stamina!" << endl;
    playersArray[index].setStamina(playersArray[index].getStamina() + 100);
    playersArray[index].setWisdom(playersArray[index].getWisdom() + 200);
    playersArray[index].setpoweredUpPlayer(false);
    playersArray[index].setPlayersTurn(false);

    }
    else{
    cout << "Scavangers of the desert have found you and the battle takes a toll." << endl;
    cout << "Player " << index + 1 << " (" << playersArray[index].getName() << ")" << " looses 300 stamina and is returned to the board tile they were last on." << endl;
    
    //player looses 300 stamina
    playersArray[index].setStamina(playersArray[index].getStamina() - 300);

    //move back to origonal spot implementation
    if(playerPosition != 0){
        playersArray[index].setPlayerPosition(playerPosition);
    }
    else{playersArray[index].makePlayerPositionZero();}
    playersArray[index].setPlayersTurn(false);
    }
    return;
}

if(tileType == "Graveyard"){
    cout << endl;
    cout << "You landed on a GRAVEYARD tile!" << endl;

    //if your advisor power-up is active then you don't recieve negative effects
    if(playersArray[index].getPoweredUpPlayer() == true){
        cout << "The graveyard in no match for your lion with their advisors power! They comfortably make their way through the area." << endl;
        cout << "Player " << index + 1 << " gains 200 strength as well as an extra turn." << endl;
        playersArray[index].setpoweredUpPlayer(false);
        playersArray[index].setStrength(playersArray[index].getStrength() + 200);
        playersArray[index].setPlayersTurn(true);
    }
    else{
    cout << "Player " << index + 1 << " (" << playersArray[index].getName() << ")" << " has found themselves in a graveyard!" << endl;
    cout << "Player " << index + 1 << " looses 100 strength, 100 stamina and 100 wisdom. They also move back 10 spaces on the board." << endl;

    //player looses 100 strength, stamina and wisdom
    playersArray[index].setStrength(playersArray[index].getStrength() - 100);
    playersArray[index].setStamina(playersArray[index].getStamina() - 100);
    playersArray[index].setWisdom(playersArray[index].getWisdom() - 100);

    //move back 10 spaces implementation
    if(playerPosition > 10){
        playersArray[index].addPlayerPosition(-10);
        }
        else{playersArray[index].makePlayerPositionZero();}

    playersArray[index].setPlayersTurn(false);
    }
    return;
}

if(tileType == "Challenge"){
    cout << endl;
    cout << "You landed on a CHALLENGE tile!" << endl;

    //riddle implementation
    //if riddle is guessed correctly pride points goes up 500
    //else nothing happens and you move on

    string line;
    string answerToRiddle;
    string answerGuess;
    const int ARR_SIZE = 2;
    string storageArray[ARR_SIZE];

    srand(time(0));
    int desiredLine = (rand() % 27) + 1;
    int counter = 0;

    ifstream riddlesFile;
    riddlesFile.open("riddles.txt");

    if(riddlesFile.is_open() == false){
        cout << "Riddles file did not open" << endl;
    }
    else{
        
    while(getline(riddlesFile, line) && counter < desiredLine){

        split(line, '|', storageArray, 2);
        counter ++;

        }
    }

    riddlesFile.close();

    answerToRiddle = storageArray[1];

    cout << storageArray[0] << endl;
    //cout << "The answer is " << storageArray[1] << endl;

    cin.clear();
    cin.ignore();
    getline(cin, answerGuess);

    if(answerGuess == storageArray[1].substr(0, storageArray[1].length() - 1)){
        cout << "Congrats, that is the correct answer! Player " << index + 1 << " will now be rewarded with 500 pride points for their wits." << endl;
        playersArray[index].setPridePoints(playersArray[index].getPridePoints() + 500);
    }
    else {cout << "Good try however that is not the answer better luck next time!" << endl;}

    playersArray[index].setpoweredUpPlayer(false);
    playersArray[index].setPlayersTurn(false);
}

if(tileType == "Pride Rock (end)"){
    cout << endl;
    cout << "Player " << index + 1 << " has reached the PRIDE ROCK! (end of the board)" << endl;
    cout << "All of your leadership traits will now be converted to pride points. Please wait for all players to finish the game to see who wins!" << endl;

    //converts every 100 strength stamina and wisdom to 1000 pride points
    //playersArray[index].convertStatsToPridePoints(playersArray[index].getStrength(), playersArray[index].getStamina(), playersArray[index].getWisdom());
    playersArray[index].setpoweredUpPlayer(false);
    playersArray[index].setPlayersTurn(false);
}

return;
}

string Board :: getTileType(int player, int playerPosition){

string tileType = "";

//looks at the tiles in the row that player chose, from there the position is gound along with the tile color
if(_tiles[playersArray[player].getPathTaken()][playerPosition].getTileColor() == 'O'){
tileType = "Pride Rock (end)";
return tileType;
}

if(_tiles[playersArray[player].getPathTaken()][playerPosition].getTileColor() == 'Y'){
tileType = "Start";
return tileType;
}

if(_tiles[playersArray[player].getPathTaken()][playerPosition].getTileColor() == 'G'){
tileType = "Grasslands";
return tileType;
}

if(_tiles[playersArray[player].getPathTaken()][playerPosition].getTileColor() == 'B'){
tileType = "Oasis";
return tileType;
}

if(_tiles[playersArray[player].getPathTaken()][playerPosition].getTileColor() == 'P'){
tileType = "Counseling";
return tileType;
}

if(_tiles[playersArray[player].getPathTaken()][playerPosition].getTileColor() == 'N'){
tileType = "Hyenas";
return tileType;
}

if(_tiles[playersArray[player].getPathTaken()][playerPosition].getTileColor() == 'R'){
tileType = "Graveyard";
return tileType;
}

if(_tiles[playersArray[player].getPathTaken()][playerPosition].getTileColor() == 'U'){
tileType = "Challenge";
return tileType;
}

return tileType;
}

//display functions that prompt user interaction
void Board :: displayPlayerSelection(player Players[]){

cout << endl;
cout << "WELCOME TO THE GAME OF LIFE, LION KING EDITION!" << endl;
cout << endl;
cout << "The goal of this game is to reach the pride rock, the last tile on the board." << endl;
cout << "This a two player game so grab a friend! Each of you will take turns moving along the board making decisions for you character based on what experiences each tile presents." << endl;
cout << "The winner of the game is determined by who has the most pride points at the end of the game." << endl;
cout << "While pride points are their own stat at the end of the game all leadership stats will be converted to pride points as well!" << endl;
cout << endl;
cout << "Now it's time to select everyones character! please see the options belwow." << endl;

//each player selects which lion preset they want to start with
int playerIndexAssignment = 0;
while(playerIndexAssignment < 2){

cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << endl;

player tempPlayerHolder("Name", 1, 1, 1);
string selectionValue;

if(playerIndexAssignment == 0){
    cout << "Player 1 please select a character (enter number): " << endl;
}
else{
    cout << "Player 2 please select a character (enter number): " << endl;
}

cout << "#  Name  | Age | Strength | Stamina | Wisdom | Pride-Points" << endl;
cout << "1. Apollo|  5  |    500   |   520   |  1000  |    20000" << endl;
cout << "2. Mane  |  8  |    900   |   600   |  630   |    20000" << endl;
cout << "3. Elsa  |  12 |    900   |   700   |  500   |    20000" << endl;
cout << "4. Zuri  |  7  |    600   |   500   |  900   |    20000" << endl;
cout << "5. Roary |  18 |    1000  |   510   |  500   |    20000" << endl;

cin >> selectionValue;
if(validateInteger(selectionValue) == false){
    selectionValue = "6";
}

while(stoi(selectionValue) > 5 || stoi(selectionValue) < 1){
    cout << "Please enter a valid character number." << endl;
    cin >> selectionValue;
    if(validateInteger(selectionValue) == false){
    selectionValue = "6";
}
}

int finalValue = stoi(selectionValue);

switch(finalValue){

case 1: 
        tempPlayerHolder.setName("Apollo");
        tempPlayerHolder.setAge(5);
        tempPlayerHolder.setStrength(500);
        tempPlayerHolder.setStamina(520);
        tempPlayerHolder.setWisdom(1000);
        tempPlayerHolder.setPridePoints(20000);
        Players[playerIndexAssignment] = tempPlayerHolder;
        cout << "Apollo has been successfully selected for Player " << playerIndexAssignment + 1 << endl; 
    break;

case 2: 
        tempPlayerHolder.setName("Mane");
        tempPlayerHolder.setAge(8);
        tempPlayerHolder.setStrength(900);
        tempPlayerHolder.setStamina(600);
        tempPlayerHolder.setWisdom(630);
        tempPlayerHolder.setPridePoints(20000);
        Players[playerIndexAssignment] = tempPlayerHolder;
        cout << "Mane has been successfully selected for Player " << playerIndexAssignment + 1 << endl; 
    break;

case 3:
        tempPlayerHolder.setName("Elsa");
        tempPlayerHolder.setAge(12);
        tempPlayerHolder.setStrength(900);
        tempPlayerHolder.setStamina(700);
        tempPlayerHolder.setWisdom(500);
        tempPlayerHolder.setPridePoints(20000);
        Players[playerIndexAssignment] = tempPlayerHolder;
        cout << "Elsa has been successfully selected for Player " << playerIndexAssignment + 1 << endl; 
    break;

case 4:
        tempPlayerHolder.setName("Zuri");
        tempPlayerHolder.setAge(7);
        tempPlayerHolder.setStrength(600);
        tempPlayerHolder.setStamina(500);
        tempPlayerHolder.setWisdom(900);
        tempPlayerHolder.setPridePoints(20000);
        Players[playerIndexAssignment] = tempPlayerHolder;
        cout << "Zuri has been successfully selected for Player " << playerIndexAssignment + 1 << endl; 
    break;

case 5: 
        tempPlayerHolder.setName("Roary");
        tempPlayerHolder.setAge(18);
        tempPlayerHolder.setStrength(1000);
        tempPlayerHolder.setStamina(510);
        tempPlayerHolder.setWisdom(500);
        tempPlayerHolder.setPridePoints(20000);
        Players[playerIndexAssignment] = tempPlayerHolder;
        cout << "Roary has been successfully selected for Player " << playerIndexAssignment + 1 << endl; 
    break;
        }

playerIndexAssignment++;
cout << endl;
    }
cout << endl;
}

void Board :: playerPathSelection(player Players[]){

cout << "Now it is time to select everyones path, which will dramatically effect how each journey unfolds." << endl;
cout << "You can choose to either train, gaining knowledge and insight on the path ahead (less negative tiles) or get straight into the action will which comes with its own risks and rewards!" << endl;
cout << "Are you a calculated player who wants to train their lion loosing some pride points? Or are you willing to take a risker path gaining pride points in the process?" << endl;
cout << endl;

//each player selects the path they want to take
int playerIndexAssignment = 0;
while(playerIndexAssignment < 2){
string pathSelection;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "PLAYER " << playerIndexAssignment + 1 << " WHAT WOULD YOU LIKE TO DO:" << endl;
        cout << endl;
        cout << "(1) Go to cub training, gaining 500 strength, 500 stamina, and 500 wisdom but loosing 5000 pride points?" << endl;
        cout << "    You will select an advisor to start with along with 1 advisor power-up." << endl;
        cout << endl;
        cout << "(2) Go straight to the pride lands, loosing 250 strength, 250 stamina, and 300 wisdom but gaining 5000 pride points?" << endl;
        cout << "    You will not select an advisor to start with however you will be given 3 adivor power-ups to use once you find one." << endl;

    cin >> pathSelection;
    if(validateInteger(pathSelection) == false){
        pathSelection = "3";
    }
    while(stoi(pathSelection) > 2 || stoi(pathSelection) < 1){
        cout << "Please enter a valid path number, (1) for pride lands or (2) for cub training." << endl;
        cin >> pathSelection;
        if(validateInteger(pathSelection) == false){
        pathSelection = "3";
        }
    }

    int finalPathSelection = stoi(pathSelection);
    string advisorSelection;

    switch(finalPathSelection){

//input of 2 will send the player to the pride lands and adjust stats accordingly
    case 2: 
        Players[playerIndexAssignment].setPathSelected(1);
        Players[playerIndexAssignment].toPrideLands();
        Players[playerIndexAssignment].setAdvisorPowerUps(3);
        cout << "Your headed to the pride lands!" << endl;
        break;

//input of 1 will send the player to training adjusting stats accordingly, they will also be prompted to select an advisor
    case 1: 
        Players[playerIndexAssignment].setPathSelected(0);
        Players[playerIndexAssignment].trainCub(500, 500, 1000);
        displayAdvisorMenu(playerIndexAssignment, Players);
        Players[playerIndexAssignment].setAdvisorPowerUps(1);
        cout << "You're headed to cub training!" << endl;
        break;
        }
        playerIndexAssignment++;
        cout << endl;
    }

cout << "Now it is time to play the game! Player 1 will now be prompted with the game menu used to move there play, check character stats, as well as their advisor if applicable." << endl;
cout << "To visully see the board itself and what is on the path ahead please select number 3 in the menu!" << endl;

}

void Board :: displayAdvisorMenu(int index, player playerSet[]){

cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
string advisorSelection;
                cout << endl;
                cout << "Please select an advisor to accompany you along you journey. Each of them offer unique special abilities!" << endl;
                cout << "# | ADVISOR NAME | ABILITY" << endl;
                cout << "1 |   Rafiki     | Invisibility" << endl; 
                cout << "2 |   Nala       | Night Vision" << endl; 
                cout << "3 |   Sarabi     | Energy Manipulation" << endl; 
                cout << "4 |   Zazu       | Weather Control" << endl; 
                cout << "5 |   Sarafina   | Super Speed" << endl;

                cin >> advisorSelection;
            if(validateInteger(advisorSelection) == false){
                advisorSelection = "6";
            }

            while(stoi(advisorSelection) > 5 || stoi(advisorSelection) < 1){
                cout << "Please input a valid advisor selection (1-5)" << endl;
                cin >> advisorSelection;
                if(validateInteger(advisorSelection) == false){
                advisorSelection = "6";
                }
            }

            int finalAdvisor = stoi(advisorSelection);

            //based on the input the player will select which advisor they want to have
            switch(finalAdvisor){

            case 1:
                playerSet[index].setAdvisor(1);
                cout << "Advisor Rafiki selected!" << endl;
                break;

            case 2:
                playerSet[index].setAdvisor(2);
                cout << "Advisor Nala selected!" << endl;
                break;

            case 3:
                playerSet[index].setAdvisor(3);
                cout << "Advisor Sarabi selected!" << endl;
                break;

            case 4:
                playerSet[index].setAdvisor(4);
                cout << "Advisor Zazu selected!" << endl;
                break;

            case 5:
                playerSet[index].setAdvisor(5);
                cout << "Advisor Sarafina selected!" << endl;
                break;
            }

            cout << "This is advisor number " << playerSet[index].getAdvisor() << endl;
}

void Board :: displayMenu(int activePlayer){

string menuSelection;
string advisorMenuSelection;
string conversionMenuSelection;
int finalConversionMenuSelection;
int finalAdvisorMenuSelection;
int currentPosition = playersArray[activePlayer].getPlayerPosition();
int advisor = playersArray[activePlayer].getAdvisor();

int characterStrength = playersArray[activePlayer].getStrength();
int characterStamina = playersArray[activePlayer].getStamina();
int characterWisdom = playersArray[activePlayer].getWisdom();

do{
cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << endl;
cout << "PLAYER " << activePlayer + 1 << "'S TURN" << endl; 
cout << "MAIN MENU: Select an option to continue (enter number)" << endl;
cout << "1. Check Player Progress" << endl;
cout << "2. Review Character" << endl;

if(playersArray[activePlayer].getNumberOfTurnsTaken() % 5 == 0 && playersArray[activePlayer].getNumberOfTurnsTaken() != 0 ){
    playersArray[activePlayer].addNumberOfTurnsTaken(1);
    playersArray[activePlayer].setLionBirthday(true);
    playersArray[activePlayer].setAge(playersArray[activePlayer].getAge() + 1);
    if(playersArray[activePlayer].getLionBirthday() == true){
        cout << "- BIRTHDAY CELEBRATION AVAILABLE!" << endl;
        }
    }
else{playersArray[activePlayer].setLionBirthday(false);}

cout << "3. Check Position" << endl;
cout << "4. Review Your Advisor" << endl;
cout << "5. Move Forward (END TURN)" << endl;

cin >> menuSelection;
cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

if(validateInteger(menuSelection) == false){
    menuSelection = "6";
}

while(stoi(menuSelection) > 5 || stoi(menuSelection) < 1){
cout << "Please enter a valid selection" << endl;
cin >> menuSelection;

    if(validateInteger(menuSelection) == false){
        menuSelection = "6";
    }
}

int finalSelection = stoi(menuSelection);
switch(finalSelection){

    case 1:
        cout << endl;
        cout << "PLAYER PROGRESS:" << endl;
        cout << "Player " << activePlayer + 1 << "'s Strength: " << playersArray[activePlayer].getStrength() << endl;
        cout << "Player " << activePlayer + 1 << "'s Stamina: " << playersArray[activePlayer].getStamina() << endl;;
        cout << "Player " << activePlayer + 1 << "'s Wisdom: " << playersArray[activePlayer].getWisdom() << endl;
        cout << "Player " << activePlayer + 1 << "'s Pride Points: " << playersArray[activePlayer].getPridePoints() << endl;
        cout << endl;

        if(playersArray[activePlayer].getUsedConversion() == false){
            cout << "Would you like to convert any of your pride points to leaderships stats at rate of 1000 pride points per 100 of one leadership stat?" << endl;
            cout << "Please note that if you any of your leadership stats fall to zero (0) and you take a turn your character will loose 5000 pride points in exchange for 100 points of the needed stat. ENTER:" << endl;
            cout << endl;
            cout << "(8) to go back to the menu." << endl;
            cout << "(9) to convert 1000 pride points into 100 points of your lowest leadership stat. Can only do this once per turn." << endl;

            cin >> conversionMenuSelection;
            cout << endl;
            cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;


            if(validateInteger(conversionMenuSelection) == false){
                menuSelection = "5";
                }

            while(stoi(conversionMenuSelection) > 9 || stoi(conversionMenuSelection) < 8){
                cout << "Please enter a valid selection" << endl;
                cin >> conversionMenuSelection;

                if(validateInteger(conversionMenuSelection) == false){
                    conversionMenuSelection = "10";
                }
            }

            finalConversionMenuSelection = stoi(conversionMenuSelection);

            switch(finalConversionMenuSelection){

            case 8:
            break;

            case 9:
            if(characterStrength <= characterStamina && characterStrength <= characterWisdom){
                playersArray[activePlayer].setStrength(playersArray[activePlayer].getStrength() + 100);
                playersArray[activePlayer].addPridePoints(-1000);
                cout << "Exchange successful! You have gained 100 Strength!" << endl;
                playersArray[activePlayer].setUsedConversion(true);
            }
            else if(characterStamina <= characterStrength && characterStamina <= characterWisdom){
                playersArray[activePlayer].setStamina(playersArray[activePlayer].getStamina() + 100);
                playersArray[activePlayer].addPridePoints(-1000);
                cout << "Exchange successful! You have gained 100 Stamina!" << endl;
                playersArray[activePlayer].setUsedConversion(true);
            }
            else if(characterWisdom <= characterStrength && characterWisdom <= characterStamina){
                playersArray[activePlayer].setWisdom(playersArray[activePlayer].getWisdom() + 100);
                playersArray[activePlayer].addPridePoints(-1000);
                cout << "Exchange successful! You have gained 100 Wisdom!" << endl;
                playersArray[activePlayer].setUsedConversion(true);
            }
            cout << endl;
            }
            break;
            }else{cout << "You have already used your stat conversion ability for this turn." << endl;}

        cout << endl;
        break;
    
    case 2: 
        cout << endl;
        cout << "CHARACTER OVERVIEW:" << endl;
        cout << "Player " << activePlayer + 1 << "'s Name: " << playersArray[activePlayer].getName() << endl;
        cout << "Player " << activePlayer + 1 << "'s Age: " << playersArray[activePlayer].getAge() << endl;
        cout << endl;
        if(playersArray[activePlayer].getLionBirthday() == true){
            cout << "Enough time has passed that your character is turning one year older!" << endl;
            cout << "Because you have taken the time to recognize this event, your character reflects and their stats change" << endl;
            
            if(playersArray[activePlayer].getAge() > 10){
                cout << "Do to your characters older age they gain 300 wisdom but loose 100 stamina." << endl;
                playersArray[activePlayer].setWisdom(playersArray[activePlayer].getWisdom() + 300);
                playersArray[activePlayer].setStamina(playersArray[activePlayer].getStamina() - 100);
                playersArray[activePlayer].setLionBirthday(false);
            }
            else{cout << "Your character is still young and spry they gain 100 strength and 50 stamina" << endl;
                playersArray[activePlayer].setStrength(playersArray[activePlayer].getStrength() + 100);
                playersArray[activePlayer].setStamina(playersArray[activePlayer].getStamina() + 50);
                playersArray[activePlayer].setLionBirthday(false);
            }
        }
        break;
    
    case 3:
        cout << endl;
        cout << "BOARD VIEW: " << endl;
        cout << endl;
        displayBoard();
        cout << endl;
        cout << "YOUR EXACT POSITION IS " << playersArray[activePlayer].getPathTaken() + 1 << " ROW & THE " << playersArray[activePlayer].getPlayerPosition() + 1 << " SQUARE" << endl;
        cout << endl;
        break;
    
    case 4:
        cout << endl;
        cout << "ADVISOR INFORMATION:" << endl;

        cout << "You have advisor number: " << playersArray[activePlayer].getAdvisor() << endl;

        if(advisor == 0){
            cout << "You do not currently have an advisor" << endl; 
        }
        else if(advisor == 1){
            cout << "Your advisor is: Rafiki (invisibility)" << endl;
        }
        else if(advisor == 2){
            cout << "Your advisor is: Nala (night vision)" << endl;
        }
        else if(advisor == 3){
            cout << "Your advisor is: Sarabi (energy manipulation)" << endl;
        }
        else if(advisor == 4){
            cout << "Your advisor is: Zazu (weather control)" << endl;
        }
        else if(advisor == 5){
            cout << "Your advisor is: Sarafina (super speed)" << endl;
        }
        cout << "NUMBER OF ADVISOR POWER-UPS: " << playersArray[activePlayer].getAdvisorPowerUps() << endl;
        cout << endl;

        if(playersArray[activePlayer].getPoweredUpPlayer() == true){
            cout << "An advisor power up is currently active." << endl;
        }
        
        else if(playersArray[activePlayer].getAdvisor() != 0 && playersArray[activePlayer].getAdvisorPowerUps() != 0){
            cout << "Advisor power-ups allow you be uneffected by the negative events of HYENA & GRAVEYARD tiles!" << endl; 
            cout << "They are a one time use and will only be active for the turn they're used on so don't waste them. ENTER:" << endl;
            cout << "(8) to go back to the main menu." << endl;
            cout << "(9) if you would like to use an advisor power-up." << endl;
            cin >> advisorMenuSelection;

            if(validateInteger(advisorMenuSelection) == false){
                advisorMenuSelection = "5";
            }

            while(stoi(advisorMenuSelection) > 9 || stoi(advisorMenuSelection) < 8){
                cout << "Please enter a valid integer. (8 or 9)" << endl;
                cin >> advisorMenuSelection;
                if(validateInteger(advisorMenuSelection) == false){
                    advisorMenuSelection = "5";
                }    
            }

            finalAdvisorMenuSelection = stoi(advisorMenuSelection);

            switch(finalAdvisorMenuSelection){
                case 8:
                break;
                case 9: 
                cout << endl;
                cout << "Advisor Power-Ups has been activated! Considered yourself safe when you decide to move!" << endl;
                playersArray[activePlayer].addAdvisorPowerUps(-1);
                playersArray[activePlayer].setpoweredUpPlayer(true);
                break;
                }
            }

        else if(playersArray[activePlayer].getAdvisor() == 0){
            cout << "You don't have an advisor to use power-ups, find one on counseling tiles!" << endl;
        }

        else if(playersArray[activePlayer].getAdvisorPowerUps() == 0){
            cout << "You currently don't have any advisor power-ups, find them in OASIS or COUNSELING tiles and use them here." << endl;
            }
        cout << endl;
        break;

    case 5: 
        cout << endl;
        int spacesMoved = spinTheWheel();
        cout << "After spinning the virtual wheel Player " << activePlayer + 1 << " will move " << spacesMoved << " spaces!" << endl;

        for(int i = 0; i < spacesMoved; i++){
        movePlayer(activePlayer);
        }

        playersArray[activePlayer].setUsedConversion(false);
        setTileEvents(getTileType(activePlayer, playersArray[activePlayer].getPlayerPosition()), activePlayer, currentPosition);
        cout << endl;
        menuSelection = "quit";
        break;
    }

}while(menuSelection != "quit");
}

void Board :: displayEndGameScreen(){

//show the final board and the stats of both players
cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
cout << endl;
cout << "FINAL BOARD AND STATS:" << endl;

cout << endl;
displayBoard();
cout << endl;

cout << "Player 1's FINAL STATS:" << endl;
getPlayersArray(0).printStats();
cout << endl;
cout << "Player 2's FINAL STATS:" << endl;
getPlayersArray(1).printStats();
cout << endl;

//converting all leadership stats to pride points
cout << "Every 100 points of each leadership stat each player has will now be converted to 1000 pride points." << endl;

playersArray[0].convertStatsToPridePoints(playersArray[0].getStrength(), playersArray[0].getStamina(), playersArray[0].getWisdom());
playersArray[1].convertStatsToPridePoints(playersArray[1].getStrength(), playersArray[1].getStamina(), playersArray[1].getWisdom());

cout << "After converting all leadership stats into pride points here are the final results!" << endl;
cout << "Player 1 has a grand total of " << playersArray[0].getPridePoints() << " pride points." << endl;
cout << "Player 2 has a grand total of " << playersArray[1].getPridePoints() << " pride points." << endl;

cout << endl;
if(playersArray[0].getPridePoints() > playersArray[1].getPridePoints()){
    cout << "THE WINNER IS PLAYER 1! BY A DIFFERENCE OF " << playersArray[0].getPridePoints() - playersArray[1].getPridePoints() << " PRIDE POINTS. CONGRATS!" << endl;
}
else if(playersArray[0].getPridePoints() < playersArray[1].getPridePoints()){
    cout << "THE WINNER IS PLAYER 2! BY A DIFFERENCE OF " << playersArray[1].getPridePoints() - playersArray[0].getPridePoints() << " PRIDE POINTS. CONGRATS!" << endl;
}
cout << endl;

cout << "This concludes the game." << endl;
cout << "Thank you for playing: THE GAME OF LIFE, LION KING EDITION!" << endl;
cout << endl;
}

//write end stat of each player to an output file
void Board :: writeToEndStatsToFile(){

ofstream endOfGameFile;
endOfGameFile.open("final_stats.txt");

endOfGameFile << "GAME OVER FINAL STATS FOR ALL PLAYERS" << endl;
endOfGameFile << endl;

for(int i = 0; i < 2; i++){
    endOfGameFile << playersArray[i].getName() << "'s stats:" << endl;
    endOfGameFile << "Age: " << playersArray[i].getAge() << endl;
    endOfGameFile << "Strength: " << playersArray[i].getStrength() << endl;
    endOfGameFile << "Stamina: " << playersArray[i].getStamina() << endl;
    endOfGameFile << "Wisdom: " << playersArray[i].getWisdom() << endl;
    endOfGameFile << "Pride Points: " << playersArray[i].getPridePoints() << endl;
    endOfGameFile << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    endOfGameFile << endl;
    }
endOfGameFile << "Thank you for playing! :)" << endl;

endOfGameFile.close();
}