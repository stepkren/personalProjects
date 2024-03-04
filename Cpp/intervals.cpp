#include <algorithm>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;


//  Forward declaration of CRangeList class
class CRangeList;
//  A class representing a interval of integers
class CRange {
public:
//  Constructor
  CRange(const long long int c_lo, const long long int c_hi)
      : lo(c_lo), hi(c_hi) {
    if (lo > hi)
      throw logic_error("");
  }
//  Addition operator that takes a CRange class object as a parameter
  CRangeList operator+(const CRange &range);
//  Substraction operator that takes a CRange class object as a parameter
  CRangeList operator-(const CRange &range);

private:
  long long int lo, hi; //  Lower limit of the interval, higher limit of the interval
  friend class CRangeList; //   Friend class declaration
};
//  A class representing a list of intervals
class CRangeList {
public:

/**
*   Checks if a given value is included in any of the intervals
*
*   @param a The value to check for inclusion
*   @return True if the value is included in any interval, false otherwise
*/
  bool includes(const long long int a) const {
    for (size_t i = 0; i < intervals.size(); i++) {
      if ((a >= intervals[i].lo) && (a <= intervals[i].hi))
        return true;
    }
    return false;
  }

/**
 *  Checks if a given interval is included in any of the intervals
 * 
 *  @param range The interval to search for in the vector
 *  @return True if the interval is included in the vector
*/
  bool includes(const CRange &range) const {
    for (size_t i = 0; i < intervals.size(); i++) {
      if (((range.lo >= intervals[i].lo) && (range.lo <= intervals[i].hi)) &&
          ((range.hi <= intervals[i].hi) && (range.hi >= intervals[i].lo)))
        return true;
    }
    return false;
  }

/**
 *  Adds given interval to the vector of intervals
 * 
 *  @param range The interval that is to be added
 *  @return A reference to the updated CRangeList object
*/
  CRangeList &operator+=(const CRange &range) {
    if (intervals.empty()) {
      intervals.push_back(range);
      return *this;
    }

    bool found = false;
    for (size_t i = 0; i < intervals.size(); i++) {
      if ((intervals[i].lo != LLONG_MIN) && (intervals[i].hi != LLONG_MAX)) {
        if ((range.lo < intervals[i].lo) && (range.hi > intervals[i].hi)) {
          intervals[i].lo = range.lo;
          intervals[i].hi = range.hi;
          found = true;
          break;
        } else if ((range.lo < intervals[i].lo) &&
                   ((range.hi >= intervals[i].lo - 1) &&
                    (intervals[i].lo != LLONG_MIN))) {
          intervals[i].lo = range.lo;
          found = true;
          break;
        } else if (((range.lo >= intervals[i].lo) &&
                    ((range.lo <= intervals[i].hi + 1) &&
                     (intervals[i].hi != LLONG_MAX))) &&
                   (range.hi > intervals[i].hi)) {
          intervals[i].hi = range.hi;
          found = true;
          break;
        } else if ((intervals[i].lo <= range.lo) &&
                   (intervals[i].hi >= range.hi)) {
          found = true;
          break;
        }
      }
    }
    if (!found) {
      auto insertPos =
          lower_bound(intervals.begin(), intervals.end(), range, compareLo);
      intervals.insert(insertPos, range);
    }
    concatenate();
    return *this;
  }

/**
 *  Adds a vector of intervals to a different vector of intervals
 * 
 *  @param other A CRangeList class object
 *  @return A reference to the updated CRangeList object
*/
  CRangeList &operator+=(const CRangeList &other) {
    for (size_t i = 0; i < other.intervals.size(); i++) {
      *this += other.intervals[i];
    }

    return *this;
  }

/**
 *  Addition operator that adds an interval to an existing vector of intervals
 * 
 *  @param range The interval that is to be added
 *  @return A reference to the updated CRangeList object
*/
  CRangeList &operator+(const CRange &range) {
    *this += range;

    return *this;
  }

/**
 *  Removes an interval from an existing vector of intervals
 * 
 *  @param range The interval that is to be removed from the vector
 *  @return A reference to the updated CRangeList object
*/
  CRangeList &operator-=(const CRange &range) {
    if (intervals.empty())
      return *this;

    for (size_t i = 0; i < intervals.size(); i++) {
      if ((intervals[i].lo < range.lo) && (intervals[i].hi > range.hi)) {
        CRange tmp(range.hi + 1, intervals[i].hi);
        if (range.lo != LLONG_MIN)
          intervals[i].hi = range.lo - 1;
        auto insertPos = intervals.begin() + i + 1;
        intervals.insert(insertPos, tmp);
      } else if ((intervals[i].lo >= range.lo) &&
                 (intervals[i].hi <= range.hi)) {
        auto erasePos = intervals.begin() + i;
        intervals.erase(erasePos);
        --i;
      } else if ((range.lo <= intervals[i].lo) &&
                 (range.hi <= intervals[i].hi) &&
                 (range.hi >= intervals[i].lo)) {
        if (range.hi != LLONG_MAX)
          intervals[i].lo = range.hi + 1;
      } else if ((range.lo >= intervals[i].lo) &&
                 (range.hi >= intervals[i].hi) &&
                 (range.lo <= intervals[i].hi)) {
        if (range.lo != LLONG_MIN)
          intervals[i].hi = range.lo - 1;
      }
    }

    return *this;
  }

/**
 *  Subtracts ( removes ) intervals from the vector of intervals
 * 
 *  @param other A CRangeList class object which contains the vector of intervals that are to be removed
 *  @return A reference to the updated CRangeList object
*/
  CRangeList &operator-=(const CRangeList &other) {
    for (size_t i = 0; i < other.intervals.size(); i++) {
      *this -= other.intervals[i];
    }

    return *this;
  }

//  Removes an interval from the vector of intervals
  CRangeList &operator-(const CRange &range) {
    *this -= range;

    return *this;
  }

//  Assignment operator that clears the vector of intervals and inserts a new interval
  CRangeList &operator=(const CRange &range) {
    intervals.clear();
    intervals.push_back(range);

    return *this;
  }

/**
 *  Assignment operator thar clears the vector of intervals and sets a new one
 * 
 *  @param other A CRangeList class object
 *  @return A reference to the updated CRangelist object
*/
  CRangeList &operator=(const CRangeList &other) {
    intervals.clear();
    for (size_t i = 0; i < other.intervals.size(); i++) {
      *this += other.intervals[i];
    }

    return *this;
  }

/**
 *  Relation operator that compares two objects of class CRangeList
 * 
 *  @param other 
 *  @return True if both CRangeList objects are the same, false otherwise
*/
  bool operator==(const CRangeList &other) const {
    if (intervals.size() != other.intervals.size())
      return false;
    for (size_t i = 0; i < intervals.size(); i++) {
      if ((intervals[i].lo != other.intervals[i].lo) ||
          (intervals[i].hi != other.intervals[i].hi))
        return false;
    }
    return true;
  }

//  Opposite to operator==
  bool operator!=(const CRangeList &other) const {
    if (intervals.size() != other.intervals.size())
      return true;
    for (size_t i = 0; i < intervals.size(); i++) {
      if ((intervals[i].lo != other.intervals[i].lo) ||
          (intervals[i].hi != other.intervals[i].hi))
        return true;
    }
    return false;
  }

//  Stream insertion operator
  friend ostream &operator<<(ostream &oss, const CRangeList &other) {
    other.printVector(oss);

    return oss;
  }

private:
  vector<CRange> intervals; //   Vector of intervals

//  Private method that prints the vector of intervals to ostream
  void printVector(ostream &oss) const {
    if (intervals.size() == 0) {
      oss << "{}";
      return;
    }
    oss << "{";
    for (size_t i = 0; i < intervals.size(); i++) {
      if (intervals[i].lo == intervals[i].hi) {
        oss << intervals[i].lo;
        if (i != intervals.size() - 1)
          oss << ",";
        continue;
      }
      oss << "<" << intervals[i].lo << ".." << intervals[i].hi << ">";
      if (i != intervals.size() - 1)
        oss << ",";
    }
    oss << "}";
  }

//  Compare function that compares two intervals
  static bool compareLo(const CRange &a, const CRange &b) {
    return (a.lo < b.lo);
  }

//  Private method that concatenates the vector of intervals so that no duplicate or overlapping intervals are present
  void concatenate(void) {
    if (intervals.size() <= 1)
      return;
    for (size_t i = 0; i < intervals.size() - 1; i++) {
      auto erasePos = intervals.begin() + i + 1;
      if ((intervals[i].lo <= intervals[i + 1].lo) &&
          (intervals[i].hi >= intervals[i + 1].hi)) {
        intervals.erase(erasePos);
        --i;
      } else if ((intervals[i].lo <= intervals[i + 1].lo) &&
                 (((intervals[i].hi < intervals[i + 1].hi) &&
                   (intervals[i].hi >= intervals[i + 1].lo - 1)) &&
                  (intervals[i + 1].lo != LLONG_MIN))) {
        intervals[i].hi = intervals[i + 1].hi;
        intervals.erase(erasePos);
        --i;
      } else if ((intervals[i].lo == intervals[i + 1].lo) &&
                 (intervals[i].hi <= intervals[i + 1].hi)) {
        intervals[i].hi = intervals[i + 1].hi;
        intervals.erase(erasePos);
        --i;
      } else if ((intervals[i].hi == intervals[i + 1].hi) &&
                 (intervals[i].lo >= intervals[i + 1].lo)) {
        intervals[i].lo = intervals[i + 1].lo;
        intervals.erase(erasePos);
        --i;
      }
    }
  }
};

