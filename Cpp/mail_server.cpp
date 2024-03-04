#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// Own implementation of a string 
class MyString
{
    public:
        // MyString class constructor
        MyString ( void )
        : m_length ( 0 ), m_max ( 0 ), str ( nullptr ) {}

        // MyString class destructor
        ~MyString ( void ) {
            delete[] str;
            m_length = 0;
            m_max = 0;
        }

        // MyString class constructor
        MyString ( const char * Str )
        : m_length ( strlen( Str ) ), m_max ( m_length + 1 ), str ( new char[m_max] ) {
            memcpy ( str, Str, m_length + 1 );
        }

        /**
         * Copy constructor.
         * 
         * @param Str A MyString class object to be copied
        */
        MyString ( const MyString &Str )
        : m_length ( Str . m_length ), m_max ( Str . m_max ), str ( new char[m_max] ) {
            memcpy ( str, Str . str, m_length + 1 );
        }

        /**
         * Assignment operator for assigning a C-style string to a MyString object.
         * 
         * @param Str The C-style string to assign
         * @return A reference to the modified MyString object
        */
        MyString &operator= ( const char * Str ) {
            delete[] str;
            m_length = strlen( Str );
            m_max = m_length + 1;
            str = new char[ m_max ];
            memcpy ( str, Str, m_length + 1 );   
            return *this;
        }

        /**
         * Assignment operator for assigning a MyString object to another MyString object.
         * 
         * @param Str The MyString object to assign
        */
        MyString &operator= ( const MyString &Str ) {
            if ( &Str != this )
            {
                delete[] str;
                m_length = Str . m_length;
                m_max = Str . m_max;                
                str = new char[m_max];
                memcpy ( str, Str . str, m_length + 1 );
            }            
            return *this;
        }

        /**
         * Equality comparison operator for comparing a MyString object with a C-style string.
         * 
         * @param Str The C-style string to compare
         * @return True if the MyString object is equal to the input string, False otherwise
        */
        bool operator== ( const char * Str ) const {
            if ( strcmp ( str, Str ) == 0 )
                return true;
            return false;
        }

        /**
         * Equality comparison operator for comparing a MyString object with another MyString object.
         * 
         * @param Str The MyString object to be compared
         * @return True if the MyString object is equal to the input MyString object
        */
        bool operator== ( const MyString &Str ) const {
            if ( strcmp ( str, Str . str ) == 0 )
                return true;
            return false;
        } 

    private:    
        int m_length, m_max;
        char * str;
        friend class CMail;
};
 
class CMail
{
  public:
    // Default constructor of the CMail class
    CMail ( void ) {}

    /**
     * Constructor of the CMail class.
     * 
     * @param from The sender of the CMail object
     * @param to The recipient of the CMail object
     * @param body The body of the mail
    */
    CMail ( const char * from, const char * to, const char * body )
    : sender ( from ), recipient ( to ), message ( body ) {}

    /**
     * An assignment operator for assigning one CMail object to another.
     * 
     * @param other The CMail object to assign
     * @return A reference to the modified CMail object
    */
    CMail &operator= ( const CMail &other ) {
        sender = other . sender;
        recipient = other . recipient;
        message = other . message;

        return *this;
    }                                                  

    /**
     * Equality comparison operator for comparing two CMail objects.
     * 
     * @param x The CMail object to compare
     * @return True if the sender, recipient and body of both CMail objects are equal, False otherwise
    */
    bool operator == ( const CMail & x ) const {
        if ( ( strcmp ( sender . str, x . sender . str ) == 0 ) && ( strcmp ( recipient . str, x . recipient . str ) == 0 ) && ( strcmp ( message . str, x . message . str ) == 0 ) )
            return true;
        return false;
    }

    /**
     * Overloaded output stream insertion operator for outputting a CMail object to an output stream.
     * 
     * @param os The output stream
     * @param m The CMail object to output
     * @return The modified output stream
    */
    friend ostream & operator << ( ostream & os, const CMail & m ) {
        m . printMyString ( os );
        return os;
    }

