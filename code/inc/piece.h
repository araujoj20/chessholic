#pragma once

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

class Piece
{
    private:
        
    public:
        Piece();
        ~Piece();
        //virtual 
};
