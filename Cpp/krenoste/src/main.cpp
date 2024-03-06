// Including standard library headers
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <SDL2/SDL.h>
// Including custom headers
#include "GameObject.h"
#include "Game.h"


int main ( int argc, char* argv[] )
{
    // Removing contents of file containing filePath
    ofstream fileTrunc ( "examples/filePath.txt", ofstream::trunc );
    fileTrunc.close();

    // Checking first argument of the execution command
    string filePath;    
    if ( argc > 1 ){
        filePath = argv[1];
    }
    else{
        filePath = "newConfig.json"; // defaultly set to new game
    }

    ofstream file ( "examples/filePath.txt" );
    file << filePath;
    file.close();

    // Setting the delay between frames
    unsigned int TIME_DELAY = 1000/144; 

    Uint32 frameStart, frameTime;
    if ( TheGame::Instance () -> Init ( "LUNARIA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 768, false ) ){
        while ( TheGame::Instance () -> Running () ){
            frameStart = SDL_GetTicks();
            
            TheGame::Instance () -> HandleEvents ();    // Singleton class method to Handle events
            TheGame::Instance () -> Update ();  // Singleton class method to Update the game
            TheGame::Instance () -> Render ();  // Singleton class method to Render objects in the game

            // Setting stable Frames Per Second
            frameTime = SDL_GetTicks() - frameStart;
            if ( frameTime < TIME_DELAY ){
                SDL_Delay ( (int)( TIME_DELAY - frameTime) );
            }
        }
    }
    else{
        cout << "The Game initialisation failed..." << endl;    // If SDL doesn't initialize crash the game
        return EXIT_FAILURE;
    }

    cout << "Game closing!" << endl;
    TheGame::Instance () -> Clean ();   // Cleaning the game ( deleting window, renderer, etc. )

    return EXIT_SUCCESS;
}