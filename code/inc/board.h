#pragma once

#include "piece.h"

#include <array>
#include <memory>
struct Position
{
    int column;
    int row;
};

class Board {

    private:
        Board();
        ~Board() = default;
        std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board_;

    public:
    
};