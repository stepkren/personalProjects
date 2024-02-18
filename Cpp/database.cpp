#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;

struct Person
{
    string firstName, lastName, email;
    int salary;
};

class CPersonalAgenda
{
  public:
// CONSTRUCTOR  
                  CPersonalAgenda  ( void )
                  {
                  }
// DESTRUCTOR                  
                  ~CPersonalAgenda ( void )
                  {

                  }
/** Add entry to the database */
    bool          add              ( const string    & name,
                                     const string    & surname,
                                     const string    & email,
                                     unsigned int      salary )
    {
        p.firstName = name;
        p.lastName = surname;
        p.email = email;
        p.salary = salary;

        for ( size_t i = 0; i < names.size(); i++ ){
            if ( ( ( names[i].firstName == name ) && ( names[i].lastName == surname ) ) || ( names[i].email == email ) )
                return false;
        }   

        auto itNames = lower_bound ( names.begin(), names.end(), p, compareNames );
        auto itEmails = lower_bound ( emails.begin(), emails.end(), p, compareEmails );

        names.insert ( itNames , p );
        emails.insert ( itEmails, p );

        return true;
    }
// METHOD DELETE ENTRY ( NAME, SURNAME )    
    bool          del              ( const string    & name,
                                     const string    & surname )
    {
        Person tmp;
        tmp.firstName = name;
        tmp.lastName = surname;

        auto itNames = lower_bound ( names.begin(), names.end(), tmp, compareNames );
        size_t posNames = itNames - names.begin();
        if ( posNames > names.size() - 1 )
            return false;        

        if ( ( ( names[posNames].firstName == name ) && ( names[posNames].lastName == surname ) ) ){
            tmp.email = names[posNames].email;
            names.erase( itNames );
        }
        else return false;

        auto itEmails = lower_bound ( emails.begin(), emails.end(), tmp, compareEmails );
        emails.erase( itEmails );

        return true;
    }                                     
// METHOD DELETE ENTRY ( EMAIL )                                     
    bool          del              ( const string    & email )
    {
        Person tmp;
        tmp.email = email;

        auto itEmails = lower_bound ( emails.begin(), emails.end(), tmp, compareEmails );
        size_t posEmails = itEmails - emails.begin();
        if ( posEmails > emails.size() - 1 )
            return false;        

        if ( emails[posEmails].email == email ){
            tmp.firstName = emails[posEmails].firstName; tmp.lastName = emails[posEmails].lastName;
            emails.erase( itEmails );
        }
        else return false;

        auto itNames = lower_bound ( names.begin(), names.end(), tmp, compareNames );
        names.erase( itNames );

        return true;
    }
// METHOD CHANGE NAME    
    bool          changeName       ( const string    & email,
                                     const string    & newName,
                                     const string    & newSurname )
    {
        Person tmp;
        tmp.email = email;
        tmp.firstName = newName;
        tmp.lastName = newSurname;

        size_t posNames = lower_bound( names.begin(), names.end(), tmp, compareNames ) - names.begin();
        if ( ( names[posNames].firstName == newName ) && ( names[posNames].lastName == newSurname ) )
            return false;

        size_t posEmails = lower_bound ( emails.begin(), emails.end(), tmp, compareEmails ) - emails.begin();
        if ( posEmails > emails.size() - 1 )
            return false;

        if ( emails[posEmails].email == email ){
            tmp.firstName = emails[posEmails].firstName; tmp.lastName = emails[posEmails].lastName; tmp.salary = emails[posEmails].salary;
            emails[posEmails].firstName = newName; emails[posEmails].lastName = newSurname;
        }
        else return false;

        auto itNames = lower_bound ( names.begin(), names.end(), tmp, compareNames );
        names.erase( itNames );
        tmp.firstName = newName; tmp.lastName = newSurname;
        itNames = lower_bound ( names.begin(), names.end(), tmp, compareNames );
        posNames = itNames - names.begin();
        if ( ( names[posNames].firstName == newName ) && ( names[posNames].lastName == newSurname ) )
            return false;
        names.insert( itNames, tmp );
        // names[posNames].firstName = newName; names[posNames].lastName = newSurname;  - names.begin()

        return true;
    }                                     
// METHOD CHANGE EMAIL                                     
    bool          changeEmail      ( const string    & name,
                                     const string    & surname,
                                     const string    & newEmail )
    {
        Person tmp;
        tmp.firstName = name;
        tmp.lastName = surname;
        tmp.email = newEmail;

        size_t posEmails = lower_bound( emails.begin(), emails.end(), tmp, compareEmails ) - emails.begin();
        if ( emails[posEmails].email == newEmail )
            return false;

        size_t posNames = lower_bound ( names.begin(), names.end(), tmp, compareNames ) - names.begin();
        if ( posNames > names.size() - 1 )
            return false;
        // cout << "pos = " << posNames << " FN = " << names[posNames].firstName << " LN = " << names[posNames].lastName << endl;
        // cout << names.size() << endl;
        if ( ( names[posNames].firstName == name ) && ( names[posNames].lastName == surname ) ){
            tmp.email = names[posNames].email; tmp.salary = names[posNames].salary;
            // cout << names[posNames].email << endl;
            if ( names[posNames].email == newEmail )
                return false;
            names[posNames].email = newEmail;
        }
        else return false;

        auto itEmails = lower_bound ( emails.begin(), emails.end(), tmp, compareEmails );
        emails.erase( itEmails );
        tmp.email = newEmail;
        itEmails = lower_bound ( emails.begin(), emails.end(), tmp, compareEmails );
        posEmails = itEmails - emails.begin();
        if ( ( emails[posEmails].email == newEmail ) )
            return false;
        emails.insert( itEmails, tmp );
        // emails[posEmails].email = newEmail; - emails.begin()

        return true;
    }                                     
// METHOD SET SALARY ( NAME, SURNAME )                                     
    bool          setSalary        ( const string    & name,
                                     const string    & surname,
                                     unsigned int      salary )
  	{
        Person tmp;
        tmp.firstName = name;
        tmp.lastName = surname;

        size_t posNames = lower_bound( names.begin(), names.end(), tmp, compareNames ) - names.begin();
        if ( posNames > names.size() - 1 )
            return false;
        if ( ( names[posNames].firstName == name ) && ( names[posNames].lastName == surname ) ){
            tmp.email = names[posNames].email;
            names[posNames].salary = salary;
        }
        else return false;

        size_t posEmails = lower_bound( emails.begin(), emails.end(), tmp, compareEmails ) - emails.begin();
        emails[posEmails].salary = salary;

        return true;
    }                                     
// METHOD SET SALARY ( EMAIL )                                     
    bool          setSalary        ( const string    & email,
                                     unsigned int      salary )
    {
        Person tmp;
        tmp.email = email;

        size_t posEmails = lower_bound ( emails.begin(), emails.end(), tmp, compareEmails ) - emails.begin();
        if ( posEmails > emails.size() - 1 )
            return false;

        if ( emails[posEmails].email == email ){
            tmp.firstName = emails[posEmails].firstName; tmp.lastName = emails[posEmails].lastName;
            emails[posEmails].salary = salary;
        }
        else return false;

        size_t posNames = lower_bound ( names.begin(), names.end(), tmp, compareNames ) - names.begin();
        names[posNames].salary = salary;

        return true;
    }                                     
// METHOD GET SALARY ( NAME, SURNAME )                                     
    unsigned int  getSalary        ( const string    & name,
                                     const string    & surname ) const
    {
        Person tmp;
        tmp.firstName = name;
        tmp.lastName = surname;
        unsigned int m_salary = 0;

        size_t posNames = lower_bound( names.begin(), names.end(), tmp, compareNames ) - names.begin();
        if ( posNames > names.size() - 1 )
            return false;        
        if ( ( names[posNames].firstName == name ) && ( names[posNames].lastName == surname ) ){
            m_salary = names[posNames].salary;
        }
        else return 0;

        return m_salary;
    }                                     
// METHOD GET SALARY ( EMAIL )                                     
    unsigned int  getSalary        ( const string    & email ) const
    {
        Person tmp;
        tmp.email = email;
        unsigned int m_salary =0;

        size_t posEmails = lower_bound( emails.begin(), emails.end(), tmp, compareEmails ) - emails.begin();
        if ( posEmails > emails.size() - 1 )
            return false;        
        if ( emails[posEmails].email == email ){
            m_salary = emails[posEmails].salary;
        }
        else return 0;

        return m_salary;
    }
// METHOD GET RANK ( NAME, SURNAME )    
    bool          getRank          ( const string    & name,
                                     const string    & surname,
                                     int             & rankMin,
                                     int             & rankMax ) const
    {
      Person tmp;
      tmp.firstName = name;
      tmp.lastName = surname;
      int compSalary = 0;
      rankMax = 0; rankMin = 0;

      size_t posNames = lower_bound( names.begin(), names.end(), tmp, compareNames ) - names.begin();
      if ( posNames > names.size() - 1 )
            return false;      
      if ( ( names[posNames].firstName == name ) && ( names[posNames].lastName == surname ) ){
        compSalary = names[posNames].salary;
      }
      else return false;

      for ( size_t i = 0; i < names.size(); i++ ){
        if ( names[i].salary < compSalary )
            rankMin++;
        else if ( names[i].salary == compSalary )
            rankMax++;
      }
      rankMax = rankMin + rankMax - 1;
    //   cout << "min = " << rankMin << " max = " << rankMax << endl;

      return true;
    }                                     
// METHOD GET RANK ( EMAIL )                                     
    bool          getRank          ( const string    & email,
                                     int             & rankMin,
                                     int             & rankMax ) const
    {
      Person tmp;
      tmp.email = email;
      int compSalary = 0;
      rankMin = 0; rankMax = 0;

      size_t posEmails = lower_bound( emails.begin(), emails.end(), tmp, compareEmails ) - emails.begin();
      if ( posEmails > emails.size() - 1 )
            return false;      
      if ( emails[posEmails].email == email ){
        compSalary = emails[posEmails].salary;
      }
      else return false;

        for ( size_t i = 0; i < emails.size(); i++ ){
        if ( emails[i].salary < compSalary )
            rankMin++;
        else if ( emails[i].salary == compSalary )
            rankMax++;
      }
      rankMax = rankMin + rankMax - 1;

    // cout << "min = " << rankMin << " max = " << rankMax << endl;

      return true;
    }                                     
// METHOD RETURN FIRST ENTRY ( SORTED - (1. SURNAME), (2. NAME) )                                     
    bool          getFirst         ( string          & outName,
                                     string          & outSurname ) const
    {
      if ( names.size() == 0 )
        return false;

      outName = names[0].firstName;
      outSurname = names[0].lastName;

      return true;
    }                                     
// METHOD RETURN NEXT ENRY ( SORTED - (1. SURNAME), (2. NAME)                                     
    bool          getNext          ( const string    & name,
                                     const string    & surname,
                                     string          & outName,
                                     string          & outSurname ) const
    {
        Person tmp;
        tmp.firstName = name;
        tmp.lastName = surname;

        auto itNames = lower_bound ( names.begin(), names.end(), tmp, compareNames );
        size_t posNames = itNames - names.begin();

        if ( posNames == names.size() - 1 )
            return false;

        if ( ( names[posNames].firstName == name ) && ( names[posNames].lastName == surname ) ){
            outName = names[posNames + 1].firstName; outSurname = names[posNames + 1].lastName;
        }

        return true;
    }

