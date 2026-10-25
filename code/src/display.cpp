#include "display.h"

Display::Display()
{   
    SDL_Init(SDL_INIT_VIDEO);
    
    initSDL();
    initImage();
    createWindow();
    createRenderer();

    boardTexture_ = loadBoard();
    loadPieces();
}

Display::~Display()
{
    SDL_DestroyTexture(boardTexture_);

    for (const auto& texturesByColor : pieceTexture_) {
        for (SDL_Texture* texture : texturesByColor) {
            SDL_DestroyTexture(texture);
        }
    }

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    IMG_Quit();
    SDL_Quit();
}

void Display::initSDL() const
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << '\n';
        return;
    }
}

void Display::initImage() const
{
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
    {
		std::cerr << "Error initializing SDL_image: " << IMG_GetError() << '\n';
		SDL_Quit();
		return;
	}
}
void Display::createWindow()
{
    window_ = SDL_CreateWindow(
        gameName_.c_str(),          // window title
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
        windowWidth_,               // width, in pixels
        windowHeight_,              // height, in pixels
        SDL_WINDOW_RESIZABLE        // flags
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
    
    if (renderer_ == NULL){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
    }
    
    if (SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND)){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not change renderer mode: %s\n", SDL_GetError());
    }
}

void Display::renderSetColor(int r, int g, int b, int opacity)
{
    if (SDL_SetRenderDrawColor(
        renderer_,
        static_cast<Uint8>(r),
        static_cast<Uint8>(g),
        static_cast<Uint8>(b),
        static_cast<Uint8>(opacity))){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not set renderer color: %s\n", SDL_GetError());
    }
}

void Display::renderSquare(SquareColor color, Position pos)
{
    SDL_Rect square = texturePosition(pos);

    switch (color)
    {
        case SquareColor::GREEN:
            renderSetColor(170, 220, 190, 200);
            break;

        case SquareColor::RED:
            renderSetColor(170, 0, 0, 200);
            break;

        default:
            return;
    }
    SDL_RenderFillRect(renderer_, &square);
}

SDL_Texture* Display::loadBoard() const
{
    return IMG_LoadTexture(renderer_, "data/board/bases.png");
}

void Display::loadPieces()
{
    pieceTexture_[PieceColor::WHITE][PieceType::KING] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/wk.png");

    pieceTexture_[PieceColor::WHITE][PieceType::QUEEN] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/wq.png");

    pieceTexture_[PieceColor::WHITE][PieceType::ROOK] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/wr.png");

    pieceTexture_[PieceColor::WHITE][PieceType::BISHOP] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/wb.png");

    pieceTexture_[PieceColor::WHITE][PieceType::KNIGHT] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/wn.png");

    pieceTexture_[PieceColor::WHITE][PieceType::PAWN] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/wp.png");

    pieceTexture_[PieceColor::BLACK][PieceType::KING] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/bk.png");

    pieceTexture_[PieceColor::BLACK][PieceType::QUEEN] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/bq.png");

    pieceTexture_[PieceColor::BLACK][PieceType::ROOK] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/br.png");

    pieceTexture_[PieceColor::BLACK][PieceType::BISHOP] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/bb.png");

    pieceTexture_[PieceColor::BLACK][PieceType::KNIGHT] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/bn.png");

    pieceTexture_[PieceColor::BLACK][PieceType::PAWN] =
        IMG_LoadTexture(renderer_, "data/pieces/neo/bp.png");
}

SDL_Texture* Display::textureFor(PieceID piece) const
{
    const auto color = static_cast<std::size_t>(piece.color);
    const auto type  = static_cast<std::size_t>(piece.type);

    if (color >= pieceTexture_.size() || type >= pieceTexture_[color].size()) {
        return nullptr;
    }

    return pieceTexture_[color][type];
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
    SDL_Rect square = texturePosition(position);
    SDL_Texture* texture = textureFor(id);
    renderTexture(texture, &square); // TODO
}

SDL_Rect Display::texturePosition(Position pos)
{
    return {
        (pos.column * squareWidth),
        (pos.row * squareWidth),
        squareWidth,
        squareWidth
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