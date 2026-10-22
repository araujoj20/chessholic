#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>
#include <map>
#include "piece.h"
#include "board.h"

class Display {

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

    private:
        std::string gameName_ = "CHESSHOLIC";
        SDL_Window* window_ = nullptr;
        SDL_Renderer* renderer_ = nullptr;
        SDL_Texture* boardTexture_ = nullptr;
        
        std::map<PieceID, SDL_Texture*> pieceTexture_;
        
        unsigned int windowWidth_  = 800;
        unsigned int windowHeight_ = 800;
        
        void createWindow();
        void createRenderer();
        SDL_Texture* loadBoard();
        void loadPieces();
        SDL_Rect texturePosition(Position pos);
};