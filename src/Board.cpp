#include "Board.h"

Board::Board(unsigned int size) : size{size}
{
    board.resize(size,std::vector<Piece*>(size, nullptr));

    for(unsigned int i=0; i<board.size(); ++i) {
        for(unsigned int j=0; j<board[i].size(); ++j){
            board[i][j] = new Piece(Colour::NONE);
        }
    }
}

Board::~Board() {
    for(unsigned int i=0; i<board.size(); ++i){
        for(unsigned int j=0; j<board[i].size(); ++j){
           delete board[i][j];
        }
    }
}

bool Board::movePiece(Colour side, Coordinate* start, Coordinate* destination) {

    if(start->getX() >= size || start->getY() >= size || destination->getX() >= size || destination->getY() >= size) {
        throw invalid_location_error("Location not on the board.");
    }

    Piece* piece = getPiece(start);

    if(piece->getSide() == Colour::NONE)
        throw no_piece_error("No piece at that location.");

    if(side != piece->getSide())
        throw invalid_piece_error("Not your piece to move.");

    if(piece->isValidMove(start, destination, &board)) {
        board[start->getX()][start->getY()] = new Piece(Colour::NONE);
        placePiece(piece, destination);
        return true;
    }
    return false;
}

void Board::emptySpace(Coordinate* c){
    delete board[c->getX()][c->getY()];
    board[c->getX()][c->getY()] = new Piece(Colour::NONE);
}

void Board::placePiece(Piece* p, Coordinate* c) {    
    if(c->getX() >= size || c->getY() >= size) {
        throw invalid_location_error("Location not on the board.");
    }

    delete board[c->getX()][c->getY()];
    board[c->getX()][c->getY()] = p;
    p->updateLocation(c);
}

Piece* Board::getPiece(Coordinate* c) {
    return board[c->getX()][c->getY()];
}

bool Board::isWinner(Colour side) {
  Piece* p;
  Colour opponent = (side == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
  for(unsigned int i=0; i<board.size(); ++i) {
      for(unsigned int j=0; j<board[i].size(); ++j) {
        if(board[i][j]->getSide() == opponent) {
          return false;
        }
      }
  }
  return true;
}

void Board::draw() {

    std::cout << "   ";
    for(unsigned int x=0; x<size; ++x) {
        std::cout << (char)('A'+x);
    }
    std::cout << std::endl;

    std::cout << "   ";
    for(unsigned int x=0; x<size; ++x) {
        std::cout << '-';
    }
    std::cout << std::endl;

    for(int y=size-1; y>=0; --y) {
        std::cout << y+1 << "| ";
        for(unsigned int x=0; x<size; ++x) {
            Piece* piece = board[x][y];
            std::cout << (*piece);
        }
        std::cout << std::endl;
    }
}
