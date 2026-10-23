#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <array>
#include <iostream>
#include <string>
#include "piece.h"
#include "board.h"

class Display {

    private:
        std::string gameName_ = "CHESSHOLIC";
        SDL_Window* window_ = nullptr;
        SDL_Renderer* renderer_ = nullptr;
        SDL_Texture* boardTexture_ = nullptr;
        
        std::array<std::array<SDL_Texture*, 6>, 2> pieceTexture_;
        
        unsigned int windowWidth_  = 800;
        unsigned int windowHeight_ = 800;
        void initSDL() const;
        void initImage() const;    
        void createWindow();
        void createRenderer();
        SDL_Texture* loadBoard() const;
        void loadPieces();
        SDL_Rect texturePosition(Position pos);

    public:
        Display(); // == default (no need to implement func)
        ~Display();

        //void changeWindowSize(unsigned int);
        void renderTexture(SDL_Texture* texture, const SDL_Rect* position);
        void renderPiece(PieceID id, Position position);
        void renderBoard();
        void renderPresent();
        void renderClean();
        SDL_Texture* textureFor(PieceID piece) const;
};