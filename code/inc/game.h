#pragma once

#include "display.h"
#include "piece.h"
#include "board.h"

enum GameState {
    WaitingForSelection,
    ShowingPossibleMoves
};

class Game
{

    private:
        bool running = true;
        SDL_Event event;
        Display display;
        Board board;
        GameState state = GameState::WaitingForSelection;
        Position selectedPos{-1, -1};
        void handleClick(int x, int y);
        void handleEvent(const SDL_Event &event);
        void selectDestination(const Position& dest);
        void render();
    
    public:
        Game() = default;
        ~Game() = default;
        
        int run();

};