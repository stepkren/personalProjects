#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <iostream>
#include <vector>
#include "Vector2D.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

//  Enum representign mouse buttons
enum mouse_buttons{
    LEFT = 0,
    RIGHT = 1,
    MIDDLE = 2  
};

class InputHandler{
public:
    static InputHandler * Instance ( void )
    {
        if ( m_instance == 0 ){
            m_instance = new InputHandler();
        }
        return m_instance;
    }

    void Update ( void );
    void Clean ( void );
    void Reset ( void );

    bool IsKeyDown ( SDL_Scancode key );    // Pressing a specific key returns true
    bool GetMouseButtonState ( int buttonNumber );  // @return true if mousebutton is pressed

    //  @return Vector2D class object of mouse position
    Vector2D * GetMousePosition ( void )
    {
        return m_mousePosition;
    }

private:
    // InputHandler class is now a singleton class
    // Keystates array representing keyboard keys
    // Boolean vector initialized to none buttons pressed
    InputHandler ( void )
    : m_keystates ( SDL_GetKeyboardState ( 0 ) ), m_mousePosition ( new Vector2D ( 0, 0 ) )
    {
        for ( int i = 0; i < 3; i++ ){
            m_mouseButtonStates.push_back ( false );
        }
    }

    ~InputHandler ( void ) {}
    static InputHandler * m_instance;

    void OnKeyDown ( void );
    void OnKeyUp ( void );

    void OnMouseButtonDown ( SDL_Event & event );
    void OnMouseButtonUp ( SDL_Event & event );

    void OnMouseMove ( SDL_Event & event );

    const Uint8 * m_keystates;
    vector<bool> m_mouseButtonStates;

    Vector2D * m_mousePosition;
};

typedef InputHandler TheInputHandler;

#endif /* INPUT_HANDLER_H */