    void printVectors ( void )
    {
        for ( size_t i = 0; i < names.size(); i++ ){
            // cout << names[i].firstName << " " << names[i].lastName << " " << names[i].email << " " << names[i].salary << endl;
        }

        for ( size_t i = 0; i < emails.size(); i++ ){
            // cout << emails[i].firstName << " " << emails[i].lastName << " " << emails[i].email << " " << emails[i].salary << endl;
        }
    }                                                               
                                     
  private:

    Person p;
    vector<Person> names;
    vector<Person> emails;

    static bool compareNames ( const Person& a, const Person& b )
    {
        if ( a.lastName != b.lastName )
            return a.lastName < b.lastName;
        return a.firstName < b.firstName;
    }

    static bool compareEmails ( const Person& a, const Person& b )
    {
        return a.email < b.email;
    }
};

#ifndef __PROGTEST__
int main ( void )
{
  string outName, outSurname;
  int lo, hi;

  CPersonalAgenda b1;
  assert ( b1 . add ( "John", "Smith", "john", 30000 ) );
  assert ( b1 . add ( "John", "Miller", "johnm", 35000 ) );
  assert ( b1 . add ( "Peter", "Smith", "peter", 23000 ) );

  assert ( b1 . getFirst ( outName, outSurname )
           && outName == "John"
           && outSurname == "Miller" );
  assert ( b1 . getNext ( "John", "Miller", outName, outSurname )
           && outName == "John"
           && outSurname == "Smith" );
  assert ( b1 . getNext ( "John", "Smith", outName, outSurname )
           && outName == "Peter"
           && outSurname == "Smith" );
  assert ( ! b1 . getNext ( "Peter", "Smith", outName, outSurname ) );
  assert ( b1 . setSalary ( "john", 32000 ) );
  assert ( b1 . getSalary ( "john" ) ==  32000 );
  assert ( b1 . getSalary ( "John", "Smith" ) ==  32000 );
  assert ( b1 . getRank ( "John", "Smith", lo, hi )
           && lo == 1
           && hi == 1 );
  assert ( b1 . getRank ( "john", lo, hi )
           && lo == 1
           && hi == 1 );
  assert ( b1 . getRank ( "peter", lo, hi )
           && lo == 0
           && hi == 0 );
  assert ( b1 . getRank ( "johnm", lo, hi )
           && lo == 2
           && hi == 2 );
  assert ( b1 . setSalary ( "John", "Smith", 35000 ) );
  assert ( b1 . getSalary ( "John", "Smith" ) ==  35000 );
  assert ( b1 . getSalary ( "john" ) ==  35000 );
  assert ( b1 . getRank ( "John", "Smith", lo, hi )
           && lo == 1
           && hi == 2 );
  assert ( b1 . getRank ( "john", lo, hi )
           && lo == 1
           && hi == 2 );
  assert ( b1 . getRank ( "peter", lo, hi )
           && lo == 0
           && hi == 0 );
  assert ( b1 . getRank ( "johnm", lo, hi )
           && lo == 1
           && hi == 2 );
  assert ( b1 . changeName ( "peter", "James", "Bond" ) );
  assert ( b1 . getSalary ( "peter" ) ==  23000 );
  assert ( b1 . getSalary ( "James", "Bond" ) ==  23000 );
  assert ( b1 . getSalary ( "Peter", "Smith" ) ==  0 );
  assert ( b1 . getFirst ( outName, outSurname )
           && outName == "James"
           && outSurname == "Bond" );
  assert ( b1 . getNext ( "James", "Bond", outName, outSurname )
           && outName == "John"
           && outSurname == "Miller" );
  assert ( b1 . getNext ( "John", "Miller", outName, outSurname )
           && outName == "John"
           && outSurname == "Smith" );
  assert ( ! b1 . getNext ( "John", "Smith", outName, outSurname ) );
  assert ( b1 . changeEmail ( "James", "Bond", "james" ) );
  assert ( b1 . getSalary ( "James", "Bond" ) ==  23000 );
  assert ( b1 . getSalary ( "james" ) ==  23000 );
  assert ( b1 . getSalary ( "peter" ) ==  0 );
  assert ( b1 . del ( "james" ) );
  assert ( b1 . getRank ( "john", lo, hi )
           && lo == 0
           && hi == 1 );
  assert ( b1 . del ( "John", "Miller" ) );
  assert ( b1 . getRank ( "john", lo, hi )
           && lo == 0
           && hi == 0 );
  assert ( b1 . getFirst ( outName, outSurname )
           && outName == "John"
           && outSurname == "Smith" );
  assert ( ! b1 . getNext ( "John", "Smith", outName, outSurname ) );
  assert ( b1 . del ( "john" ) );
  assert ( ! b1 . getFirst ( outName, outSurname ) );
  assert ( b1 . add ( "John", "Smith", "john", 31000 ) );
  assert ( b1 . add ( "john", "Smith", "joHn", 31000 ) );
  assert ( b1 . add ( "John", "smith", "jOhn", 31000 ) );

  CPersonalAgenda b2;
  assert ( ! b2 . getFirst ( outName, outSurname ) );
  assert ( b2 . add ( "James", "Bond", "james", 70000 ) );
  assert ( b2 . add ( "James", "Smith", "james2", 30000 ) );
  assert ( b2 . add ( "Peter", "Smith", "peter", 40000 ) );
  assert ( ! b2 . add ( "James", "Bond", "james3", 60000 ) );
  assert ( ! b2 . add ( "Peter", "Bond", "peter", 50000 ) );
  assert ( ! b2 . changeName ( "joe", "Joe", "Black" ) );
  assert ( ! b2 . changeEmail ( "Joe", "Black", "joe" ) );
  assert ( ! b2 . setSalary ( "Joe", "Black", 90000 ) );
  assert ( ! b2 . setSalary ( "joe", 90000 ) );
  assert ( b2 . getSalary ( "Joe", "Black" ) ==  0 );
  assert ( b2 . getSalary ( "joe" ) ==  0 );
  assert ( ! b2 . getRank ( "Joe", "Black", lo, hi ) );
  assert ( ! b2 . getRank ( "joe", lo, hi ) );
  assert ( ! b2 . changeName ( "joe", "Joe", "Black" ) );
  assert ( ! b2 . changeEmail ( "Joe", "Black", "joe" ) );
  assert ( ! b2 . del ( "Joe", "Black" ) );
  assert ( ! b2 . del ( "joe" ) );
  assert ( ! b2 . changeName ( "james2", "James", "Bond" ) );
  assert ( ! b2 . changeEmail ( "Peter", "Smith", "james" ) );
  assert ( ! b2 . changeName ( "peter", "Peter", "Smith" ) );
  assert ( ! b2 . changeEmail ( "Peter", "Smith", "peter" ) );
  assert ( b2 . del ( "Peter", "Smith" ) );
  assert ( ! b2 . changeEmail ( "Peter", "Smith", "peter2" ) );
  assert ( ! b2 . setSalary ( "Peter", "Smith", 35000 ) );
  assert ( b2 . getSalary ( "Peter", "Smith" ) ==  0 );
  assert ( ! b2 . getRank ( "Peter", "Smith", lo, hi ) );
  assert ( ! b2 . changeName ( "peter", "Peter", "Falcon" ) );
  assert ( ! b2 . setSalary ( "peter", 37000 ) );
  assert ( b2 . getSalary ( "peter" ) ==  0 );
  assert ( ! b2 . getRank ( "peter", lo, hi ) );
  assert ( ! b2 . del ( "Peter", "Smith" ) );
  assert ( ! b2 . del ( "peter" ) );
  assert ( b2 . add ( "Peter", "Smith", "peter", 40000 ) );
  assert ( b2 . getSalary ( "peter" ) ==  40000 );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
