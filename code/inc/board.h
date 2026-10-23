#pragma once

#include "piece.h"

#include <array>
#include <memory>
struct Position
{
    unsigned int row;
    unsigned int column;
};

class Board {

    private:
    
        std::array<std::array<std::unique_ptr<Piece>, 8>, 8> squares_;

    public:
    
};