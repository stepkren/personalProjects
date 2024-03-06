#include "GameStateMachine.h"

void GameStateMachine::PushGameState ( GameState * state )
{
    m_gameStates.push_back ( state );

    //  After pushing the game state to the back of the vector call the method after entering
    m_gameStates.back () -> OnEnter ();
}

void GameStateMachine::PopState ( void )
{
    //  Remove game state from the back of the vector
    //  Call the exiting method 
    if ( !m_gameStates.empty () ){
        if ( m_gameStates.back () -> OnExit () ){            
            m_gameStates.pop_back ();
        }
    }
}

void GameStateMachine::ChangeGameState ( GameState * state )
{
    if ( !m_gameStates.empty () ){
        // If the game state we want to change to is the current state of the game do nothing
        if ( m_gameStates.back () -> GetStateID () == state -> GetStateID () ){
            return;
        }
        // If the state we want to exit from exitted without any problems then delete the state from the vector
        if ( m_gameStates.back () -> OnExit () ){
            cout << "deleting state=" << m_gameStates.back() -> GetStateID () << endl;
            m_gameStates.pop_back ();
        }
    }
    //  push back the new state and call the entering method
    m_gameStates.push_back ( state );
    cout << "initialising new state" << state->GetStateID () << endl;
    m_gameStates.back () -> OnEnter ();
}

void GameStateMachine::Update ( void )
{
    //  Update the current game state
    if ( !m_gameStates.empty () ){
        m_gameStates.back () -> Update ();
    }
}

void GameStateMachine::Render ( void )
{
    //  Render the current game state
    if ( !m_gameStates.empty () ){
        m_gameStates.back () -> Render ();
    }
}