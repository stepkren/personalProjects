#include "InputHandler.h"
#include "Game.h"

InputHandler * InputHandler::m_instance = 0;

//	if key is pressed return true 
bool InputHandler::IsKeyDown ( SDL_Scancode key )
{
	if(m_keystates != 0){
		if(m_keystates[key] == 1){
			return true;
		}
		else{
			return false;
		}
	}
	
	return false;    
}

void InputHandler::Update ( void )
{
	SDL_Event event;
	if ( SDL_PollEvent ( &event ) ){
		switch ( event.type ){
			case SDL_QUIT:
				TheGame::Instance () -> Quit ();
				break;
			case SDL_MOUSEBUTTONDOWN:
				OnMouseButtonDown ( event );
				break;
			case SDL_MOUSEBUTTONUP:
				OnMouseButtonUp ( event );
				break;
			case SDL_MOUSEMOTION:
				OnMouseMove ( event );
				break;
		}
	}
}

// if mouse button is pressed return true
void InputHandler::OnMouseButtonDown ( SDL_Event & event )
{
	if ( event.type == SDL_MOUSEBUTTONDOWN ){
		if ( event.button.button == SDL_BUTTON_LEFT ){
			m_mouseButtonStates[LEFT] = true;
		}
		if ( event.button.button == SDL_BUTTON_MIDDLE ){
			m_mouseButtonStates[MIDDLE] = true;
		}
		if ( event.button.button == SDL_BUTTON_RIGHT ){
			m_mouseButtonStates[RIGHT] = true;
		}
	}
}

void InputHandler::OnMouseButtonUp ( SDL_Event & event )
{
	if ( event.type == SDL_MOUSEBUTTONUP ){
		if ( event.button.button == SDL_BUTTON_LEFT ){
			m_mouseButtonStates[LEFT] = false;
		}
		if ( event.button.button == SDL_BUTTON_MIDDLE ){
			m_mouseButtonStates[MIDDLE] = false;
		}
		if ( event.button.button == SDL_BUTTON_RIGHT ){
			m_mouseButtonStates[RIGHT] = false;
		}
	}	
}

//	Set mouse coordinates based on mouse position relative to window
void InputHandler::OnMouseMove ( SDL_Event & event )
{
	m_mousePosition -> setX ( event.motion.x );
	m_mousePosition -> setY ( event.motion.y );
}

bool InputHandler::GetMouseButtonState ( int buttonNumber )
{
	return m_mouseButtonStates[buttonNumber];
}

void InputHandler::Clean ( void )
{

}

//	Set all mouse buttons to false
void InputHandler::Reset ( void )
{
	for ( int i = 0; i < 3; i++ ){
		m_mouseButtonStates[i] = false;
	}
}