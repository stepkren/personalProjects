#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#include <iterator>
#include <stdexcept>
using namespace std;

template<typename M_>
struct MatchRes
{
  public:
    // Constructor for the MatchRes structure
    MatchRes ( const string & cont1, const string & cont2, const M_ & res )
    : contestant1 ( cont1 ), contestant2 ( cont2 ), result ( res ) {}

    string contestant1;
    string contestant2;
    M_ result;
};

template <typename M_>
class CContest
{
  public:
    // Default constructor for the CContest class.
    CContest ( void ) {}

    // Destructor for the CContest class.
    ~CContest ( void ) {}

    /**
     * Adds a match to the vector of matches.
     * 
     * @param a The first team of the match
     * @param b The second team of the match
     * @param win Determines which of the two teams won
     * @return A reference to the CContest class object (*this)
    */
    CContest & addMatch ( const string & a, const string & b, const M_ & win )
    {
      MatchRes<M_> tmp ( a, b, win );

      for ( size_t i = 0; i < matches . size(); i++ ){
        if ( ( ( matches[i] . contestant1 == tmp . contestant1 ) && ( matches[i] . contestant2 == tmp . contestant2 ) ) ||
             ( ( matches[i] . contestant1 == tmp . contestant2 ) && ( matches[i] . contestant2 == tmp . contestant1 ) ) ){
              throw logic_error ( "already inside!" );
        }
      }

      matches . push_back( tmp );

      return *this;
    }

    /**
     * Determines whether the completed match results lead to a clear score sheet or not.
     * 
     * @param compare A function object that compares match results
     * @return True if the score sheet is clear, False if not
    */
    bool isOrdered ( const function<int ( const M_ & match )> & compare ) const
    {
      map<string, vector<string>> graph;
      map<string, int> wins;

      for ( const auto & elem : matches ){
        wins . insert ( make_pair( elem . contestant1, 0 ) );
        wins . insert ( make_pair( elem . contestant2, 0 ) );
        int res = compare ( elem . result );
        if ( res > 0 ){
          graph[elem . contestant1] . push_back( elem . contestant2 );
        }
        else if ( res < 0 ){
          graph[elem . contestant2] . push_back( elem . contestant1 );
        }
        else
          return false;
      }
    
      for (const auto& start_node : graph) {
        map<string, bool> visited;
        queue<string> q;

        q.push(start_node.first);
        visited[start_node.first] = true;

        while (!q.empty()) {
          string current_node = q . front();
          q.pop();

          for (const auto& neighbor : graph[current_node]) {
            if (!visited[neighbor]) {
              q.push(neighbor);
              visited[neighbor] = true;
              wins[start_node . first]++;
            }
          }
        }
      }      

      for ( auto it = wins . begin(); it != wins . end(); ++it ){
        auto nextIt = it;
        ++nextIt;
        if ( nextIt != wins . end() && it -> second == nextIt -> second ){
          return false;
        }
      }

      return true;
    }

    /**
     * Calculates the result sheet.
     * 
     * @param compare A function object used to compare match results
     * @return A list of strings with the names of the opponents in order from first (overall winner) to last
     * @throws logic_error if the result sheet isn't unambiguous
    */
    list<string> results ( const function<int ( const M_ & match )> & compare ) const
    {
      list<string> res;
      map<string, vector<string>> graph;
      map<string, int> wins;

      for ( const auto & elem : matches ){
        wins . insert ( make_pair( elem . contestant1, 0 ) );
        wins . insert ( make_pair( elem . contestant2, 0 ) );
        int res = compare ( elem . result );
        if ( res > 0 ){
          graph[elem . contestant1] . push_back( elem . contestant2 );
        }
        else if ( res < 0 ){
          graph[elem . contestant2] . push_back( elem . contestant1 );
        }
        else
          throw logic_error ("undefined order!");
      }
    
      for (const auto& start_node : graph) {
        map<string, bool> visited;
        queue<string> q;

        q.push(start_node.first);
        visited[start_node.first] = true;

        while (!q.empty()) {
          string current_node = q . front();
          q.pop();

          for (const auto& neighbor : graph[current_node]) {
            if (!visited[neighbor]) {
              q.push(neighbor);
              visited[neighbor] = true;
              wins[start_node . first]++;
            }
          }
        }
      }          

      for ( auto it = wins . begin(); it != wins . end(); ++it ){
        auto nextIt = it;
        ++nextIt;
        if ( nextIt != wins . end() && it -> second == nextIt -> second ){
          throw logic_error("undefined order!");
        }
      }

      vector<pair<string, int>> pairs;
      for ( const auto & elem : wins ){
        pairs . push_back ( elem );
      }
      sort ( pairs . begin(), pairs . end(), [](const pair<string, int> & a, const pair<string, int> & b ){
        return b . second < a . second;
      } );

      for ( const auto & elem : pairs ){
        res . push_back( elem . first );
      }

      return res;      
    }

    
    // Prints the matches in the 'matches' vector.
    void printMatches ( void ) const
    { 
      for ( const auto & elem : matches ){
        cout << elem . contestant1 << " " << elem . contestant2 << endl;  
      }
    }

