#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <typeinfo>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <algorithm>
#include <type_traits>
using namespace std;

class CRect 
{
    public:
        // Constructor for the CRect class.
        CRect ( double x, double y, double w, double h )
        : m_X ( x ), m_Y ( y ), m_W ( w ), m_H ( h ) {}

        /**
         * Friend function for overloading the '<<' operator to enable outputting the details of a CRect object to an output stream. 
         * 
         * @param os The output stream
         * @param x The CRect object whose details will be written to the output stream
         * @return A reference to the output stream
        */
        friend ostream & operator << ( ostream & os, const CRect & x ) {
        return os << '(' << x . m_X << ',' << x . m_Y << ',' << x . m_W << ',' << x . m_H << ')';
        }

        double                   m_X;
        double                   m_Y;
        double                   m_W;
        double                   m_H;
};

class CDWindow
{
    public:
        // Constructor for the CDWindow class.
        CDWindow ( int id, const CRect & relPos )
        : m_id ( id ), m_APos ( relPos ), m_RPos ( relPos ) {}

        // Constructor fot the CDWindow class.
        CDWindow ( int id, const CRect & absPos, const CRect & relPos )
        : m_id ( id ), m_APos ( absPos ), m_RPos ( relPos ) {}

        // Abstract method
        virtual shared_ptr<CDWindow> p_copy ( void ) const = 0;

        /**
         * Prints the details of a CDWindow object to an output stream.
         * 
         * @param os The output stream
         * @param flag A flag parameter
        */
        virtual void printCDWindow ( ostream & os, int flag = 0 ) const {
            os << *this;
        }

        /**
         * Friend function for overloading the '<<' operator to enable outputting the details of a CDWindow object to an output stream.
         * 
         * @param os The output stream
         * @param x The CDWindow object whose details will be written to the output stream
         * @return A reference to the output stream
        */
        friend ostream &operator<< ( ostream & os, const CDWindow & x )
        {
            x . printCDWindow( os, 0 );
            return os;
        }

    protected:
        int m_id;
        CRect m_APos;
        CRect m_RPos;
        friend class CWindow;
};

class CWindow
{
    public:
        // Constructor for the CWindow class.
        CWindow ( int id, const string & title, const CRect & absPos )
        : m_id ( id ), m_text ( title ), m_APos ( absPos ) {}

        // Copy constructor for the CWindow class.
        CWindow ( const CWindow & other )
        : m_id ( other . m_id ), m_text ( other . m_text ), m_APos ( other . m_APos )
        {
            for ( size_t i = 0; i < other . ptrs . size(); i++ ){
                ptrs . push_back ( other . ptrs[i] -> p_copy() );
            }
        }                                                                                          

        /**
         * Method calculating the new position of the CDWindow object.
         * 
         * @param tmp A shared pointer to the CDWIndow object for which the position will be calculated
        */
        void calculatePos ( shared_ptr<CDWindow> tmp ) {
            tmp -> m_APos . m_X = m_APos . m_W * tmp -> m_RPos . m_X + m_APos . m_X;
            tmp -> m_APos . m_Y = m_APos . m_H * tmp -> m_RPos . m_Y + m_APos . m_Y;
            tmp -> m_APos . m_W = m_APos . m_W * tmp -> m_RPos . m_W;
            tmp -> m_APos . m_H = m_APos . m_H * tmp -> m_RPos . m_H;        
        }

        /**
         * Adds a CDWindow to the current CWindow, performing necessary calculations for its position. 
         * 
         * @param x The CDWindow object to be added to the CWindow
         * @return A reference to the modified CWindow
        */
        CWindow &add ( const CDWindow & x ) {
            shared_ptr<CDWindow> tmp ( x . p_copy() );
            calculatePos ( tmp );
            ptrs . push_back ( tmp );
            return *this;
        }

        /**
         * Searches for the CDWindow with the specified ID in the list of CDWindows. 
         * 
         * @param id The ID of the CDWindow to search for
         * @return A reference to the shared pointer to the found CDWindow, or a reference to the first CDWindow if not found
        */
        shared_ptr<CDWindow> &search ( const int id ) {
            for ( size_t i = 0; i < ptrs . size(); i++ ){
                if ( id == ptrs[i] -> m_id ){
                    return ptrs[i];
                }
            }
            return ptrs[0];
        }

