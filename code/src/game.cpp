#include "game.h"

Game::Game()
{
    display = new Display();
}

Game::~Game()
{
    delete display;
}

int Game::run()
{
    bool done = false;

    PieceID pieceTest{QUEEN, BLACK};
    Position pieceTestPos{7, 7};

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
            }
        }

        static int i = 0;
        i = (i + 1) & 7;

        pieceTestPos.column = i;
        pieceTestPos.row = i;

        display->renderClean();
        display->renderBoard();
        display->renderPiece(pieceTest, pieceTestPos);
        display->renderPresent();
    }

    return 0;
}