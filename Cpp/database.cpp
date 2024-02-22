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
    // No args constructor  
    CPersonalAgenda  ( void )
    {
    }

    // Destructor                  
    ~CPersonalAgenda ( void )
    {
    }

    /** Add a new person entry with given details to the database.
     * 
     * @param name The first name of the person to be added
     * @param surname The last name of the person to be added
     * @param email The email address of the person to be added
     * @param salary The salary of the person to be added
     * @return True if the person was successfully added, False if a person with the same name (first name and last name) or email already exists in the database 
     */
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

    /**
     * Deletes a person entry from the database by their first name and last name.
     * 
     * @param name The first name of the person to be deleted
     * @param surname The last name of the person to be deleted
     * @return True if the person was successfully deleted from the database, False if the person wasn't found in the database
    */
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

    /**
     * Deletes a person entry from the database by their email.
     * 
     * @param enail The email of the person to be deleted
     * @return True if the person was successfully deleted, False if the person wasn't found in the database
    */
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

    /**
     * Change the first and last name of a person in the database found by email.
     * 
     * @param email The email address of the person whose first and last names are to be changed
     * @param newName The new first name for the person
     * @param newSurname The new last name for the person
     * @return True if the first and last names were successfully changed, False if the email doesn't exist in the database or the new first name or surname are already in the database
    */
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

        return true;
    }       

    /**
     * Change the email address of a person in the database found by first and last name.
     * 
     * @param name The first name of the person whose email address is to be changed
     * @param surname The last name of the person whose email address is to be changed
     * @param newEmail The new email address for the person
     * @return True if the email address was successfully changed, False if the first or last name don't exist in the database or the new email address is already in the database
    */                                
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
        if ( ( names[posNames].firstName == name ) && ( names[posNames].lastName == surname ) ){
            tmp.email = names[posNames].email; tmp.salary = names[posNames].salary;
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

        return true;
    }

    /**
     * Sets the salary of a person in the database.
     * 
     * @param name The first name of the person in the database whose salary is to be set
     * @param surname The last name of the person in the database whose salary is to be set
     * @param salary The value of the salary to be set
     * @return True if the salary was successfully set, False if the first and last name don't exist in the database
    */
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

    /**
     * Sets the salary of a person in the database.
     * 
     * @param email The email address of the person in the database whose salary is to be set
     * @param salary The value of the salary to be set
     * @return True if the salary was successfully set, False if the email address doesn't exist in the database
    */                              
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

    /**
     * Returns the salary of a person in the database.
     * 
     * @param name The first name of the person whose salary is to be returned
     * @param surname The last name of the person whose salary is to be returned
     * @return The salary of the person in the database
    */                                
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

    /**
     * Returns the salary of a person in the database.
     * 
     * @param email The email address of the person whose salary is to be returned
     * @return The salary of the person in the database
    */                                  
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

    /**
     * Returns the salary position of the person on an imaginary scale from worst (lowest) to best (highest).
     * 
     * @param name The first name of the person whose "rank" is to be returned
     * @param surname The last name of the person whose "rank" is to be returned
     * @param rankMin The lowest value of the interval of salary ranks
     * @param rankMax The highest value of the interval of salary ranks
     * @return True if the "rank" is successfully returned, False if the first and last name don't exist in the database
    */
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

      return true;
    }                                     

    /**
     * Returns the salary position of the person on an imaginary scale from worst (lowest) to best (highest).
     * 
     * @param email The email address of the person whose "rank" is to be returned
     * @param rankMin The lowest value of the interval of salary ranks
     * @param rankMax The highest value of the interval of salary ranks
     * @return True if the "rank" is successfully returned, False if the email address doesn't exist in the database
    */                                    
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

      return true;
    }                                     

    /**
     * Returns the first person in the sorted database.
     * 
     * @param outName The first name of the first person in the database
     * @param outSurname The last name of the first person in the database
     * @return True if the person is successfully returned, False if the database is empty
    */
    bool          getFirst         ( string          & outName,
                                     string          & outSurname ) const
    {
      if ( names.size() == 0 )
        return false;

      outName = names[0].firstName;
      outSurname = names[0].lastName;

      return true;
    }                                     

    /**
     * Returns the next person in the sorted database.
     * 
     * @param name The first name of the person before the searched for person
     * @param surname The last name of the person before the searched for person
     * @param outName The first name of the next person after the found person
     * @param outSurname The last name of the next person after the found person
     * @return True if the person is successfully returned, False if the person (name, surname) wasn't found or if the found person is the last entry in the database
    */                                     
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

    
    // Prints the names and emails vectors.
    void printVectors ( void )
    {
        for ( size_t i = 0; i < names.size(); i++ ){
            cout << names[i].firstName << " " << names[i].lastName << " " << names[i].email << " " << names[i].salary << endl;
        }

        for ( size_t i = 0; i < emails.size(); i++ ){
            cout << emails[i].firstName << " " << emails[i].lastName << " " << emails[i].email << " " << emails[i].salary << endl;
        }
    }                                                               
                                     
  private:

    Person p;
    vector<Person> names;
    vector<Person> emails;

    /**
     * Method that compares 2 Person objects by first and last name.
     *
     * @param a The first Person object to be compared
     * @param b The second Person object to be compared
     * @return True if 'a' should come before 'b' in the sorted order based on last names and first names, false otherwise
    */
    static bool compareNames ( const Person& a, const Person& b )
    {
        if ( a.lastName != b.lastName )
            return a.lastName < b.lastName;
        return a.firstName < b.firstName;
    }

    /**
     * Method that compares 2 Person objects by email address.
     * 
     * @param a The first Person object to be compared
     * @param b The second Person object to be compared
     * @return True if 'a' should come before 'b' in the sorted order based on email addresses, false otherwise
    */
    static bool compareEmails ( const Person& a, const Person& b )
    {
        return a.email < b.email;
    }
};


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
