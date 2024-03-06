#include "Tilemap.h"
#include "Game.h"
#include "InputHandler.h"
#include <math.h>

using json = nlohmann::json;

// Loading tilemap to a 2D integer array
bool Tilemap::loadMatrix ( const char * fileName, PlayerCharacter &player )
{
    // Loading values from configuration file
    ifstream inputFile ( fileName );
    cout << fileName << endl;
    json root;
    inputFile >> root;

    int ofX = root["OFFSETX"];
    int ofY = root["OFFSETY"];
    int MH = root["MAP_HEIGHT"];
    int MW = root["MAP_WIDTH"];
    int HP = root["PLAYER_HP"];
    int O2 = root["PLAYER_O2"];
    int Bricks = root["PLAYER_BRICKS"];
    player.SetHp ( HP );
    player.SetO2 ( O2 );
    player.SetBricks ( Bricks );
    offSetX = ofX;
    offSetY = ofY;
    m_mapHeight = MH;
    m_mapWidth = MW;

    // Initializing 2D tilemap array
    m_tilemap = new int *[m_mapHeight];
    for ( int i = 0; i < m_mapHeight; i++ ){
        m_tilemap[i] = new int[m_mapWidth];
    }  

            /* cout << MH << "    " << MW << endl; */

    // Loading tilemap from saved file                
    const json tileMapArray = root["MAP_TILES"];
    for ( int i = 0; i < m_mapHeight; ++i ){
        const json row = tileMapArray[i];
        for ( int j = 0; j < m_mapWidth; ++j ){
            m_tilemap[i][j] = row[j];
        }
    }  

    inputFile.close(); // Close inputFile

    inputFile = ifstream ( "examples/Monsters.json" );
    inputFile >> root;

    int attackDamage = root["ATTACK"];
    m_attackDamage = attackDamage;    

    // Creating tileset texture
    SDL_Surface * tmpSurface = IMG_Load ( "assets/tiles/Tileset32_2.png" );
    mapTex = SDL_CreateTextureFromSurface ( TheGame::Instance() -> GetRenderer (), tmpSurface );
    SDL_FreeSurface ( tmpSurface );

    return true;
}

// Render tilemap
void Tilemap::Render ( void )
{
    SDL_Rect srcRect, dstRect;

    for ( int i = 0; i < 24; i++ ){
        for ( int j = 0; j < 40; j++ ){
            if ( offSetX < 0 ){
                offSetX = 0;
            }
            if ( offSetX > 98 ){
                offSetX = 98;
            }               
            if ( offSetY < 0 ){
                offSetY = 0;
            }
            if ( offSetY > 98 ){
                offSetY = 98;
            }

    // Getting mouse position
    Vector2D * mousePos = TheInputHandler::Instance () -> GetMousePosition ();
    int mouseX = mousePos -> getY () / 32;
    int mouseY = mousePos -> getX () / 32;
    int before = m_tilemap[mouseX + offSetY][mouseY + offSetX];

    // Highlighting selected tiles in the range of 4 tiles from the player
    if ( ( mousePos -> getX () < 768 && mousePos -> getX () > 512 )
     && ( mousePos -> getY () < 512 && mousePos -> getY () > 256 )  ){
        switch ( m_tilemap[mouseX + offSetY][mouseY + offSetX] ){
            case 17:
                m_tilemap[mouseX + offSetY][mouseY + offSetX] = 28;
                break;
            case 18:
                m_tilemap[mouseX + offSetY][mouseY + offSetX] = 29;
                break;
            case 19:
                m_tilemap[mouseX + offSetY][mouseY + offSetX] = 30;
                break;
            case 20:
                m_tilemap[mouseX + offSetY][mouseY + offSetX] = 31;
                break;       
            default:
                break;        
        }
    }
            srcRect.x = 32 * ( m_tilemap[i + offSetY][j + offSetX] - 17 );
            srcRect.y = 0;
            srcRect.w = srcRect.h = 32;

            dstRect.x = 32 * j;
            dstRect.y = 32 * i;
            dstRect.w = dstRect.h = 32;

            SDL_RenderCopy ( TheGame::Instance () -> GetRenderer (), mapTex, &srcRect, &dstRect );

            m_tilemap[mouseX + offSetY][mouseY + offSetX] = before;
        }
    }       
}