        /**
         * Sets the position and dimensions of the CWindow object and recalculates positions of all associated CDWindows.  
         * 
         * @param newAPos The new position and dimensions (CRect) to set for the CWindow
        */
        void setPosition ( const CRect & newAPos) {
            m_APos . m_X = newAPos . m_X;
            m_APos . m_Y = newAPos . m_Y;
            m_APos . m_W = newAPos . m_W;
            m_APos . m_H = newAPos . m_H;

            for ( size_t i = 0; i < ptrs . size(); i++ ){
                calculatePos ( ptrs[i] );
            }
        }

        /**
         * Prints the CWindow object.
         * 
         * @param os The output stream
         * @param flag A flag parameter
        */
        void printCWindow ( ostream &os, const int flag ) const {
            os << "[" << m_id << "]" << " Window" << " \"" << m_text << "\" " << m_APos << endl;
            for ( size_t i = 0; i < ptrs . size(); i++ ){
                if ( i == ptrs . size() - 1 ){
                    os << "+- ";
                    ptrs[i] -> printCDWindow ( os, 1 );
                }
                else{
                    os << "+- ";
                    ptrs[i] -> printCDWindow ( os, 2 );
                }
            }
        }

        /**
         * Friend function for overloading the '<<' operator to enable outputting the details of a CWindow object to an output stream.
         * 
         * @param os The output stream
         * @param x The CWindow object whose details will be written to the output stream
         * @return
        */
        friend ostream &operator<< ( ostream &os, const CWindow & x ) {
            x . printCWindow ( os, 0 );
            return os;
        }

    private:
        int m_id;
        string m_text;
        CRect m_APos;
        vector<shared_ptr<CDWindow>> ptrs;
};

/**
 * CButton - derived class
 * CDWindow - base class
 *
 * CButton class represents a button. 
*/
class CButton : public CDWindow
{
    public:
        // Constructor for the CButton class
        CButton ( int id, const CRect & relPos, const string & name )
        : CDWindow ( id, relPos ), m_text ( name ) {}

        // Constructor for the CButton class
        CButton ( const CButton & other )
        : CDWindow ( other . m_id, other . m_APos, other . m_RPos ), m_text ( other . m_text ) {}

        /**
         * Creates a copy of the CDWindow object using shared_ptr.
         * 
         * This method is overridden from the base class. It creates a new instance of CButton by copying the current object (*this)
         * and returns it as a shared pointer to CDWindow. 
         * 
         * @return A shared pointer to the copy of the CDWindow object
        */
        shared_ptr<CDWindow> p_copy ( void ) const override {
            return make_shared<CButton>(*this);
        }

        /**
         * Prints the details of the CButton object.
         * 
         * @param os The output stream
         * @param flag A flag parameter
        */
        void printCDWindow ( ostream & os, const int flag ) const override {
            os << "[" << m_id << "]" << " Button" << " \"" << m_text << "\" " << m_APos << endl;
        }

    private:
        string m_text;
};

/**
 * CInput - derived class
 * CDWindow - base class
 *
 * CInput class represents a text input window. 
*/
class CInput : public CDWindow
{
    public:
        // Constructor for the CInput class.
        CInput ( int id, const CRect & relPos, const string & value )
        : CDWindow ( id, relPos ), m_text ( value ) {}

        // Constructor for the CInput class.
        CInput ( const CInput & other )
        : CDWindow ( other . m_id, other . m_APos, other . m_RPos ), m_text ( other . m_text ) {}

        /**
         * Creates a copy of the CDWindow object using shared_ptr.
         * 
         * This method is overridden from the base class. It creates a new instance of CInput by copying the current object (*this)
         * and returns it as a shared pointer to CDWindow. 
         * 
         * @return A shared pointer to the copy of the CDWindow object
        */
        shared_ptr<CDWindow> p_copy ( void ) const override {
            return make_shared<CInput>(*this);
        }

        /**
         * Sets the value of the input window.
         * 
         * @param x The new value to set for the input window
        */
        void setValue ( const string & x ) {
            m_text = x;
        }

        /**
         * Returns the value of the input window.
         * 
         * @return The value of the input window
        */
        string getValue ( void ) {
            return m_text;
        }

        /**
         * Prints the details of the CInput object.
         * 
         * @param os The output stream
         * @param flag A flag parameter
        */
        void printCDWindow ( ostream & os, const int flag ) const override {
            os << "[" << m_id << "]" << " Input" << " \"" << m_text << "\" " << m_APos << endl;
        }    

    private:
        string m_text;
};

