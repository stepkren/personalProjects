#ifndef GAME_H
#define GAME_H

#include "GameObject.h"
#include "TextureManager.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "Tilemap.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Game{
public:
    // Global access
    static Game * Instance ()
    {
        if ( m_instance == 0 ){
            m_instance = new Game ();
        }
        return m_instance;
    }

    bool Init ( const char * title, int x, int y, int width, int height, bool fullscreen ); // Initialization of a SDL objects
    bool Running ( void ) { return m_isRunning; }   // Check if the game is running
    void HandleEvents ( void );
    void Update ( void );
    void Render ( void );   // Method for rendering objects to the screen
    void Clean ( void );    // Freeing memory
    void Quit ( void ) { m_isRunning = false; } // Quitting the game

    GameStateMachine * GetStateMachine ( void ) { return m_GameStateMachine; }  // GameStateMachine getter ( used for changing states )

    SDL_Renderer * GetRenderer ( void ) { return m_renderer; }  // Renderer getter

private:
    Game ( void ) {}    // Game class is now a singleton class ( only one instance of this class can exist )
    ~Game ( void ) {}   // Game class destructor

    // Member variables
    static Game * m_instance;

    SDL_Renderer * m_renderer;
    SDL_Window * m_window;

    bool m_isRunning;
    vector<GameObject*> m_gameobjects;

    GameStateMachine * m_GameStateMachine;
};

typedef Game TheGame; // Creation of an alias

#endif /* GAME_H */