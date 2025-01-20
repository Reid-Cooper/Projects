#include "player.hpp"
#include "Board.h"
#include "Tiles.hpp"
#include <iostream>
using namespace std;

int main(){

player Players[2];

Board newBoard(2);
newBoard.initializeBoard();
newBoard.displayPlayerSelection(Players);
newBoard.playerPathSelection(Players);
newBoard.setPlayersArray(Players);
cout << endl;

//running the game
//player one goes first
int activePlayer = 0;

//sets player 1's turn to true before begenning
newBoard.getPlayersArray(activePlayer).setPlayersTurn(true);

do{

newBoard.displayMenu(activePlayer);

//only if the active players turn has been set to false by landing on an appropriate tile does the active player change
if(newBoard.getPlayersArray(activePlayer).getPlayersTurn() == false){

    //if no player has reached the end alternate
    if(newBoard.getPlayersArray(0).getPlayerPosition() != 51 && newBoard.getPlayersArray(1).getPlayerPosition() != 51){
        if(activePlayer == 0){
            activePlayer = 1;
            newBoard.getPlayersArray(activePlayer).setPlayersTurn(true);
        }
        else if(activePlayer == 1){
            activePlayer = 0;
            newBoard.getPlayersArray(activePlayer).setPlayersTurn(true);
        }
    }

    //if player 1 has reached the end only player 2 gets to play
    if(newBoard.getPlayersArray(0).getPlayerPosition() == 51 && newBoard.getPlayersArray(1).getPlayerPosition() != 51){
        activePlayer = 1;
        newBoard.getPlayersArray(activePlayer).setPlayersTurn(true);
    }

    //if player 2 has reached the end only player 1 gets to play
    if(newBoard.getPlayersArray(0).getPlayerPosition() != 51 && newBoard.getPlayersArray(1).getPlayerPosition() == 51){
        activePlayer = 0;
        newBoard.getPlayersArray(activePlayer).setPlayersTurn(true);
    }

}

}while(newBoard.getPlayersArray(0).getPlayerPosition() != 51 || newBoard.getPlayersArray(1).getPlayerPosition() != 51);

//writes the ending character stats to an output file ("final_stats.txt")
newBoard.writeToEndStatsToFile();
//prints the the final stats of each player, converts every leadership stat to 1000 pride points per 100 points of each stat, a winner is declared and GAME OVER message is printed
newBoard.displayEndGameScreen();

return 0;
}