  private:
    vector<MatchRes<M_>> matches;
    map<string, int> neverLost;
};

struct CMatch
{
  public:
    // CMatch struct constructor
    CMatch ( int a, int b )
    : m_A ( a ), m_B ( b ) {}
    
    int m_A;
    int m_B;
};

class HigherScoreThreshold
{
  public:
    // HigherScoreThreshold class constructor
    HigherScoreThreshold ( int diffAtLeast )
    : m_DiffAtLeast ( diffAtLeast ) {}

    int operator () ( const CMatch & x ) const {
      return ( x . m_A > x . m_B + m_DiffAtLeast ) - ( x . m_B > x . m_A + m_DiffAtLeast );
    }

  private:
    int m_DiffAtLeast;    
};

int HigherScore ( const CMatch & x ) {
  return ( x . m_A > x . m_B ) - ( x . m_B > x . m_A );
}

int main ( void ) {
  CContest<CMatch>  x;
  
  x . addMatch ( "C++", "Pascal", CMatch ( 10, 3 ) )
    . addMatch ( "C++", "Java", CMatch ( 8, 1 ) )
    . addMatch ( "Pascal", "Basic", CMatch ( 40, 0 ) )
    . addMatch ( "Java", "PHP", CMatch ( 6, 2 ) )
    . addMatch ( "Java", "Pascal", CMatch ( 7, 3 ) )
    . addMatch ( "PHP", "Basic", CMatch ( 10, 0 ) );
    
  
  assert ( ! x . isOrdered ( HigherScore ) );
  try
  {
    list<string> res = x . results ( HigherScore );
    assert ( "Exception missing!" == nullptr );
  }
  catch ( const logic_error & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown!" == nullptr );
  }

  x . addMatch ( "PHP", "Pascal", CMatch ( 3, 6 ) ); 

  assert ( x . isOrdered ( HigherScore ) );
  try
  {
    list<string> res = x . results ( HigherScore );
    assert ( ( res == list<string>{ "C++", "Java", "Pascal", "PHP", "Basic" } ) );
  }
  catch ( ... )
  {
    assert ( "Unexpected exception!" == nullptr );
  }

  
  assert ( ! x . isOrdered ( HigherScoreThreshold ( 3 ) ) );
  try
  {
    list<string> res = x . results ( HigherScoreThreshold ( 3 ) );
    assert ( "Exception missing!" == nullptr );
  }
  catch ( const logic_error & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown!" == nullptr );
  }
  
  assert ( x . isOrdered ( [] ( const CMatch & x )
  {
    return ( x . m_A < x . m_B ) - ( x . m_B < x . m_A ); 
  } ) );
  try
  {
    list<string> res = x . results ( [] ( const CMatch & x )
    {
      return ( x . m_A < x . m_B ) - ( x . m_B < x . m_A ); 
    } );
    assert ( ( res == list<string>{ "Basic", "PHP", "Pascal", "Java", "C++" } ) );
  }
  catch ( ... )
  {
    assert ( "Unexpected exception!" == nullptr );
  }
  
  CContest<bool>  y;
  
  y . addMatch ( "Python", "PHP", true )
    . addMatch ( "PHP", "Perl", true )
    . addMatch ( "Perl", "Bash", true )
    . addMatch ( "Bash", "JavaScript", true )
    . addMatch ( "JavaScript", "VBScript", true );
  
  assert ( y . isOrdered ( [] ( bool v )
  {
    return v ? 10 : - 10;
  } ) );
  try
  {
    list<string> res = y . results ( [] ( bool v )
    {
      return v ? 10 : - 10;
    });
    assert ( ( res == list<string>{ "Python", "PHP", "Perl", "Bash", "JavaScript", "VBScript" } ) );
  }
  catch ( ... )
  {
    assert ( "Unexpected exception!" == nullptr );
  }
    
  y . addMatch ( "PHP", "JavaScript", false );
  assert ( !y . isOrdered ( [] ( bool v )
  {
    return v ? 10 : - 10;
  } ) );
  try
  {
    list<string> res = y . results ( [] ( bool v )
    {
      return v ? 10 : - 10;
    } );
    assert ( "Exception missing!" == nullptr );
  }
  catch ( const logic_error & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown!" == nullptr );
  }
  
  try
  {
    y . addMatch ( "PHP", "JavaScript", false );
    assert ( "Exception missing!" == nullptr );
  }
  catch ( const logic_error & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown!" == nullptr );
  }
  
  try
  {
    y . addMatch ( "JavaScript", "PHP", true );
    assert ( "Exception missing!" == nullptr );
  }
  catch ( const logic_error & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown!" == nullptr );
  }
  return EXIT_SUCCESS;
}