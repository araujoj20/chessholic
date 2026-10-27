#pragma once

#include "piece.h"

#include <array>
#include <memory>
#include <utility>

enum class PlayerColor {
    WHITE,
    BLACK
};

using BoardSquares = std::array<std::array<std::unique_ptr<Piece>, 8>, 8>; // easier to use in functions
struct Position
{
    int column;
    int row;

    //Position(int column, int row) : column(column), row(7-row) {} // convert automatically y axis
    bool operator==(const Position& other) const{ // overload == operator, to allow pos compare 
        return column == other.column && row == other.row;
    }
};

struct PossibleMoves
{
    std::vector<Position> moves;
    std::vector<Position> captures;
};

class Board {

    private:

    public:
        Board();
        ~Board() = default;
        const Piece* pieceAt(Position pos) const;
        void movePiece(Position start, Position end);
        PossibleMoves possibleMoves(const Position& pos) const;
        BoardSquares squares_;
};