#include "Chess.h"
#include <iostream>
#include <cmath>

Chess::Chess(ChessUI* ui, Board* b) : ui(ui), board(b){ }

Chess::~Chess(){
}

void Chess::setup() {
    Coordinate* c;
    // White pawns
    for(int x=0; x<BOARD_SIZE; ++x) {
        c = new Coordinate(x, 0);
        board->placePiece(new Pawn(Colour::WHITE), c);
        delete c;
    }

    // Black pawns
    for(int x=0; x<BOARD_SIZE; ++x) {
        c = new Coordinate(x, 4);
        board->placePiece(new Pawn(Colour::BLACK), c);
        delete c;
    }
}

void Chess::playGame() {
    setup();
    bool over = false;
    Colour side = Colour::WHITE;
    std::string player;
    std::string source, destination;
    do {
        board->draw();
        source = ui->getLocation(side, "of piece to move: ");
        destination = ui->getLocation(side, " of destination: ");

        Coordinate* sourceSquare = new Coordinate(source);
        Coordinate* destinationSquare = new Coordinate(destination);

        try{
          if(board->movePiece(side, sourceSquare, destinationSquare)) {
              if(board->isWinner(side)) {
                  over = true;
              }
              side = (side == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
          }
        } catch (no_piece_error& e) {
            ui->invalidMove(e);
        } catch (invalid_location_error& e) {
            ui->invalidMove(e);
        } catch (invalid_piece_error& e) {
            ui->invalidMove(e);
        }
        delete sourceSquare;
        delete destinationSquare;
    } while(!over);
    ui->gameOver(side);
}
