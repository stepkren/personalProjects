#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"
#include "GameObject.h"
#include <vector>

class MenuState : public GameState{
public:
    // Constructor
    MenuState ( void )
    : GameState ()
    {}
    ~MenuState ( void ) {}  // Destructor
    
    virtual void Update ( void );   // Updating the Menu State object
    virtual void Render ( void );   // Render the Menu State class objects

    virtual bool OnEnter ( void );  // Call upon entering the menu state
    virtual bool OnExit ( void );   // Call upon exiting the menu state

    virtual string GetStateID ( void ) const { return m_menuID; }

private:
    static const string m_menuID;
    vector<GameObject*> m_gameObjects;  // Menu State object vector

    static void menuToPlay ( void );    // Callback functions to play state
    static void exitFromMenu ( void );  // Callback functions to exit 
};

#endif /* MENU_STATE_H */