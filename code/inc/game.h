#pragma once

#include "display.h"
#include "piece.h"
#include "board.h"

class Game
{

    private:
    
    Display* display;
    
    public:
        Game();
        ~Game();
        
        
        int run();

};