#include "TextureManager.h"
#include "Game.h"

TextureManager * TextureManager::m_instance = 0;

bool TextureManager::Load ( const char * fileName, const string & textureID, SDL_Renderer * renderer )
{
    SDL_Surface * tmpSurface = IMG_Load ( fileName ); // Creating surface from image
    if ( tmpSurface == 0 ){
        return false;
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface ( renderer, tmpSurface ); // Creating texture from surface
    SDL_FreeSurface ( tmpSurface );

    if ( texture != 0 ){
        m_textureMap[textureID] = texture; // Inserting texture ID into the map
        return true;
    }

    return false;
}

void TextureManager::Draw ( const string & textureID, int xPos, int yPos, int width, int height, SDL_Renderer * renderer, SDL_RendererFlip flip )
{
    SDL_Rect srcRect, dstRect;

    srcRect.x = 0;    //cout << m_position.getX () << " " << m_position.getY() << endl;
    srcRect.y = 0;
    srcRect.w = width;
    srcRect.h = height;

    dstRect.x = xPos;
    dstRect.y = yPos;
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;

    SDL_RenderCopyEx ( renderer, m_textureMap[textureID], &srcRect, &dstRect, 0, 0, flip );
}

void TextureManager::DrawFrame ( const string & textureID, double xPos, double yPos, int width, int height, int currentRow, int currentFrame, SDL_Renderer * renderer, SDL_RendererFlip flip )
{
    //cout << textureID << " " << xPos << " " << yPos << " " << width << " " << height << endl;
    //cout << currentRow << endl;
    SDL_Rect srcRect, dstRect;

    srcRect.x = width * currentFrame;
    srcRect.y = height * ( currentRow - 1 );
    srcRect.w = width;
    srcRect.h = height;

    dstRect.x = xPos;
    dstRect.y = yPos;
    dstRect.w = width;
    dstRect.h = height;

    SDL_RenderCopyEx ( renderer, m_textureMap[textureID], &srcRect, &dstRect, 0, 0, flip );    
}

void TextureManager::ClearFromTextureMap ( const string textureID )
{
    m_textureMap.erase ( textureID );
}