CRangeList CRange::operator+(const CRange &range) {
  CRangeList tmp;
  tmp += *this;
  tmp += range;

  return tmp; //    Returns a newly created CRangeList object
}

CRangeList CRange::operator-(const CRange &range) {
  CRangeList tmp;
  tmp += *this;
  tmp -= range;

  return tmp; //    Returns a newly created CRangeList object
}

string toString(const CRangeList &x) {
  ostringstream oss;
  oss << x;
  return oss.str();
}

int main(void) {
  CRangeList a, b;

  assert(sizeof(CRange) <= 2 * sizeof(long long));
  a = CRange(5, 10);
  a += CRange(25, 100);
  assert(toString(a) == "{<5..10>,<25..100>}");
  a += CRange(-5, 0);
  a += CRange(8, 50);
  assert(toString(a) == "{<-5..0>,<5..100>}");
  a +=
      CRange(101, 105) + CRange(120, 150) + CRange(160, 180) + CRange(190, 210);
  assert(toString(a) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}");
  a += CRange(106, 119) + CRange(152, 158);
  assert(toString(a) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}");
  a += CRange(-3, 170);
  a += CRange(-30, 1000);
  assert(toString(a) == "{<-30..1000>}");
  b = CRange(-500, -300) + CRange(2000, 3000) + CRange(700, 1001);
  a += b;
  assert(toString(a) == "{<-500..-300>,<-30..1001>,<2000..3000>}");
  a -= CRange(-400, -400);
  assert(toString(a) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}");
  a -= CRange(10, 20) + CRange(900, 2500) + CRange(30, 40) +
       CRange(10000, 20000);
  assert(
      toString(a) ==
      "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}");
  try {
    a += CRange(15, 18) + CRange(10, 0) + CRange(35, 38);
    assert("Exception not thrown" == nullptr);
  } catch (const std::logic_error &e) {
  } catch (...) {
    assert("Invalid exception thrown" == nullptr);
  }
  assert(
      toString(a) ==
      "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}");
  b = a;
  assert(a == b);
  assert(!(a != b));
  b += CRange(2600, 2700);
  assert(
      toString(b) ==
      "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}");
  assert(a == b);
  assert(!(a != b));
  b += CRange(15, 15);
  assert(toString(b) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41.."
                        "899>,<2501..3000>}");
  assert(!(a == b));
  assert(a != b);
  assert(b.includes(15));
  assert(b.includes(2900));
  assert(b.includes(CRange(15, 15)));
  assert(b.includes(CRange(-350, -350)));
  assert(b.includes(CRange(100, 200)));
  assert(!b.includes(CRange(800, 900)));
  assert(!b.includes(CRange(-1000, -450)));
  assert(!b.includes(CRange(0, 500)));
  a += CRange(-10000, 10000) + CRange(10000000, 1000000000);
  assert(toString(a) == "{<-10000..10000>,<10000000..1000000000>}");
  b += a;
  assert(toString(b) == "{<-10000..10000>,<10000000..1000000000>}");
  b -= a;
  assert(toString(b) == "{}");
  b += CRange(0, 100) + CRange(200, 300) - CRange(150, 250) + CRange(160, 180) -
       CRange(170, 170);
  assert(toString(b) == "{<0..100>,<160..169>,<171..180>,<251..300>}");
  b -= CRange(10, 90) - CRange(20, 30) - CRange(40, 50) - CRange(60, 90) +
       CRange(70, 80);
  assert(toString(b) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160.."
                        "169>,<171..180>,<251..300>}");

  return EXIT_SUCCESS;
}