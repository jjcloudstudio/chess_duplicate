#include "Pawn.h"



bool Pawn::isValidMove(Coordinate* start, Coordinate* destination,
                       std::vector<std::vector<Piece*>>* board) {

    bool oneSpace = (side == Colour::WHITE) ? (destination->getY() - start->getY() == 1) : (start->getY() - destination->getY() == 1);
    bool twoSpace = false;
    if(abs(start->getY() - destination->getY()) == 2)
        twoSpace = (side == Colour::WHITE) ? start->getY() == 0 : start->getY() == 4;
    bool correctNumber = oneSpace || twoSpace;
    bool notSideways = (start->getX() == destination->getX());

    // Enpassant
    enPassantState = enPassant(start, destination, *board);// && !enPassantState;
    if(enPassantState) {
        int yOffset = (side == Colour::WHITE) ? -1 : 1;
        delete enPassantCoord;
        enPassantCoord = new Coordinate(destination->getX(), destination->getY() + yOffset);
    }

    Pawn* left;
    Pawn* right;
    unsigned int epRank = 2;
    right = (start->getX() != 0) ? dynamic_cast<Pawn*>((*board)[start->getX()-1][epRank]) : nullptr;
    left = (start->getX() != 4) ? dynamic_cast<Pawn*>((*board)[start->getX()+1][epRank]) : nullptr;


    bool enpassantValid = ((right != nullptr && *destination == *(right->enPassantCoord)) ||
                            (left != nullptr && *destination == *(left->enPassantCoord))) &&
                            (destination->getY() == 1 || destination->getY() == 3);

    if(enpassantValid) {
        int yOffset = (side == Colour::WHITE) ? -1 : 1;
        delete (*board)[destination->getX()][destination->getY()+yOffset];
        (*board)[destination->getX()][destination->getY()+yOffset] = new Piece(Colour::NONE);
    }

    bool capture = false;
    if(oneSpace && abs(start->getX()-destination->getX()) == 1) {
        capture = ((*board)[destination->getX()][destination->getY()]->getSide() != Colour::NONE) &&
                  (side != (*board)[destination->getX()][destination->getY()]->getSide());
    }

    if(!capture) {
        if((*board)[destination->getX()][destination->getY()]->getSide() != Colour::NONE) {
            return false;
        }
    }

    return (correctNumber && notSideways) || capture || enpassantValid;
}

bool Pawn::enPassant(Coordinate* start, Coordinate* destination, std::vector<std::vector<Piece*>> board) {

    bool whitePawnInitialTwo = start->getY() == 0 && destination->getY() == 2;
    bool blackPawnLeft = (start->getX() != 0) && (dynamic_cast<Pawn*>(board[start->getX()-1][2]) != nullptr);
    bool blackPawnRight = (start->getX() != 4) && (dynamic_cast<Pawn*>(board[start->getX()+1][2]) != nullptr);

    if(whitePawnInitialTwo && (blackPawnLeft || blackPawnRight)) {
        return true;
    }

    bool blackPawnInitialTwo = start->getY() == 4 && destination->getY() == 2;
    bool whitePawnRight = (start->getX() != 0) && (dynamic_cast<Pawn*>(board[start->getX()-1][2]) != nullptr);
    bool whitePawnLeft = (start->getX() != 4) && (dynamic_cast<Pawn*>(board[start->getX()+1][2]) != nullptr);

    if(blackPawnInitialTwo && (whitePawnLeft || whitePawnRight)) {
        return true;
    }
    return false;
}
