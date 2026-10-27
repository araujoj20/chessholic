#include "board.h"

Board::Board()
{
    //squares_[0][0] = std::unique_ptr<Piece>(new Rook(PieceColor::WHITE));
    squares_[0][0] = std::make_unique<Rook>  (PieceColor::WHITE);
    squares_[1][0] = std::make_unique<Knight>(PieceColor::WHITE);
    squares_[2][0] = std::make_unique<Bishop>(PieceColor::WHITE);
    squares_[3][0] = std::make_unique<Queen> (PieceColor::WHITE);
    squares_[4][0] = std::make_unique<King>  (PieceColor::WHITE);
    squares_[5][0] = std::make_unique<Bishop>(PieceColor::WHITE);
    squares_[6][0] = std::make_unique<Knight>(PieceColor::WHITE);
    squares_[7][0] = std::make_unique<Rook>  (PieceColor::WHITE);

    for (int column = 0; column < 8; column++){
        squares_[column][1] = std::make_unique<Pawn>(PieceColor::WHITE);
        squares_[column][6] = std::make_unique<Pawn>(PieceColor::BLACK);
    }

    squares_[0][7] = std::make_unique<Rook>  (PieceColor::BLACK);
    squares_[1][7] = std::make_unique<Knight>(PieceColor::BLACK);
    squares_[2][7] = std::make_unique<Bishop>(PieceColor::BLACK);
    squares_[3][7] = std::make_unique<Queen> (PieceColor::BLACK);
    squares_[4][7] = std::make_unique<King>  (PieceColor::BLACK);
    squares_[5][7] = std::make_unique<Bishop>(PieceColor::BLACK);
    squares_[6][7] = std::make_unique<Knight>(PieceColor::BLACK);
    squares_[7][7] = std::make_unique<Rook>  (PieceColor::BLACK);
}

const Piece* Board::pieceAt(Position pos) const
{
    return squares_[pos.column][pos.row].get(); // .get to use pointer on Piece
}

PossibleMoves Board::possibleMoves(const Position& pos) const
{
    PossibleMoves result;

    const Piece* initialPiece = pieceAt(pos);
    const Piece* targetPiece;
    
    if (pieceAt(pos) == nullptr)
    {
        return result;
    }

    const MovementPattern pattern = initialPiece->movementPattern();

    for (const Offset& direction : pattern.directions)
    {
        const int maxSteps = pattern.extend ? 7 : 1;

        for (int step = 1; step <= maxSteps; ++step)
        {
            const Position target{
                pos.column + direction.d_column * step,
                pos.row + direction.d_raw * step
            };

            if (target.column < 0 || target.column >= 8 ||
                target.row < 0 || target.row >= 8)
            {
                break;
            }

            targetPiece = pieceAt(target);

            if (targetPiece == nullptr)
            {
                result.moves.push_back(target);
                continue;
            }

            if (targetPiece->getId().color != initialPiece->getId().color)
            {
                result.captures.push_back(target);
            }

            break;
        }
    }
    return result;
}

void Board::movePiece(Position start, Position end)
{
    auto movingPiece = std::move(squares_[start.column][start.row]);

    if (movingPiece != nullptr && !(movingPiece->getHasMoved())){
        movingPiece->setHasMoved(true);
    }

    squares_[end.column][end.row] = std::move(movingPiece);
}