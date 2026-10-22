#include "display.h"

Display::Display()
{   
    SDL_Init(SDL_INIT_VIDEO);

    createWindow();
    createRenderer();

    //IMG_Init(IMG_INIT_PNG);

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
    {
		std::cerr << "Error initializing SDL_image: " << IMG_GetError() << '\n';
		SDL_Quit();
		return;
	}

    boardTexture_ = loadBoard();
    loadPieces();
}

Display::~Display()
{
    SDL_DestroyTexture(boardTexture_);

    for (const auto& texture : pieceTexture_) {
        SDL_DestroyTexture(texture.second);
    }

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    IMG_Quit();
    SDL_Quit();
}

void Display::createWindow()
{
    window_ = SDL_CreateWindow(
        gameName_.c_str(),          // window title
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
        windowWidth_,               // width, in pixels
        windowHeight_,              // height, in pixels
        SDL_WINDOW_RESIZABLE        // flags - see below
    );

    if (window_ == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    }
}

void Display::createRenderer()
{
    renderer_ = SDL_CreateRenderer(
        window_,
        -1,
        SDL_RENDERER_ACCELERATED    // The renderer_ uses hardware acceleration
    );

    if (renderer_ == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    }
}

SDL_Texture* Display::loadBoard()
{
    return IMG_LoadTexture(renderer_, "data/board/bases.png");
}

void Display::loadPieces()
{
    pieceTexture_[{PieceType::KING, PieceColor::WHITE}] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/wk.png");

    pieceTexture_[{PieceType::QUEEN, PieceColor::WHITE}] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/wq.png");

    pieceTexture_[{PieceType::ROOK, PieceColor::WHITE}] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/wr.png");

    pieceTexture_[{PieceType::BISHOP, PieceColor::WHITE}] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/wb.png");

    pieceTexture_[{PieceType::KNIGHT, PieceColor::WHITE}] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/wn.png");

    pieceTexture_[{PieceType::PAWN, PieceColor::WHITE}] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/wp.png");

    pieceTexture_[{PieceType::KING, PieceColor::BLACK}] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/bk.png");

    pieceTexture_[{PieceType::QUEEN, PieceColor::BLACK}] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/bq.png");

    pieceTexture_[{PieceType::ROOK, PieceColor::BLACK}] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/br.png");

    pieceTexture_[{PieceType::BISHOP, PieceColor::BLACK}] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/bb.png");

    pieceTexture_[{PieceType::KNIGHT, PieceColor::BLACK}] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/bn.png");

    pieceTexture_[{PieceType::PAWN, PieceColor::BLACK}] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/bp.png");
}

SDL_Texture* Display::textureFor(PieceID piece) const
{
    const auto textureIterator = pieceTexture_.find(piece);

    if (textureIterator == pieceTexture_.end()) {
        return nullptr;
    }

    return textureIterator->second; // returns piece texture aka loaded PNG
}

void Display::renderTexture(SDL_Texture* texture, const SDL_Rect* position)
{   
    if (texture == nullptr) {
        std::cerr << "Texture not found for piece\n";
        return;
    }

    if (SDL_RenderCopy(renderer_, texture, NULL, position))
    {
		std::cerr << "Error in SDL_RenderCopy: " << IMG_GetError() << '\n';
		return;
	}
}

void Display::renderBoard()
{
    renderTexture(boardTexture_, NULL);
}

void Display::renderPiece(PieceID id, Position position)
{
    SDL_Rect rectangle = texturePosition(position);
    SDL_Texture* texture = textureFor(id);
    renderTexture(texture, &rectangle); // TODO
}

SDL_Rect Display::texturePosition(Position pos)
{
    const int squareWidth  = static_cast<int>(windowWidth_ / 8);
    const int squareHeight = static_cast<int>(windowHeight_ / 8);

    return {
        static_cast<int>(pos.column * squareWidth),
        static_cast<int>(pos.row * squareHeight),
        squareWidth,
        squareHeight
    };
}

void Display::renderPresent()
{
    SDL_RenderPresent(renderer_);
}

void Display::renderClean()
{
    SDL_RenderClear(renderer_);
}