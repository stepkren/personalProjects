#include "Vector2D.h"

// Addition operator
Vector2D Vector2D::operator+ ( const Vector2D & Vector )
{
    return Vector2D ( m_xPos + Vector.m_xPos, m_yPos + Vector.m_yPos );
}

// Substraction operator
Vector2D Vector2D::operator- ( const Vector2D & Vector )
{
    return Vector2D ( m_xPos - Vector.m_xPos, m_yPos - Vector.m_yPos );
}

// Multiplier operator
Vector2D Vector2D::operator* ( const double scalar )
{
    return Vector2D ( m_xPos * scalar, m_yPos * scalar );
} 

// Division operator
Vector2D Vector2D::operator/ ( const double scalar )
{
    return Vector2D ( m_xPos / scalar, m_yPos / scalar );    
}

Vector2D & Vector2D::operator+= ( const Vector2D & Vector )
{
    m_xPos += Vector.m_xPos;
    m_yPos += Vector.m_yPos;

    return *this;
}

Vector2D & Vector2D::operator-= ( const Vector2D & Vector )
{
    m_xPos -= Vector.m_xPos;
    m_yPos -= Vector.m_yPos;

    return *this;
}

Vector2D & Vector2D::operator*= ( const double scalar )
{
    m_xPos *= scalar;
    m_yPos *= scalar;

    return *this;
}

Vector2D & Vector2D::operator/= ( const double scalar )
{
    m_xPos /= scalar;
    m_yPos /= scalar;

    return *this;
}

// Return the lenght of a vector
double Vector2D::lenght ( void )
{
    return sqrt ( m_xPos * m_xPos + m_yPos * m_yPos ); 
}

void Vector2D::normaliseVector ( void )
{
    double len = lenght ();
    if ( len > 0 ){
        (*this) *= 1/len;
    }
}