// Update offset of X
void Tilemap::UpdateX ( const int x )
{
    m_sumX += x;
    if ( m_sumX % 8 == 0 && m_sumX != 0 && m_sumX != ( m_sumX - x ) ){
        if ( m_sumX < ( m_sumX - x ) ){
            offSetX--;
        }
        else
            offSetX++;
        return;
    }
}

// Update offset of Y
void Tilemap::UpdateY ( const int y )
{
    m_sumY += y;
    if ( m_sumY % 8 == 0 && m_sumY != 0 && m_sumY != ( m_sumY - y ) ){
        if ( m_sumY < ( m_sumY - y ) ){
            offSetY--;
        }
        else
            offSetY++;     
        return;
    }
}

// When clicked change block to bricks
void Tilemap::UpdateBuild ( PlayerCharacter &player )
{
    Vector2D * mousePos = TheInputHandler::Instance () -> GetMousePosition ();

    int mouseX = mousePos -> getY () / 32;
    int mouseY = mousePos -> getX () / 32;

    // The player cannot build on some blocks
    if ( ( mousePos -> getX () < 768 && mousePos -> getX () > 512 )
       && ( mousePos -> getY () < 512 && mousePos -> getY () > 256 )
       && m_tilemap[mouseX + offSetY][mouseY + offSetX] != 16 + 16
       && m_tilemap[mouseX + offSetY][mouseY + offSetX] != 11 + 16
       && m_tilemap[mouseX + offSetY][mouseY + offSetX] != 10 + 16
       && m_tilemap[mouseX + offSetY][mouseY + offSetX] != 9 + 16
       && m_tilemap[mouseX + offSetY][mouseY + offSetX] != 8 + 16
       && m_tilemap[mouseX + offSetY][mouseY + offSetX] != 5 + 16
       && m_tilemap[mouseX + offSetY][mouseY + offSetX] != 6 + 16
       && m_tilemap[mouseX + offSetY][mouseY + offSetX] != 21 + 16
       && m_tilemap[mouseX + offSetY][mouseY + offSetX] != 22 + 16
       && player.BricksRemaining () > 0 ){
        if ( TheInputHandler::Instance () -> GetMouseButtonState ( RIGHT ) ){
            m_tilemap[mouseX + offSetY][mouseY + offSetX] = 16 + 16;
            player.DecrementBricks ();  // when building one block of bricks decrease the amount of bricks by one
        }
    }
}

// When specific tiles are clicked mine a whole meteorite and gain resources to build with
void Tilemap::UpdateMine ( PlayerCharacter &player )
{
    Vector2D * mousePos = TheInputHandler::Instance () -> GetMousePosition ();

    int mouseX = mousePos -> getY () / 32;
    int mouseY = mousePos -> getX () / 32;

    // When one block is clicked all other around it disappear
    if ( ( mousePos -> getX () < 768 && mousePos -> getX () > 512 )
       && ( mousePos -> getY () < 512 && mousePos -> getY () > 256 ) ){
        if ( TheInputHandler::Instance () -> GetMouseButtonState ( LEFT ) ){
            if ( m_tilemap[mouseX + offSetY][mouseY + offSetX] == 10 + 16 ){
                m_tilemap[mouseX + offSetY][mouseY + offSetX] = 2 + 16;
                m_tilemap[mouseX + offSetY][mouseY + offSetX + 1] = 2 + 16;
                m_tilemap[mouseX + offSetY - 1][mouseY + offSetX + 1] = 2 + 16;
                m_tilemap[mouseX + offSetY - 1][mouseY + offSetX] = 2 + 16;
                player.AddBricks ();
            }
            if ( m_tilemap[mouseX + offSetY][mouseY + offSetX] == 11 + 16 ){
                m_tilemap[mouseX + offSetY][mouseY + offSetX] = 2 + 16;
                m_tilemap[mouseX + offSetY][mouseY + offSetX - 1] = 2 + 16;
                m_tilemap[mouseX + offSetY - 1][mouseY + offSetX - 1] = 2 + 16;
                m_tilemap[mouseX + offSetY - 1][mouseY + offSetX] = 2 + 16;
                player.AddBricks ();
            }
            if ( m_tilemap[mouseX + offSetY][mouseY + offSetX] == 8 + 16 ){
                m_tilemap[mouseX + offSetY][mouseY + offSetX] = 2 + 16;
                m_tilemap[mouseX + offSetY][mouseY + offSetX + 1] = 2 + 16;
                m_tilemap[mouseX + offSetY + 1][mouseY + offSetX + 1] = 2 + 16;
                m_tilemap[mouseX + offSetY + 1][mouseY + offSetX] = 2 + 16;
                player.AddBricks ();
            }
            if ( m_tilemap[mouseX + offSetY][mouseY + offSetX] == 9 + 16 ){
                m_tilemap[mouseX + offSetY][mouseY + offSetX] = 2 + 16;
                m_tilemap[mouseX + offSetY][mouseY + offSetX - 1] = 2 + 16;
                m_tilemap[mouseX + offSetY + 1][mouseY + offSetX - 1] = 2 + 16;
                m_tilemap[mouseX + offSetY + 1][mouseY + offSetX] = 2 + 16;
                player.AddBricks ();
            }                                    
        }
    }
}

