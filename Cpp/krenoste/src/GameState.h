#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <iostream>

using namespace std;

class GameState{
public:
    GameState ( void ) {}   // Constructor
    virtual ~GameState ( void ) {}  // virtual Destructor

    virtual void Update ( void ) = 0;
    virtual void Render ( void ) = 0;

    virtual bool OnEnter ( void ) = 0;  // Method to be called when entering given game state
    virtual bool OnExit ( void ) = 0;   // Method to be called when leaving given game state

    virtual string GetStateID ( void ) const = 0;
};

#endif /* GAME_STATE_H */