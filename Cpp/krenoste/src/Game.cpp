#include "Game.h"

Game * Game::m_instance = 0;

/**
 * Initialization of SDL Window and Renderer
 * Initialization of SDL TTF
 * Creation of window 
*/

bool Game::Init ( const char * title, int x, int y, int width, int height, bool fullscreen )
{
    if ( TTF_Init () != 0 ){
        return false;        
    }
    if ( SDL_Init ( SDL_INIT_EVERYTHING ) == 0 ){
        cout << "SDL initialised sucessfully!" << endl;

        int flags = 0;

        if ( fullscreen ){
            flags = SDL_WINDOW_FULLSCREEN;  // Set flag to fullscreen
        }

        m_window = SDL_CreateWindow ( title, x, y, width, height, flags );

        if ( m_window != 0 ){
            cout << "Window created sucessfully!" << endl;

            m_renderer = SDL_CreateRenderer ( m_window, -1, 0 );

            if ( m_renderer != 0 ){
                cout << "Renderer created sucessfully!" << endl;
                SDL_SetRenderDrawColor ( m_renderer, 9, 2, 42, 255 );   // Setting window background color
            }
            else { return false; }
        }
        else { return false; }

    }
    else {
        cout << "SDL initialisation failed!" << endl;
        return false;
    }

    m_isRunning = true;

    m_GameStateMachine = new GameStateMachine ();
    m_GameStateMachine -> ChangeGameState ( new MenuState () ); // Initializing new menu state


    cout << "Number of entities loaded=" << m_gameobjects.size() << endl;
    return true;
}

void Game::HandleEvents()
{
    TheInputHandler::Instance () -> Update ();  // InputHandler singleton class Update method

    //  Play game from menu by pressing Enter
    if ( TheInputHandler::Instance() -> IsKeyDown ( SDL_SCANCODE_RETURN ) ){
        m_GameStateMachine -> ChangeGameState ( new PlayState () );
    }    
}

void Game::Update ( void )
{
    m_GameStateMachine -> Update ();    // Update method of GameStateMachine class
}

void Game::Render ( void )
{
    SDL_RenderClear ( m_renderer ); // Clear window with background color

    m_GameStateMachine -> Render ();    //  Render method of GameStateMachine class

    SDL_RenderPresent ( m_renderer );   // Update the screen
}

void Game::Clean ( void )
{
    cout << "cleaning..." << endl;
    SDL_DestroyWindow ( m_window ); // Destroying window
    SDL_DestroyRenderer ( m_renderer ); // Destroying renderer
    TheInputHandler::Instance () -> Clean ();   
    SDL_Quit ();    // Quitting the game
}