// Methods updating the players state
void Tilemap::UpdatePlayer ( PlayerCharacter &player, vector<GameObject*> &objects )
{
    // if hitpoints reach 0 the player dies
    if ( player.HpRemaining () == 0 ){
        // When the player dies delete his saved game
        ifstream copyFile ( "examples/newConfig.json" );
        string inputContent ( ( istreambuf_iterator<char>(copyFile) ), istreambuf_iterator<char> () );
        ofstream outputFile ( "examples/saveConfig.json" );
        outputFile << inputContent;
        copyFile.close();
        outputFile.close();

        cout << "YOU DIED!" << endl;
        TheGame::Instance () -> Quit ();
    }

    // When player collides with an enemy the player takes damage
    for ( size_t i = 0; i < objects.size (); i++ ){
        Vector2D EnemyPos = objects[i] -> GetPosition ();
        if ( EnemyPos.getX () == 640 && EnemyPos.getY () <= 384 && EnemyPos.getY () >=320 ){
            player.TakeDamage ( m_attackDamage );
            cout << "You got hit by a monster, Hp remaining -> " << player.HpRemaining () << endl;
            continue;
        }
    }

    // When players oxygen reaches 0 slowly deplete hitpoints
    if ( player.O2Remaining () == 0 ){
        m_suffocating++;
        if ( m_suffocating % 150 == 0 ){
            player.TakeDamage ( 10 );
            cout << "Not enough O2, HP remaining -> " << player.HpRemaining () << endl;
            m_suffocating %= 150;
        }
    }

    // When standing on magma rapidly deplete hitpoints
    if ( m_tilemap[m_playerPosY + offSetY][ m_playerPosX + offSetX] == 2 + 16 ){
        m_burnt++;        
        if ( m_burnt % 50 == 0 ){
            player.TakeDamage ( 5 );
            cout << "You are standing on magma, HP remaining -> " << player.HpRemaining () << endl;
            m_burnt %= 50;
        }        
    }

    // When player walks over a blue egg spawn a blue monster
    // Also gain 50 oxygen
    if ( m_tilemap[m_playerPosY + offSetY][ m_playerPosX + offSetX] == 21 + 16 ){
        m_tilemap[m_playerPosY + offSetY][ m_playerPosX + offSetX] = 17;
        LoaderParams params ( m_playerPosX * 32 - 32, m_playerPosY * 32 - 96, 64, 64, "blueEnemy" );
        objects.push_back ( new EnemyCharacter ( params, false ) );
        player.GainO2 ( 50 );
    }

    // When player walks over a red egg spawn a red monster
    // Also gain 15 hitpoints
    if ( m_tilemap[m_playerPosY + offSetY][ m_playerPosX + offSetX] == 22 + 16 ){
        m_tilemap[m_playerPosY + offSetY][ m_playerPosX + offSetX] = 17;
        LoaderParams params ( m_playerPosX * 32 - 32, m_playerPosY * 32 - 96, 64, 64, "redEnemy" );
        objects.push_back ( new EnemyCharacter ( params, false ) );
        player.Heal ( 15 );
    }       
}

// Free memory
void Tilemap::Clean ( void ){
    for ( int i = 0; i < m_mapHeight; i++ ){
        delete[] m_tilemap[i];
    }

    delete[] m_tilemap;
}