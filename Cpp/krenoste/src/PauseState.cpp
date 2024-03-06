#include "PauseState.h"
#include "Game.h"
#include "MenuButton.h"

const string PauseState::m_pauseID = "PAUSE";

//  Clicking exit button quits the game
void PauseState::ExitGame ( void )
{
    cout << "quitting game" << endl;
    TheGame::Instance () -> Quit ();
}

//  CLicking the resume button resumes the game
void PauseState::ResumePlay ( void )
{
    cout << TheGame::Instance () -> GetStateMachine () -> GetSize () << endl; 
    TheGame::Instance () -> GetStateMachine () -> PopState ();
}

//  Update Pause state objects
void PauseState::Update ( void )
{
    for ( vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++ ){
        m_gameObjects[i] -> Update ();
    }
}

//  Render Pause state objects
void PauseState::Render ( void )
{
    for ( vector<GameObject*>::size_type i = 0; i < m_gameObjects.size(); i++ ){
        m_gameObjects[i] -> Draw ();
    }
}

//  Call method when entering pause state
//  loading textures
//  creating game objects
bool PauseState::OnEnter ( void )
{
    if ( !TheTextureManager::Instance () -> Load ( "assets/buttons/ResumeButton.png", "resume_button", TheGame::Instance () -> GetRenderer () ) ){
        return false;
    }

    if ( !TheTextureManager::Instance () -> Load ( "assets/buttons/ExitButton.png", "exit_button", TheGame::Instance () -> GetRenderer () ) ){
        return false;
    }

    LoaderParams params1 ( 512, 196, 256, 128, "resume_button" );
    LoaderParams params2 ( 512, 396, 256, 128, "exit_button" );
    GameObject * button1 = new MenuButton ( params1, ResumePlay, false );
    GameObject * button2 = new MenuButton ( params2, ExitGame, false);

    m_gameObjects.push_back ( button1 );
    m_gameObjects.push_back ( button2 );

    cout << "Entering pause menu..." << endl;
    return true;
}

//  Method called when exiting pause state
//  Clear textures
//  Freeing memory
bool PauseState::OnExit ( void )
{  
    for ( auto obj : m_gameObjects ){
        delete obj;
    }
    m_gameObjects.clear ();
    TheTextureManager::Instance () -> ClearFromTextureMap ( "resume_button" );
    TheTextureManager::Instance () -> ClearFromTextureMap ( "exit_button" );

    TheInputHandler::Instance () -> Reset ();

    cout << "Exiting pause menu..." << endl;
    return true;
}

string PauseState::GetStateID ( void ) const
{
    return m_pauseID;
}