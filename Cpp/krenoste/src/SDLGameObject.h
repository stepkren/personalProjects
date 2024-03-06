#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include <string>
#include "GameObject.h"
#include "LoaderParams.h"

// SDL Game Object class 
class SDLGameObject : public GameObject{
public:
    SDLGameObject ( const LoaderParams & parameters );  // Constructor
    virtual ~SDLGameObject ( void ) {}  // Virtual Destructor

    virtual void Update ( void );
    virtual void Draw ( void );
    virtual void Clean ( void );

    virtual void Move ( void ) {}

    Vector2D GetPosition ( void ) const;
    Vector2D GetVelocity ( void ) const;

protected:
    // Member variables
    int m_width;
    int m_height;

    Vector2D m_position;
    Vector2D m_velocity;

    int m_currentRow;
    int m_currentFrame;

    string m_textureID;
};

// Player Character class, derived class of SDL Game Object class
class PlayerCharacter : public SDLGameObject
{
public:
    PlayerCharacter ( const LoaderParams & parameters );    // Constructor

    void Update ( void ) override;  // Method used to Update player character
    void Draw ( void ) override;    // Method used to Render player character
    void Clean ( void ) override;
    void Move ( void ) override;    // Method used to Update player character position

    // Methods used to change or get member variables
    int BricksRemaining ( void ) const; // Getter
    void AddBricks ( void );
    void DecrementBricks ( void );
    void SetBricks ( const int value ) { m_numOfBricks = value; }

    void Shoot ( vector<GameObject*> & shots );

    int HpRemaining ( void ) const { return m_Hp; }
    void Heal ( const int amount );
    void TakeDamage ( const int amount );
    void SetHp ( const int value ) { m_Hp = value; }

    int O2Remaining ( void ) const { return m_O2; }
    void GainO2 ( const int amount );
    void DecrementO2 ( void );
    void SetO2 ( const int value ) { m_O2 = value; }

private:
    int m_numOfBricks;
    int m_Hp;
    int m_O2;
    
    Vector2D * mousePos;
};

//  Enemy Character class, derived from SDL Game Object class
class EnemyCharacter : public SDLGameObject
{
public:
    EnemyCharacter ( const LoaderParams & parameters, bool end );   // Constructor

    void Update ( void ) override;
    void Draw ( void ) override;
    void Clean ( void ) override;

private:
    bool m_reachedEnd;  // bool member variable determining if the enemy should turn around
};
 
class Shot : public SDLGameObject
{
public:
    Shot ( const LoaderParams & parameters );

    void Update ( void ) override;
    void Draw ( void ) override;
    void Clean ( void ) override;

    void SetVelocityX ( const int x );  // set the speed of fired shots

private:
    Vector2D * mousePos;
};

#endif /* SDL_GAME_OBJECT_H */