  private:

    /**
     * Prints the CMail object and all of it's details.
     * 
     * @param os The output stream to output to
    */
    void printMyString ( ostream &os ) const {
        os << "From: " << sender . str << ", To: " << recipient . str << ", Body: " << message . str;        
    }

    MyString sender, recipient, message;
    friend class CMailServer;
    friend class CMailIterator;
};

// Own implementation of a vector
class Vector
{
    public:
        // Default constructor of the Vector class
        Vector ( void )
        : m_data ( nullptr ), m_cap ( 0 ), m_cnt ( 0 ) {}

        /**
         * Assignment operator for assigning a Vector object to another Vector object.
         * 
         * @param other The Vector object to assign
         * @return A reference to the modified Vector object
        */
        Vector &operator= ( const Vector & other ) {
            if ( m_cnt > 0 )
                clear();
            for ( size_t i = 0; i < other.m_cnt; i++ ){
                this -> push_back ( other[i] );
            }
            return *this;
        }

        // Destructor of the Vector class
        ~Vector ( void ) { delete[] m_data; m_cap = 0; m_cnt = 0; }

        /**
         * Adds a CMail object to the end of the Vector.
         * 
         * @param mail The CMail object to be added
        */
        void push_back ( const CMail &mail ) {
            if ( m_cap == m_cnt ){
                m_cap = ( m_cap * 2 ) + 2;
                CMail * tmp = new CMail[m_cap];
                for ( size_t i = 0; i < m_cnt; i++ ){
                    tmp[i] = m_data[i];
                }
                if ( m_cnt > 0 )
                    delete[] m_data;
                m_data = tmp;
            }
            m_data[m_cnt++] = mail;
        }

        // Deletes all the data from the Vector.
        void clear ( void ) {
            delete[] m_data;
            m_cap = 0;
            m_cnt = 0;
        }

        /**
         * Checks if the Vector is empty.
         * 
         * @return True if the Vector is empty, False otherwise
        */
        bool empty ( void ) const {
            if ( m_cnt > 0 )
                return false;
            return true;
        }

        /**
         * Returns the size of the Vector.
         * 
         * @return The size of the Vector
        */
        size_t size ( void ) const {
            return m_cnt;
        }

        /**
         * Access operator for accessing elements of the CMail collection at a specified position.
         * 
         * @param pos The position of the element to access
         * @return A reference to the CMail object at the specified position
        */
        CMail &operator[] ( const size_t pos ) const {
            return m_data[pos];
        } 

        /**
         * Equality comparison operator for comparing two Vector objects.
         * 
         * @param other The Vector object to compare
         * @return True if the two Vector objects are equal, False otherwise
        */
        bool operator== ( const Vector &other ) const {
            if ( m_cnt != other . m_cnt )
                return false;
            for ( size_t i = 0; i < other . m_cnt; i++ ){
                if ( ! ( m_data[i] == other . m_data[i] ) )
                    return false;
            }
            return true;
        }

    private:
        CMail * m_data;
        size_t m_cap, m_cnt;            
};

class CMailIterator 
{
  public:
    // Default CMailIterator class constructor
    CMailIterator ( void )
    : m_it ( 0 ) {}

    /**
     * Conversion operator to bool.
     * 
     * @return True if the iterator position is within the range of sentEmails, False otherwise
    */
    explicit operator bool ( void ) const {
        if ( m_it < sentEmails . size() )
            return true;
        return false;
    }

    /**
     * Logical NOT operator for checking the validity of the iterator. 
     * 
     * @return True if the iterator is at the end of the sentEmails container, False otherwise
    */
    bool operator ! ( void ) const {
        if ( m_it < sentEmails . size() )
            return false;
        return true;
    }
    
    /**
     * Dereference operator for accessing the element at the iterator's current position.
     * 
     * @return A const reference to the CMail object at the iterator's current position 
    */
    const CMail & operator * ( void ) const {
        return sentEmails[m_it];
    }

