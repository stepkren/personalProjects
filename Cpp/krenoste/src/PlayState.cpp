#include "PlayState.h"
#include "PauseState.h"
#include "Game.h"

using json = nlohmann::json;

const string PlayState::m_playID = "PLAY";

// function used to save the game stats
// when saving all enemies despawn
void SaveGame ( const string & fileName, int Hp, int O2, int Blocks, int ** tilemap, int offsetX, int offsetY )
{
    json gameState;
    json tileMapArray;
    gameState["PLAYER_HP"] = Hp;
    gameState["PLAYER_O2"] = O2;
    gameState["PLAYER_BRICKS"] = Blocks;
    gameState["MAP_HEIGHT"] = 122;
    gameState["MAP_WIDTH"] = 138;
    for ( int i = 0; i < 122; ++i ){
        json row;
        for ( int j = 0; j < 138; ++j ){
            row.push_back( tilemap[i][j] );
        }
        tileMapArray.push_back ( row );
    }
    gameState["MAP_TILES"] = tileMapArray;
    gameState["OFFSETX"] = offsetX;
    gameState["OFFSETY"] = offsetY;

    ofstream saveFile ( fileName );
    saveFile << gameState;
    saveFile.close();
}

//  Method used to Update all play state game objects
void PlayState::Update ( void )
{
    //  Whenever escape is pressed save the game and open a pause menu
    if ( TheInputHandler::Instance () -> IsKeyDown ( SDL_SCANCODE_ESCAPE ) ){
        SaveGame ( "examples/saveConfig.json", player -> HpRemaining(), player -> O2Remaining (), player -> BricksRemaining (), m_gameMap -> GetTileMap (), m_gameMap -> GetOffSetX (), m_gameMap -> GetOffSetY () );
        TheGame::Instance () -> GetStateMachine () -> PushGameState ( new PauseState () );
    }

    Vector2D playerVelocity = player -> GetVelocity ();
    Vector2D playerPos = player -> GetPosition ();

    //  Timer for taking damage when oxygen is at 0
    m_oxygenDepletion++;
    if ( m_oxygenDepletion % 150 == 0 ){
        player -> DecrementO2 ();   // Decrease oxygen by 1
        m_oxygenDepletion %= 150;
        cout << "Remaining oxygen = " << player -> O2Remaining () << endl;
    }

    //  calling methods updating the map and the player
    m_gameMap -> UpdateBuild ( *player );
    m_gameMap -> UpdateMine ( *player );
    m_gameMap -> UpdatePlayer ( *player, m_gameObjects );
    m_gameMap -> UpdateX ( playerVelocity.getX () );
    m_gameMap -> UpdateY ( playerVelocity.getY () );
    player -> Update ();
    player -> Shoot ( m_shots );

    //  Updating, Rendering and Freeing shots from the shots vector
    for ( size_t i = 0; i < m_shots.size(); i++ ){
        shotPos = m_shots[i]->GetPosition();
        m_shots[i] -> Update ();
        m_shots[i] -> Draw ();
        if ( m_shots[i]->GetPosition().getX() > 1500 ){
            delete m_shots[i];
            m_shots.erase ( m_shots.begin() + i );
            continue;
        }
    }

    //  Checking for collisions of bullets with enemies
    for ( vector<GameObject*>::size_type i = 0; i < m_gameObjects.size (); i++ ){
        m_gameObjects[i] -> Update ();
        for ( size_t j = 0; j < m_shots.size(); j++ ){
            shotPos = m_shots[j]->GetPosition();
            if ( shotPos.getX () <= m_gameObjects[i]->GetPosition().getX() && shotPos.getX () >= m_gameObjects[i]->GetPosition().getX() - 64
               && shotPos.getY () - 16 <= m_gameObjects[i]->GetPosition().getY() && shotPos.getY () - 16 >= m_gameObjects[i]->GetPosition().getY() - 64 ){
                delete m_gameObjects[i];
                m_gameObjects.erase ( m_gameObjects.begin () + i );
                break;
            }            
        }        
    }
}

