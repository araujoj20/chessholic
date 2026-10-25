#include "game.h"

Game::Game()
{
    display = new Display();
}

Game::~Game()
{
    delete display;
}

void handleClick(Display& ui, int x, int y){

    ui.renderClean();
    ui.renderBoard();
    ui.renderSquare(SquareColor::GREEN, Position{x+1,7-y});
    ui.renderPiece(PieceID{QUEEN, BLACK}, Position{x,7-y});
    //ui.renderSquare(SquareColor::RED, Position{6,5});
    ui.renderPresent();
}

int Game::run()
{
    bool done = false;

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                handleClick(*display, ((event.button.x)/100), (7-((event.button.y)/100)));
            }

            else if (event.type == SDL_QUIT)
            {
                done = true;
            }
        }
    }

    return 0;
}