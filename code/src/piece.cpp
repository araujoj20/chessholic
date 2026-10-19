#include "piece.h"

Piece::Piece(Color color, Type type) : color_(color), type_(type) {}

Piece::Color Piece::color() const {
	return color_;
}

Piece::Type Piece::type() const {
	return type_;
}

Pawn::Pawn(Color color) : Piece(color, Type::Pawn) {}

MovementPattern Pawn::movementPattern() const {
    const int direction = color() == Color::White ? 1 : -1;

    if (!hasMoved_) {
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

Knight::Knight(Color color) : Piece(color, Type::Knight) {}

MovementPattern Knight::movementPattern() const {
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

Bishop::Bishop(Color color) : Piece(color, Type::Bishop) {}

MovementPattern Bishop::movementPattern() const {
	return {{
        {1,  1}, 
        {1, -1}, 
        {-1, 1}, 
        {-1,-1}}, 
        true
    };
}

Rook::Rook(Color color) : Piece(color, Type::Rook) {}

MovementPattern Rook::movementPattern() const {
	return {{
        {1, 0}, 
        {-1,0}, 
        {0, 1}, 
        {0,-1}}, 
        true
    };
}

Queen::Queen(Color color) : Piece(color, Type::Queen) {}

MovementPattern Queen::movementPattern() const {
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

King::King(Color color) : Piece(color, Type::King) {}

MovementPattern King::movementPattern() const {
	return {
		{
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