    /**
     * Prefix increment operator for advancing the iterator to the next position.
     * 
     * @return A reference to the modified CMailIterator object
    */
    CMailIterator & operator ++ ( void ) {
        ++m_it;
        return *this;
    }

  private:
    size_t m_it;
    Vector sentEmails;
    friend class CMailServer;
};



class CMailServer 
{
  public:
    // Default constructor for the CMailServer class.
    CMailServer                   ( void ) {}

    // Destructor for the CMailServer class.
    ~CMailServer                  ( void ) {}

    /**
     * Copy constructor for the CMailServer class.
     *
     * @param src The CMailServer object to copy from
    */                             
    CMailServer ( const CMailServer & src ) {
        *this = src;
    }

    /**
     * Assignment operator for assigning a CMailServer object to another CMailServer object.
     * 
     * @param src The CMailServer to assign
     * @return A reference to the modified CMailServer object
    */
    CMailServer & operator = ( const CMailServer & src ) {
        if ( ! ( mailserver == src . mailserver ) )
            mailserver = src . mailserver;
        return *this;
    }

    /**
     * Adds a CMail object to the 'mailserver' vector.
     * 
     * @param m The CMail object to be added to the vector
    */
    void sendMail ( const CMail & m ) {
        mailserver . push_back ( m );
    }

    /**
     * Will make available emails sent from the specified email address.
     * 
     * @param email The email address the mails were sent from
     * @return CMailIterator object
    */
    CMailIterator outbox ( const char * email ) const {
        CMailIterator tmp;
        for ( size_t i = 0; i < mailserver . size(); i++ ){
            if ( mailserver[i] . sender == email )
                tmp . sentEmails . push_back ( mailserver[i] );
        }
        return tmp;
    }

    /**
     * Will make available emails sent to the specified email address.
     * 
     * @param email The email address the mails were sent to
     * @return CMailIterator object
    */
    CMailIterator inbox ( const char * email ) const {
        CMailIterator tmp;
        for ( size_t i = 0; i < mailserver . size(); i++ ){
            if ( mailserver[i] . recipient == email )
                tmp . sentEmails . push_back ( mailserver[i] );
        }
        return tmp;
    }
  
  private:
    Vector mailserver;
};

bool matchOutput ( const CMail & m, const char * str ) {
  ostringstream oss;
  oss << m;
  return oss . str () == str;
}

