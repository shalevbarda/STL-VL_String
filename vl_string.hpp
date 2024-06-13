//
// Created by Shalev Michael Barda on 11/04/2024.
//
//<-----------------Description Section----------------------->
// This file contains the implementation of the vl_string class,
// a simple string class utilizing vl_vector to store characters.
// It offers basic string operations such as appending, and conversion
// to std::string. The vl_string class implemented using a vl_vector<char>
// as the underlying data structure, allowing for dynamic resizing as needed.
// This implementation aims for efficiency and simplicity,
// providing a versatile string handling solution with
// customizable static capacity.
//<-----------------------HEADER----------------------->
//--------Header Guards-----------//

// Header guards are used to prevent multiple inclusions of the header file
// in the same translation unit, which can lead to compilation errors.
// The #ifndef, #define, and #endif directives ensure that the contents
// of the header file are only included once.

#ifndef _VL_STRING_HPP_
#define _VL_STRING_HPP_

//<------------------DEFINE & INCLUDES--------------------->
#define STATIC_CAPACITY 16 // for not using magic numbers

//<------------------DEFINE & INCLUDES--------------------->
#include "vl_vector.hpp"
#include <cstring> // For strlen, strcpy.
//#include <string> // For std::string.

//<-----------------------IMPLEMENTATION----------------------->
template<size_t StaticCapacity=STATIC_CAPACITY >
class vl_string : public vl_vector<char, StaticCapacity>
{
 private:
  // No private members are needed for this implementation.
  // The vl_vector<char, StaticCapacity> class provides all the necessary
 public:
  //<--------Constructors and Destructor---------->
  /**  * Default constructor.
         Runtime complexity: O(1).
  */

  vl_string() : vl_vector<char, StaticCapacity>() {}
    // Constructor of vl_vector<char, StaticCapacity> is called implicitly


  /**  * Copy constructor.
         Runtime complexity: O(n) - number of chars.
  */
  vl_string (const vl_string &other) : vl_vector<char, StaticCapacity> (other)
  {}
    // Copy constructor of vl_vector<char,StaticCapacity> called implicitly

  /**  * Implicit constructor. new vl_string using
         sequence based constructor of vl_vector.
         Runtime complexity: O(n) - number of chars.
  */
  vl_string (const char *str) : vl_vector<char, StaticCapacity>
      (str, str + strlen (str)) {}

  /**  * Destructor.
         Runtime complexity: O(1).
  */
  ~vl_string() = default;
  //doesn't require any explicit cleanup or deallocation
  // because the underlying data is managed by vector_vl,
  // which handles its own memory management.

  /**  * Appends a const char* to the vl_string.
         Runtime complexity: O(n) - number of chars.
  */
  void append (const char *str) noexcept
  {
    this->insert (this->end (), str, str + strlen (str));
  }

  //<--------Operators---------->
  /**  * operator += with const char
         Runtime complexity: O(1).
  */
  vl_string &operator+= (const char c)
  {
      this->push_back (c);
      return *this;
  }

  /**  * operator += with const char*
         Runtime complexity: O(n) - number of chars.
  */
  vl_string &operator+= (const char *str)
  {
    append (str);
    return *this;
  }

  /**  * operator += with vl_vector
         Runtime complexity: O(n) - number of chars.
  */
  vl_string &operator+= (const vl_vector<char, StaticCapacity> &other)
  {
    this->insert (this->end (), other.begin (), other.end ());
    return *this;
  }


  /**  * operator + with const char
         Runtime complexity: O(1).
  */
  vl_string operator+ (const char c) const
  {
    vl_string result = *this;
    result += c;
    return result;
  }

  /**  * operator + with const char*
         Runtime complexity: O(n) - number of chars.
  */
  vl_string operator+ (const char *str) const
  {
    vl_string result = *this;
    result += str;
    return result;
  }

  /**  * operator + with vl_vector
         Runtime complexity: O(n) - number of chars.
  */
  vl_string operator+ (const vl_vector<char, StaticCapacity> &other) const
  {
    vl_string result = *this;
    result += other;
    return result;
  }

  /**  * Implicit casting operator to std::string
         Converts the vl_string to a std::string.
         good for using std::string functions like print etc.
         Runtime complexity: O(n) - number of chars.
  */
  operator std::string () const
  {
    std::string result(this->begin(), this->end());
    // range constructor of std::string.
    return result;
  }

};
#endif //_VL_STRING_HPP_
