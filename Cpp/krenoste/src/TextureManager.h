#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

using namespace std;

// Singleton Texture Manager class
class TextureManager{
public:
    static TextureManager * Instance ( void )
    {
        if ( m_instance == 0 ){
            m_instance = new TextureManager;
        }
        return m_instance;
    }

    bool Load ( const char * fileName, const string & textureID, SDL_Renderer * renderer ); // Loading textures
    void Draw ( const string & textureID, int xPos, int yPos, int width, int height, SDL_Renderer * renderer, SDL_RendererFlip flip = SDL_FLIP_NONE );  // Rendering image
    // Rendering animated images
    void DrawFrame ( const string & textureID, double xPos, double yPos, int width, int height, int currentRow, int currentFrame, SDL_Renderer * renderer, SDL_RendererFlip flip = SDL_FLIP_NONE );
    void ClearFromTextureMap ( const string textureID ); // Delete texture 

private:
    TextureManager ( void ) {}  // Now a singleton class
    ~TextureManager ( void ) {} // Destructor
    static TextureManager * m_instance;

    map<string, SDL_Texture*> m_textureMap;

};

typedef TextureManager TheTextureManager;   // Setting an alias

#endif /* TEXTURE_MANAGER_H */