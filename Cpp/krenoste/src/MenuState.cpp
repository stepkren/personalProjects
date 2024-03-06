#include "MenuState.h"
#include "Game.h"
#include "MenuButton.h"

const string MenuState::m_menuID = "MENU";

//  Updating the Menu State objects
void MenuState::Update ( void )
{
    for ( vector<GameObject*>::size_type i = 0; i < m_gameObjects.size (); i++ ){
        //cout << "here" << endl;
        m_gameObjects[i] -> Update ();
    }
}

//  Rendering the Menu State objects
void MenuState::Render ( void )
{
    TheTextureManager::Instance () -> Draw ( "background", 0, 0, 1280, 768, TheGame::Instance () -> GetRenderer () );

    for ( vector<GameObject*>::size_type i = 0; i < m_gameObjects.size (); i++ ){
        m_gameObjects[i] -> Draw ();
    }
}

//  Callback method to change state to Play State
void MenuState::menuToPlay ( void )
{
    cout << "Play button clicked..." << endl;
    TheGame::Instance () -> GetStateMachine () -> ChangeGameState ( new PlayState() );
}

// Callback method to exit game
void MenuState::exitFromMenu ( void )
{
    cout << "Exit button clicked..." << endl;
    TheGame::Instance () -> Quit ();
}

//  Method called when entering menu state
//  Loading textures used in menu
bool MenuState::OnEnter ( void )
{
    if ( !TheTextureManager::Instance () -> Load ( "assets/buttons/PlayButton.png", "play_button", TheGame::Instance () -> GetRenderer () ) ){
        return false;
    }

    if ( !TheTextureManager::Instance () -> Load ( "assets/buttons/ExitButton.png", "exit_button", TheGame::Instance () -> GetRenderer () ) ){
        return false;
    }

    if ( !TheTextureManager::Instance () -> Load ( "assets/Lun_pozadi_2.png", "background", TheGame::Instance () -> GetRenderer () ) ){
        return false;
    }   

    LoaderParams params1 ( 512, 400, 256, 128, "play_button" );
    LoaderParams params2 ( 512, 550, 256, 128, "exit_button" );
    GameObject * button1 = new MenuButton ( params1, menuToPlay, false );
    GameObject * button2 = new MenuButton ( params2, exitFromMenu, false );

    m_gameObjects.push_back ( button1 );
    m_gameObjects.push_back ( button2 );

    cout << m_gameObjects . size() << endl;

    cout << "entering menu state..." << endl;
    return true;
}

// Method called when exiting menu state
// Clearing textures from menu state
bool MenuState::OnExit ( void )
{
    m_gameObjects.clear ();
    TheTextureManager::Instance () -> ClearFromTextureMap ( "play_button" );
    TheTextureManager::Instance () -> ClearFromTextureMap ( "exit_button" );

    cout << "exiting menu state..." << endl;
    return true;
}