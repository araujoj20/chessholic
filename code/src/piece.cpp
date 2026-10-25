#include "piece.h"

Piece::Piece(PieceType type, PieceColor color) : id_{type, color} {}

PieceID Piece::getId() const 
{
    return id_;
}

bool Piece::getHasMoved() const
{
    return hasMoved_;
}

void Piece::setHasMoved(bool value){
    hasMoved_ = value;
}

Pawn::Pawn(PieceColor color) : Piece(PieceType::PAWN, color) {}

MovementPattern Pawn::movementPattern() const
{
    const int direction = (getId().color == PieceColor::WHITE) ? 1 : -1;

    if (!getHasMoved())
    {
        return {
            {{direction, 0}, {2 * direction, 0}},
            false
        };
    }

    return {
        {{direction, 0}},
        false
    };
}

Knight::Knight(PieceColor color) : Piece(PieceType::KNIGHT, color) {}

MovementPattern Knight::movementPattern() const
{
	return {{
        {2,  1}, 
        {2, -1}, 
        {-2, 1}, 
        {-2,-1},
		{1,  2}, 
        {1, -2}, 
        {-1, 2}, 
        {-1,-2}},
		false
	};
}

Bishop::Bishop(PieceColor color) : Piece(PieceType::BISHOP, color) {}

MovementPattern Bishop::movementPattern() const
{
	return {{
        {1,  1}, 
        {1, -1}, 
        {-1, 1}, 
        {-1,-1}}, 
        true
    };
}

Rook::Rook(PieceColor color) : Piece(PieceType::ROOK, color) {}

MovementPattern Rook::movementPattern() const
{
	return {{
        {1, 0}, 
        {-1,0}, 
        {0, 1}, 
        {0,-1}}, 
        true
    };
}

Queen::Queen(PieceColor color) : Piece(PieceType::QUEEN, color) {}

MovementPattern Queen::movementPattern() const
{
	return {{
        {1,  0}, 
        {-1, 0}, 
        {0,  1}, 
        {0, -1},
		{1,  1}, 
        {1, -1}, 
        {-1, 1}, 
        {-1,-1}},
		true
	};
}

King::King(PieceColor color) : Piece(PieceType::KING, color) {}

MovementPattern King::movementPattern() const
{
	return {{
        {1,  0}, 
        {-1, 0}, 
        {0,  1}, 
        {0, -1},
		{1,  1}, 
        {1, -1}, 
        {-1, 1}, 
        {-1,-1}},
		false
	};
}
