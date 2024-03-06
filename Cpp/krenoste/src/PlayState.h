#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"
#include "SDLGameObject.h"
#include "json.hpp"
#include "Tilemap.h"
#include <vector>

class PlayState : public GameState{
public:
    // Constructor
    PlayState ( void )
    : GameState (), shotPos ( 0, 0 ), m_oxygenDepletion ( 0 ), m_currentFrameHp ( 0 ), m_currentFrameO2 ( 0 )
    {}

    ~PlayState ( void ) {}  // Destructor

    virtual void Update ( void );   // Method used to update play state objects
    virtual void Render ( void );   // Method used to render play state objects

    virtual bool OnEnter ( void );   // Method called when entering play state
    virtual bool OnExit ( void );   // Method called when exiting play state

    virtual string GetStateID ( void ) const { return m_playID; }

    void currentFrameHp ( void );   // set the current frame of png showing health points
    void currentFrameO2 ( void );   // set the current frame of png showing remaining oxygen

private:
    // Member variables
    static const string m_playID;
    vector<GameObject*> m_gameObjects;  // vector storing all play state game objects
    vector<GameObject*> m_shots;    // vector storing all shots
    PlayerCharacter * player;
    Tilemap * m_gameMap;
    Vector2D shotPos;

    int m_oxygenDepletion;

    int m_currentFrameHp;
    int m_currentFrameO2;
};

#endif /* PLAY_STATE_H */