/**
 * CLabel - derived class
 * CDWindow - base class
 *
 * CLabel class represents a label. 
*/
class CLabel : public CDWindow
{
    public:
        // Constructor for the CLabel class.
        CLabel ( int id, const CRect & relPos, const string & label )
        : CDWindow ( id, relPos ), m_text ( label ) {}

        // Constructor for the CLabel class.
        CLabel ( const CLabel & other )
        : CDWindow ( other . m_id, other . m_APos, other . m_RPos ), m_text ( other . m_text ) {}

        /**
         * Creates a copy of the CDWindow object using shared_ptr.
         * 
         * This method is overridden from the base class. It creates a new instance of CLabel by copying the current object (*this)
         * and returns it as a shared pointer to CDWindow. 
         * 
         * @return A shared pointer to the copy of the CDWindow object
        */
        shared_ptr<CDWindow> p_copy ( void ) const override {
            return make_shared<CLabel>(*this);
        }  

        /**
         * Prints the details of the CLabel object.
         * 
         * @param os The output stream
         * @param flag A flag parameter
        */
        void printCDWindow ( ostream & os, const int flag ) const override {
            os << "[" << m_id << "]" << " Label" << " \"" << m_text << "\" " << m_APos << endl;
        }       

    private:
        string m_text;                             
};

/**
 * CComboBox - derived class
 * CDWindow - base class
 *
 * CComboBox class represents a combo box. 
*/
class CComboBox : public CDWindow
{
    public:
        // Constructor for the CComboBox class.
        CComboBox ( int id, const CRect & relPos )
        : CDWindow ( id, relPos ), index ( 0 ) {}

        // Constructor for the CComboBox class.
        CComboBox ( const CComboBox & other )
        : CDWindow ( other . m_id, other . m_APos, other . m_RPos ), menu ( other . menu ), index ( 0 ) {}

        /**
         * Creates a copy of the CDWindow object using shared_ptr.
         * 
         * This method is overridden from the base class. It creates a new instance of CComboBox by copying the current object (*this)
         * and returns it as a shared pointer to CDWindow. 
         * 
         * @return A shared pointer to the copy of the CDWindow object
        */
        shared_ptr<CDWindow> p_copy ( void ) const override {
            return make_shared<CComboBox>(*this);
        }    
        
        /**
         * Adds a choice to the combo box menu.
         * 
         * @param x The item to be added to the combo box menu
         * @return Reference to the modified CComboBox object
        */
        CComboBox &add ( const string & x ) {
            menu . push_back ( x );
            return *this;
        }                                                                      
        
        /**
         * Sets the selected index of the combo box.
         * 
         * @param x The index to be set as selected
        */
        void setSelected ( const size_t x ) {
            index = x;
        }

        /**
         * Gets the selected index of the combo box.
         * 
         * @return The selected index
        */ 
        size_t getSelected ( void ) const {
            return index;
        }

        /**
         * Prints the combo box menu with various formatting options. 
         * 
         * @param os The output stream
         * @param flag A flag parameter
        */    
        void printMenu ( ostream & os, const int flag ) const {
            switch ( flag ){
                case 0:
                    for ( size_t i = 0; i < menu . size(); i++ ){
                        if ( i == index ){
                            os << "+->" << menu[i] << "<" << endl;
                            continue;    
                        }
                        os << "+- " << menu[i] << endl;
                    }
                    break;
                case 1:
                    for ( size_t i = 0; i < menu . size(); i++ ){
                        if ( i == index ){
                            os << "   +->" << menu[i] << "<" << endl;
                            continue;    
                        }
                        os << "   +- " << menu[i] << endl;
                    }
                    break;
                case 2:
                    for ( size_t i = 0; i < menu . size(); i++ ){
                        if ( i == index ){
                            os << "|  +->" << menu[i] << "<" << endl;
                            continue;    
                        }
                        os << "|  +- " << menu[i] << endl;
                    }
                    break;                                
            }
        }

        /**
         * Prints the details of the combo box menu.
         * 
         * @param os The output stream
         * @param flag A flag parameter
        */
        void printCDWindow ( ostream & os, const int flag ) const override
        {
            os << "[" << m_id << "]" << " ComboBox " << m_APos << endl;
            printMenu ( os, flag );
        }     

    private:
        vector<string> menu;
        size_t index;
};

