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

    bool operator<(const PieceID& other) const
    {
        if (type != other.type) {
            return type < other.type;
        }

        return color < other.color;
    }
};


// #include <map>

// textures[{PieceType::King, PieceColor::White}] = whiteKing;

// SDL_Texture* texture = textures.at({
//     PieceType::King,
//     PieceColor::White
// });