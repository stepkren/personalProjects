#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <iostream>
#include <string>

#include "Vector2D.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "LoaderParams.h"

using namespace std;

class GameObject
{
public:
    GameObject ( const LoaderParams & parameters ) {}   // Constructor
    virtual ~GameObject ( void ) {} // virtual Destructor

    virtual void Update ( void ) = 0;
    virtual void Draw ( void ) = 0;
    virtual void Clean ( void ) = 0;
    virtual Vector2D GetVelocity ( void ) const = 0;
    virtual Vector2D GetPosition ( void ) const = 0;

    virtual void Move ( void ) = 0;

protected:
};

#endif /* GAME_OBJECT_H */