//  Method used to render all play state game objects
void PlayState::Render ( void )
{
    //  Rendering the tilemap
    m_gameMap -> Render ();
    //  Displaying brick count
    TheTextureManager::Instance () -> Draw ( "bricksCounter", 10, 10, 64, 64, TheGame::Instance () -> GetRenderer () );

    TTF_Font * font = TTF_OpenFont ( "assets/fonts/VT323-Regular.ttf", 48 );
    SDL_Surface * tmpSurface = TTF_RenderText_Solid ( font, (to_string( player -> BricksRemaining () )).c_str(), {255, 255, 255} );
    SDL_Texture * fontTexture = SDL_CreateTextureFromSurface ( TheGame::Instance () -> GetRenderer (), tmpSurface );
    SDL_FreeSurface ( tmpSurface );
    TTF_CloseFont ( font );

    SDL_Rect textRect;
    textRect.x = 22;
    textRect.y = 18;
    SDL_QueryTexture ( fontTexture, nullptr, nullptr, &textRect.w, &textRect.h );
    SDL_RenderCopy ( TheGame::Instance () -> GetRenderer (), fontTexture, nullptr, &textRect ); //  Rendering brick count

    currentFrameHp();   // Calculating current frame of hitpoints image to be displayed 
    TheTextureManager::Instance () -> DrawFrame ( "hitpoints",  100, 10, 32, 32, 1, m_currentFrameHp, TheGame::Instance () -> GetRenderer () );
    currentFrameO2();   // Calculating current frame of oxygen image to be displayed 
    TheTextureManager::Instance () -> DrawFrame ( "oxygen",  100, 45, 32, 32, 1, m_currentFrameO2, TheGame::Instance () -> GetRenderer () );

    //  Rendering shots
    if ( m_shots.size() > 0 ){
        for ( size_t i = 0; i < m_shots.size(); i++ ){
            m_shots[i] -> Draw ();
        }
    }

    //  Rendering enemies
    for ( size_t i = 0; i < m_gameObjects.size (); i++ ){
        m_gameObjects[i] -> Draw ();
    }    

    player -> Draw ();  // Rendering player
}

void PlayState::currentFrameHp ( void )
{
    if ( player -> HpRemaining () > 66 ){
        m_currentFrameHp = 0;
    }
    else if ( player -> HpRemaining () > 33 ){
        m_currentFrameHp = 1;
    }
    else if ( player -> HpRemaining () > 0 ){
        m_currentFrameHp = 2;
    }
}

void PlayState::currentFrameO2 ( void )
{
    if ( player -> O2Remaining () > 135 ){
        m_currentFrameO2 = 0;
    }
    else if ( player -> HpRemaining () > 68 ){
        m_currentFrameO2 = 1;
    }
    else if ( player -> HpRemaining () > 0 ){
        m_currentFrameO2 = 2;
    }
    else if ( player -> HpRemaining () == 0 ){
        m_currentFrameO2 = 3;
    }        
}

// Loading all textures
// Creating player object
bool PlayState::OnEnter ( void )
{
    if ( !TheTextureManager::Instance () -> Load ( "assets/characters/player_animated_2.png", "player", TheGame::Instance () -> GetRenderer () ) ){
        return false;
    }

    if ( !TheTextureManager::Instance () -> Load ( "assets/misc/BricksCounter.png", "bricksCounter", TheGame::Instance () -> GetRenderer () ) ){
        return false;
    }

    if ( !TheTextureManager::Instance () -> Load ( "assets/misc/LifeState.png", "hitpoints", TheGame::Instance () -> GetRenderer () ) ){
        return false;
    }

    if ( !TheTextureManager::Instance () -> Load ( "assets/misc/OxygenState.png", "oxygen", TheGame::Instance () -> GetRenderer () ) ){
        return false;
    }            

    if ( !TheTextureManager::Instance () -> Load ( "assets/enemies/vobluda_64_attack.png", "blueEnemy", TheGame::Instance () -> GetRenderer () ) ){
        return false;
    }

    if ( !TheTextureManager::Instance () -> Load ( "assets/enemies/vobluda_2_attack.png", "redEnemy", TheGame::Instance () -> GetRenderer () ) ){
        return false;
    } 

    if ( !TheTextureManager::Instance () -> Load ( "assets/misc/strela.png", "laserShot", TheGame::Instance () -> GetRenderer () ) ){
        return false;
    }   

    cout << "Textures loaded... ( player & tileset )" << endl;    

    m_gameMap = new Tilemap ();

    ifstream file ( "examples/filePath.txt" );
    string filePath;
    getline ( file, filePath );
    file.close();

    LoaderParams params1 ( 608, 352, 64, 64, "player" );
    player =  new PlayerCharacter ( params1 );

    m_gameMap -> loadMatrix ( filePath.c_str(), *player );  // Loading tilemap

    //m_gameObjects.push_back ( player );
    cout << "number of game objects in play state:" << m_gameObjects.size() << endl;
    cout << "entering play state..." << endl;    
    return true;
}

// Freeing memory, clearing textures
bool PlayState::OnExit ( void )
{
    for ( vector<GameObject*>::size_type i = 0; i < m_gameObjects.size (); i++ ){
        m_gameObjects[i] -> Clean ();
    }
    m_gameObjects.clear ();
    TheTextureManager::Instance () -> ClearFromTextureMap ( "player" );

    m_gameMap -> Clean ();

    cout << "exiting play state..." << endl;
    return true;
}