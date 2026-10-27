#include "game.h"

void Game::render()
{
    display.renderClean();
    display.renderBoard();

    if (state == GameState::ShowingPossibleMoves){
        
        const PossibleMoves possibleMoves = board.possibleMoves(selectedPos);

        for (const Position& move : possibleMoves.moves){
            display.renderSquare(SquareColor::GREEN, move);
        }
        for (const Position& capture : possibleMoves.captures){
            display.renderSquare(SquareColor::RED, capture);
        }
    }
    display.renderPieces(board.squares_);
    display.renderPresent();
}

void Game::selectDestination(const Position& dest)
{
    const PossibleMoves possibleMoves = board.possibleMoves(selectedPos);
    bool isValid = false;

    for (const Position& move : possibleMoves.moves){
        if (dest == move){
            isValid = true;
            break;
        }
    }

    for (const Position& capture : possibleMoves.captures){
        if (dest == capture){
            isValid = true;
            break;
        }
    }
    if(isValid){
        board.movePiece(selectedPos, dest);
    }
    state = GameState::WaitingForSelection;
}

void Game::handleClick(int x, int y)
{
    if (x < 0 || x >= 8 || y < 0 || y >= 8){
        return;
    }

    const Position clickedPosition{x, y};
    switch (state)
    {
        case GameState::WaitingForSelection:
            if (board.pieceAt(clickedPosition) != nullptr){
                selectedPos = clickedPosition;
                state = GameState::ShowingPossibleMoves;
            }
            break;

        case GameState::ShowingPossibleMoves:
            const Piece* clickedPiece = board.pieceAt(clickedPosition);
            if (clickedPiece != nullptr &&
                clickedPiece->getId().color == board.pieceAt(selectedPos)->getId().color){
                selectedPos = clickedPosition;
            }
            else{
                selectDestination(clickedPosition);
                    state = GameState::WaitingForSelection;
            }
            break;
    }

    render();
}

void Game::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
            handleClick(event.button.x / 100, event.button.y / 100);
        }
    else if (event.type == SDL_QUIT){
        running = false;
    }
}

int Game::run()
{

    render();

    while (running) {

        if (SDL_WaitEvent(&event) == 0){ // PollEvent is non-blocking. Waiting avoids a busy loop when idle (100% app usage)
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_WaitEvent failed: %s", SDL_GetError());
            return 1;
        }
        else{
            handleEvent(event);
        }
    }

    return 0;
}