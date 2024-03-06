#include "LoaderParams.h"

LoaderParams::LoaderParams ( int x, int y, int w, int h, string texID )
: m_xPos ( x ), m_yPos ( y ), m_width ( w ), m_height ( h ), m_textureID ( texID )
{}

int LoaderParams::getX ( void ) const
{
    return m_xPos;
}

int LoaderParams::getY ( void ) const
{
    return m_yPos;
}

int LoaderParams::getW ( void ) const
{
    return m_width;
}

int LoaderParams::getH ( void ) const
{
    return m_height; 
}

string LoaderParams::getTexID ( void ) const
{
    return m_textureID;
}