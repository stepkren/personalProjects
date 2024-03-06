#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include "GameState.h"
#include <vector>

using namespace std;

class GameStateMachine{
public:
    GameStateMachine ( void ) {}
    virtual ~GameStateMachine ( void ) {}

    void PushGameState ( GameState * state );   // Push a gamestate object to the back of the vector
    void ChangeGameState ( GameState * state ); // Change the game state
    void PopState ( void ); // Pop a gamestate object from the back of the vector

    void Update ( void );
    void Render ( void );

    size_t GetSize ( void ) { return m_gameStates.size(); }

private:
    vector<GameState*> m_gameStates;    // Vector of gamestate objects   
};

#endif /* GAME_STATE_MACHINE_H */