#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <iostream>
#include <string>
#include "SDLGameObject.h"

using namespace std;

class MenuButton : public SDLGameObject{
public:
    MenuButton ( const LoaderParams & parameters, void (*callback) (), bool released );
    ~MenuButton ( void ) {}

    void Draw ( void );
    void Update ( void );
    void Clean ( void ); 

private:
    //  Integers representing states of button based on mouse position  
    enum button_state{
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void (*m_callback) ( void );    // Callback function ( function pointer )
    bool m_released;
};

#endif /* MENU_BUTTON_H */