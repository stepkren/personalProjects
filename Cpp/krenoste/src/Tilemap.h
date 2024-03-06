#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TextureManager.h"
#include "SDLGameObject.h"

using namespace std;

// Tilemap class
class Tilemap{
public:
    // Tilemap class constructor
    Tilemap ( void ): m_mapHeight ( 0 ), m_mapWidth ( 0 ), offSetX ( 0 ), offSetY ( 0 ), mapTex ( nullptr ), m_sumX ( 0 ), m_sumY ( 0 ), m_playerPosX ( 20 ), m_playerPosY ( 12 ), m_burnt ( 0 ), m_suffocating ( 0 ), m_attackDamage ( 0 )
    {}
    ~Tilemap ( void ) {} // Destructor

    void Render ( void );   // Rendering tilemap
    void UpdateX ( const int x ); // Updating X position
    void UpdateY ( const int y ); // Updating Y position
    void UpdateBuild ( PlayerCharacter &player );   // Changing map when player builds
    void UpdateMine ( PlayerCharacter &player );    // Mining meteorite
    void UpdatePlayer ( PlayerCharacter &player, vector<GameObject*> &objects ); // Update player
    void Clean ( void );

    bool loadMatrix ( const char * fileName, PlayerCharacter &player ); // Load complete tile map
    int ** GetTileMap ( void ) { return &*m_tilemap; } // Getter for tilemap
    int GetOffSetX ( void ) { return offSetX; } // Getter for offsetX
    int GetOffSetY ( void ) { return offSetY; } // Getter for offsetY

private:
    // Member variables
    int m_mapHeight;
    int m_mapWidth;
    int offSetX;
    int offSetY;
    SDL_Texture * mapTex;

    int m_sumX;
    int m_sumY;

    int m_playerPosX;
    int m_playerPosY;
    int m_burnt;
    int m_suffocating;

    int m_attackDamage;

    int ** m_tilemap;
};

#endif /* MAP_H */