int main ( void )
{
  char from[100], to[100], body[1024];

  assert ( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "peter", "progtest deadline" ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "progtest deadline", "peter" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "john", "progtest deadline" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "progtest deadline", "john" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "john", "peter" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "peter", "john" ) ) );
  CMailServer s0;
  s0 . sendMail ( CMail ( "john", "peter", "some important mail" ) );
  strncpy ( from, "john", sizeof ( from ) );
  strncpy ( to, "thomas", sizeof ( to ) );
  strncpy ( body, "another important mail", sizeof ( body ) );
  s0 . sendMail ( CMail ( from, to, body ) );
  strncpy ( from, "john", sizeof ( from ) );
  strncpy ( to, "alice", sizeof ( to ) );
  strncpy ( body, "deadline notice", sizeof ( body ) );
  s0 . sendMail ( CMail ( from, to, body ) );
  s0 . sendMail ( CMail ( "alice", "john", "deadline confirmation" ) );
  s0 . sendMail ( CMail ( "peter", "alice", "PR bullshit" ) );
  CMailIterator i0 = s0 . inbox ( "alice" );
  assert ( i0 && *i0 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i0,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i0 && *i0 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i0,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ! ++i0 );

  CMailIterator i1 = s0 . inbox ( "john" );
  assert ( i1 && *i1 == CMail ( "alice", "john", "deadline confirmation" ) );
  assert ( matchOutput ( *i1,  "From: alice, To: john, Body: deadline confirmation" ) );
  assert ( ! ++i1 );

  CMailIterator i2 = s0 . outbox ( "john" );
  assert ( i2 && *i2 == CMail ( "john", "peter", "some important mail" ) );
  assert ( matchOutput ( *i2,  "From: john, To: peter, Body: some important mail" ) );
  assert ( ++i2 && *i2 == CMail ( "john", "thomas", "another important mail" ) );
  
  assert ( matchOutput ( *i2,  "From: john, To: thomas, Body: another important mail" ) );
  assert ( ++i2 && *i2 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i2,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ! ++i2 );

  CMailIterator i3 = s0 . outbox ( "thomas" );
  assert ( ! i3 );

  CMailIterator i4 = s0 . outbox ( "steve" );
  assert ( ! i4 );

  CMailIterator i5 = s0 . outbox ( "thomas" );
  s0 . sendMail ( CMail ( "thomas", "boss", "daily report" ) );
  assert ( ! i5 );

  CMailIterator i6 = s0 . outbox ( "thomas" );
  assert ( i6 && *i6 == CMail ( "thomas", "boss", "daily report" ) );
  assert ( matchOutput ( *i6,  "From: thomas, To: boss, Body: daily report" ) );
  assert ( ! ++i6 );

  CMailIterator i7 = s0 . inbox ( "alice" );
  s0 . sendMail ( CMail ( "thomas", "alice", "meeting details" ) );
  assert ( i7 && *i7 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i7,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i7 && *i7 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i7,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ! ++i7 );

  CMailIterator i8 = s0 . inbox ( "alice" );
  assert ( i8 && *i8 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i8,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i8 && *i8 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i8,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i8 && *i8 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i8,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ! ++i8 );

  CMailServer s1 ( s0 );
  s0 . sendMail ( CMail ( "joe", "alice", "delivery details" ) );
  s1 . sendMail ( CMail ( "sam", "alice", "order confirmation" ) );
  CMailIterator i9 = s0 . inbox ( "alice" );
  assert ( i9 && *i9 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i9,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i9 && *i9 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i9,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i9 && *i9 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i9,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ++i9 && *i9 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( matchOutput ( *i9,  "From: joe, To: alice, Body: delivery details" ) );
  assert ( ! ++i9 );

  CMailIterator i10 = s1 . inbox ( "alice" );
  assert ( i10 && *i10 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i10,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i10 && *i10 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i10,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i10 && *i10 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i10,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ++i10 && *i10 == CMail ( "sam", "alice", "order confirmation" ) );
  assert ( matchOutput ( *i10,  "From: sam, To: alice, Body: order confirmation" ) );
  assert ( ! ++i10 );

  CMailServer s2;
  s2 . sendMail ( CMail ( "alice", "alice", "mailbox test" ) );
  CMailIterator i11 = s2 . inbox ( "alice" );
  assert ( i11 && *i11 == CMail ( "alice", "alice", "mailbox test" ) );
  assert ( matchOutput ( *i11,  "From: alice, To: alice, Body: mailbox test" ) );
  assert ( ! ++i11 );

  s2 = s0;
  s0 . sendMail ( CMail ( "steve", "alice", "newsletter" ) );
  s2 . sendMail ( CMail ( "paul", "alice", "invalid invoice" ) );
  CMailIterator i12 = s0 . inbox ( "alice" );
  assert ( i12 && *i12 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i12,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i12 && *i12 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i12,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i12 && *i12 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i12,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ++i12 && *i12 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( matchOutput ( *i12,  "From: joe, To: alice, Body: delivery details" ) );
  assert ( ++i12 && *i12 == CMail ( "steve", "alice", "newsletter" ) );
  assert ( matchOutput ( *i12,  "From: steve, To: alice, Body: newsletter" ) );
  assert ( ! ++i12 );

  CMailIterator i13 = s2 . inbox ( "alice" );
  assert ( i13 && *i13 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i13,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i13 && *i13 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i13,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i13 && *i13 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i13,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ++i13 && *i13 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( matchOutput ( *i13,  "From: joe, To: alice, Body: delivery details" ) );
  assert ( ++i13 && *i13 == CMail ( "paul", "alice", "invalid invoice" ) );
  assert ( matchOutput ( *i13,  "From: paul, To: alice, Body: invalid invoice" ) );
  assert ( ! ++i13 );

  return EXIT_SUCCESS;
}