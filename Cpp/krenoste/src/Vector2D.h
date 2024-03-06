#ifndef VECTOR_2D
#define VECTOR_2D

#include <math.h>

// Vector class representing x and y positions
class Vector2D{
public:
    // Constructor
    Vector2D ( const double x, const double y )
    : m_xPos ( x ), m_yPos ( y )
    {}

    ~Vector2D ( void ) {} // Destructor

    // Getters
    double getX ( void ) const { return m_xPos; }
    double getY ( void ) const { return m_yPos; }
    void setX ( const double X ) { m_xPos = X; }
    void setY ( const double Y ) { m_yPos = Y; }

    // Operators
    Vector2D operator+ ( const Vector2D & Vector );
    Vector2D operator- ( const Vector2D & Vector );
    Vector2D operator* ( const double scalar );
    Vector2D operator/ ( const double scalar );

    Vector2D &operator+= ( const Vector2D & Vector );
    Vector2D &operator-= ( const Vector2D & Vector );
    Vector2D &operator*= ( const double scalar );
    Vector2D &operator/= ( const double scalar );

    void normaliseVector ( void );
    double lenght ( void );

private:
    // Member variables
    double m_xPos;
    double m_yPos;
};

#endif /* VECTOR_2D */