#include "SDLGameObject.h"
#include "Game.h"

// SDL Game Object class constructor
SDLGameObject::SDLGameObject ( const LoaderParams & parameters )
: GameObject ( parameters ), m_position ( parameters . getX (), parameters . getY () ), m_velocity ( 0, 0 )
{
    m_width = parameters . getW ();
    m_height = parameters . getH ();
    m_textureID = parameters . getTexID ();

    m_currentRow = 1;
    m_currentFrame = 0;
}

// Movement of Game Objects
void SDLGameObject::Update ( void )
{
    m_position += m_velocity;
}

// Rendering Game Objects
void SDLGameObject::Draw ( void )
{
    if ( m_velocity.getX () >= 0 ){
        TextureManager::Instance () -> DrawFrame ( m_textureID, m_position.getX (), m_position.getY (), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance() -> GetRenderer () );
    }   
    else{
        TextureManager::Instance () -> DrawFrame ( m_textureID, m_position.getX (), m_position.getY (), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance() -> GetRenderer (), SDL_FLIP_HORIZONTAL );
    }
}

void SDLGameObject::Clean ( void )
{

}

// Player Character class constructor
PlayerCharacter::PlayerCharacter ( const LoaderParams & parameters )
: SDLGameObject::SDLGameObject ( parameters ), m_numOfBricks ( 0 ), m_Hp ( 100 ), m_O2 ( 200 )
{}

//  Method used to set image of player based on movement, setting speed of player
void PlayerCharacter::Update ( void )
{
    m_velocity.setX ( 0 ); m_velocity.setY ( 0 );
    m_currentRow = 4;
    m_currentFrame = int(( SDL_GetTicks () / 150 ) % 2);
    if ( TheInputHandler::Instance() -> IsKeyDown ( SDL_SCANCODE_W ) ){ // When 'W' is pressed move up
        m_currentRow = 3;
        m_velocity.setY ( -1 );
    }
    if ( TheInputHandler::Instance() -> IsKeyDown ( SDL_SCANCODE_S ) ){ // When 'S' is pressed move down
        m_currentRow = 2;
        m_velocity.setY ( 1 );
    }
    if ( TheInputHandler::Instance() -> IsKeyDown ( SDL_SCANCODE_A ) ){ // When 'A' is pressed move left
        m_currentRow = 1;
        m_velocity.setX ( -1 );
    }
    if ( TheInputHandler::Instance() -> IsKeyDown ( SDL_SCANCODE_D ) ){ // When 'D' is pressed move right
        m_currentRow = 1;
        m_velocity.setX ( 1 );
    }
}

// Update the position of the player by velocity
void PlayerCharacter::Move ( void )
{
    m_position += m_velocity;
}

void PlayerCharacter::Draw ( void )
{
    //cout << m_xPos << " " << m_yPos << endl;
    SDLGameObject::Draw ();
}

void PlayerCharacter::Clean ( void )
{
    SDLGameObject::Clean ();
}

// Change player's brick count
void PlayerCharacter::AddBricks ( void )
{
    m_numOfBricks += 20;
}

// Chech amount of bricks player has left
int PlayerCharacter::BricksRemaining ( void ) const
{
    return m_numOfBricks;
}

// When building decrease brick amount by 1
void PlayerCharacter::DecrementBricks ( void )
{
    m_numOfBricks--;
}

// Restore an amount of hitpoints to the player, maximum is 100
void PlayerCharacter::Heal ( const int amount )
{
    m_Hp += amount;
    if ( m_Hp > 100 ){
        m_Hp = 100;
    }
}

// Decrease the amount of player's hitpoints, minumum is 0, the player then dies
void PlayerCharacter::TakeDamage ( const int amount )
{
    m_Hp -= amount;
    if ( m_Hp < 0 ){
        m_Hp = 0;
    }
}

// Restore oxygen
void PlayerCharacter::GainO2 ( const int amount )
{
    m_O2 += amount;
    if ( m_O2 > 200 ){
        m_O2 = 200;
    }
}

// Lose oxygen
void PlayerCharacter::DecrementO2 ( void )
{
    m_O2--;
    if ( m_O2 < 0 ){
        m_O2 = 0;
    }
}

// Shoot laser beam in the direction of the cursor
void PlayerCharacter::Shoot ( vector<GameObject*> & shots )
{
    static bool pressed = false;

    if ( TheInputHandler::Instance () -> IsKeyDown ( SDL_SCANCODE_SPACE ) ){
        if ( !pressed ){
            pressed = true;
            mousePos = TheInputHandler::Instance () -> GetMousePosition ();
            int mouseX = mousePos -> getX ();
            LoaderParams params ( 624, 360, 32, 32, "laserShot" );
            Shot * shot = new Shot ( params );
            if ( mouseX > 640 )
                shot -> SetVelocityX ( 3 );
            else if ( mouseX < 640 )
                shot -> SetVelocityX ( -3 );
            shots.push_back ( shot );
        }
    }
    else{
        pressed = false;
    }
}

Vector2D SDLGameObject::GetVelocity ( void ) const
{
    return m_velocity;
}

Vector2D SDLGameObject::GetPosition ( void ) const
{
    return m_position;
}

// Enemy Character class constructor
EnemyCharacter::EnemyCharacter ( const LoaderParams & parameters, bool end )
: SDLGameObject::SDLGameObject ( parameters ), m_reachedEnd ( end )
{}

void EnemyCharacter::Update ( void )
{
    int ypos = m_position.getY ();
    int xpos = m_position.getX ();
    if ( xpos != 1600 && m_reachedEnd == false ){
        m_velocity.setX (1);
        if ( xpos >= 1600 )
            m_reachedEnd = true;
    }
    if ( xpos >= 1600 && m_reachedEnd == true ){
        m_velocity.setX (-1);
    }
    if ( xpos < -1600 )
        m_reachedEnd = false;

    // Keep enemies at the same position relative to the player 
    if ( TheInputHandler::Instance() -> IsKeyDown ( SDL_SCANCODE_W ) ){
            m_position.setY ( ypos += 4  );
    }
    if ( TheInputHandler::Instance() -> IsKeyDown ( SDL_SCANCODE_S ) ){
            m_position.setY ( ypos -= 4  ); 
    }
    if ( TheInputHandler::Instance() -> IsKeyDown ( SDL_SCANCODE_A ) ){
        if ( m_velocity.getX () == +1 )
            m_position.setX ( xpos += 1  );
        if ( m_velocity.getX () == -1 )
            m_position.setX ( xpos += 1  );            
    }
    if ( TheInputHandler::Instance() -> IsKeyDown ( SDL_SCANCODE_D ) ){
        if ( m_velocity.getX () == +1 )
            m_position.setX ( xpos -= 1 );
        if ( m_velocity.getX () == -1 )
            m_position.setX ( xpos -= 1  );  
    }    

    SDLGameObject::Update();
}

void EnemyCharacter::Draw ( void )
{
    SDLGameObject::Draw ();
}

void EnemyCharacter::Clean ( void )
{
    SDLGameObject::Clean ();
}

Shot::Shot ( const LoaderParams & parameters )
: SDLGameObject::SDLGameObject ( parameters ), mousePos ( nullptr )
{}

void Shot::Update ( void )
{
    SDLGameObject::Update ();
}

void Shot::Draw ( void )
{
    SDLGameObject::Draw ();
}

void Shot::Clean ( void )
{
    SDLGameObject::Clean ();
}

void Shot::SetVelocityX ( const int x )
{
    m_velocity.setX ( x );
}