template <typename _T>
string toString ( const _T & x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int main ( void )
{
  assert ( sizeof ( CButton ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
  assert ( sizeof ( CInput ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
  assert ( sizeof ( CLabel ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
  CWindow a ( 0, "Sample window", CRect ( 10, 10, 600, 480 ) );
  a . add ( CButton ( 1, CRect ( 0.1, 0.8, 0.3, 0.1 ), "Ok" ) ) . add ( CButton ( 2, CRect ( 0.6, 0.8, 0.3, 0.1 ), "Cancel" ) );
  a . add ( CLabel ( 10, CRect ( 0.1, 0.1, 0.2, 0.1 ), "Username:" ) );
  a . add ( CInput ( 11, CRect ( 0.4, 0.1, 0.5, 0.1 ), "chucknorris" ) );
  a . add ( CComboBox ( 20, CRect ( 0.1, 0.3, 0.8, 0.1 ) ) . add ( "Karate" ) . add ( "Judo" ) . add ( "Box" ) . add ( "Progtest" ) );
  assert ( toString ( a ) ==
    "[0] Window \"Sample window\" (10,10,600,480)\n"
    "+- [1] Button \"Ok\" (70,394,180,48)\n"
    "+- [2] Button \"Cancel\" (370,394,180,48)\n"
    "+- [10] Label \"Username:\" (70,58,120,48)\n"
    "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
    "+- [20] ComboBox (70,154,480,48)\n"
    "   +->Karate<\n"
    "   +- Judo\n"
    "   +- Box\n"
    "   +- Progtest\n" );
  CWindow b = a;
  assert ( toString ( *b . search ( 20 ) ) ==
    "[20] ComboBox (70,154,480,48)\n"
    "+->Karate<\n"
    "+- Judo\n"
    "+- Box\n"
    "+- Progtest\n" );
  assert ( dynamic_cast<CComboBox &> ( *b . search ( 20 ) ) . getSelected () == 0 );
  dynamic_cast<CComboBox &> ( *b . search ( 20 ) ) . setSelected ( 3 );
  assert ( dynamic_cast<CInput &> ( *b . search ( 11 ) ) . getValue () == "chucknorris" );
  dynamic_cast<CInput &> ( *b . search ( 11 ) ) . setValue ( "chucknorris@fit.cvut.cz" );
  b . add ( CComboBox ( 21, CRect ( 0.1, 0.5, 0.8, 0.1 ) ) . add ( "PA2" ) . add ( "OSY" ) . add ( "Both" ) );
  assert ( toString ( b ) ==
    "[0] Window \"Sample window\" (10,10,600,480)\n"
    "+- [1] Button \"Ok\" (70,394,180,48)\n"
    "+- [2] Button \"Cancel\" (370,394,180,48)\n"
    "+- [10] Label \"Username:\" (70,58,120,48)\n"
    "+- [11] Input \"chucknorris@fit.cvut.cz\" (250,58,300,48)\n"
    "+- [20] ComboBox (70,154,480,48)\n"
    "|  +- Karate\n"
    "|  +- Judo\n"
    "|  +- Box\n"
    "|  +->Progtest<\n"
    "+- [21] ComboBox (70,250,480,48)\n"
    "   +->PA2<\n"
    "   +- OSY\n"
    "   +- Both\n" );
  assert ( toString ( a ) ==
    "[0] Window \"Sample window\" (10,10,600,480)\n"
    "+- [1] Button \"Ok\" (70,394,180,48)\n"
    "+- [2] Button \"Cancel\" (370,394,180,48)\n"
    "+- [10] Label \"Username:\" (70,58,120,48)\n"
    "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
    "+- [20] ComboBox (70,154,480,48)\n"
    "   +->Karate<\n"
    "   +- Judo\n"
    "   +- Box\n"
    "   +- Progtest\n" );
  b . setPosition ( CRect ( 20, 30, 640, 520 ) );
  assert ( toString ( b ) ==
    "[0] Window \"Sample window\" (20,30,640,520)\n"
    "+- [1] Button \"Ok\" (84,446,192,52)\n"
    "+- [2] Button \"Cancel\" (404,446,192,52)\n"
    "+- [10] Label \"Username:\" (84,82,128,52)\n"
    "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
    "+- [20] ComboBox (84,186,512,52)\n"
    "|  +- Karate\n"
    "|  +- Judo\n"
    "|  +- Box\n"
    "|  +->Progtest<\n"
    "+- [21] ComboBox (84,290,512,52)\n"
    "   +->PA2<\n"
    "   +- OSY\n"
    "   +- Both\n" );
  return EXIT_SUCCESS;
}