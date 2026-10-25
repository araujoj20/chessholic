#pragma once

#include <vector>

enum PieceType {
    PAWN,
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT
};

enum PieceColor {
    WHITE,
    BLACK
};

struct PieceID {
    PieceType type;
    PieceColor color;
};

struct Offset
{
    int d_raw;      // dx
    int d_column;   // dy
};

struct MovementPattern {
    std::vector<Offset> directions;
    bool extend;
};

class Piece
{
    private:
        bool hasMoved_ = false;
        PieceID id_;
    public:
        Piece(PieceType type, PieceColor color);
        virtual ~Piece() = default;
        PieceID getId() const;
        bool getHasMoved() const;
        void setHasMoved(bool value);
        virtual MovementPattern movementPattern() const = 0;
};

class Pawn : public Piece {

    public:
        Pawn(PieceColor color);
        MovementPattern movementPattern() const override;
};

class Knight : public Piece {

    public:
        Knight(PieceColor color);
        MovementPattern movementPattern() const override;
};

class Bishop : public Piece {

    public:
        Bishop(PieceColor color);
        MovementPattern movementPattern() const override;
};
class Rook : public Piece {

    public:
        Rook(PieceColor color);
        MovementPattern movementPattern() const override;
};
class Queen : public Piece {

    public:
        Queen(PieceColor color);
        MovementPattern movementPattern() const override;
};
class King : public Piece {

    public:
        King(PieceColor color);
        MovementPattern movementPattern() const override;
};

