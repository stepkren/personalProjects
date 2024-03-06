#ifndef LOAD_PARAMETERS_H
#define LOAD_PARAMETERS_H

#include <string>

using namespace std;

class LoaderParams{
public:
    LoaderParams ( int x, int y, int w, int h, string texID );
    ~LoaderParams ( void ) {}

    //  Getters
    int getX ( void ) const;
    int getY ( void ) const;
    int getW ( void ) const;
    int getH ( void ) const;

    string getTexID ( void ) const;
private:
    //  Member variables  
    int m_xPos;
    int m_yPos;
    int m_width;
    int m_height;

    string m_textureID;
};

#endif /* LOAD_PARAMETERS_H */