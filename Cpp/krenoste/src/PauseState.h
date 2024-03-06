#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "LoaderParams.h"
#include "GameState.h"
#include "GameObject.h"
#include <vector>

class PauseState : public GameState{
public:
    PauseState ( void ) // Constructor
    : GameState ()
    {}
    ~PauseState ( void ) {} // Destructor

    void Update ( void ) override;  // Update Pause state objects
    void Render ( void ) override;  // Render Pause state objects
    
    bool OnEnter ( void ) override; 
    bool OnExit ( void ) override;

    string GetStateID ( void ) const override;

    size_t getsize ( void ) { return m_gameObjects.size (); }

private:
    static void ExitGame ( void );
    static void ResumePlay ( void );

    static const string m_pauseID;
    vector<GameObject*> m_gameObjects;
};

#endif /* PAUSE_STATE_H */