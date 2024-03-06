#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"

//  Constructor
MenuButton::MenuButton ( const LoaderParams & parameters, void (*callback) (), bool released )
: SDLGameObject ( parameters ), m_callback ( callback ), m_released ( released )
{
    m_currentFrame = MOUSE_OUT;
}

//  Drawing button objects
void MenuButton::Draw ( void )
{
    SDLGameObject::Draw ();
}

//  Updating button objects appearances based on mouse position
void MenuButton::Update ( void )
{
    Vector2D * mousePos = TheInputHandler::Instance () -> GetMousePosition ();

    if ( mousePos -> getX () < ( m_position.getX () + m_width )
         && mousePos -> getX () > m_position.getX ()
         && mousePos -> getY () < ( m_position.getY () + m_height )
         && mousePos -> getY () > m_position.getY () ){
        
        m_currentFrame = MOUSE_OVER;

        if ( TheInputHandler::Instance () -> GetMouseButtonState ( LEFT ) && m_released ){
            m_currentFrame = CLICKED;

            m_callback ();

            m_released = false;
        }
        else if ( !TheInputHandler::Instance () -> GetMouseButtonState ( LEFT ) ){
            m_released = true;
            m_currentFrame = MOUSE_OVER;
        }
    }
    else{
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::Clean ( void )
{
    SDLGameObject::Clean ();
}