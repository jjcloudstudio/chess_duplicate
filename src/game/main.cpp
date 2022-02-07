#include "Chess.h"

int main()
{
    ChessUI* ui = new ChessUI();
    Board* board = new Board(5);
    Chess game(ui, board);
    game.setup();
    game.playGame();

    delete ui;
    delete board;    
}
