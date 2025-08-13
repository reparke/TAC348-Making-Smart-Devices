/*
Rob Parke
Viterbi School of Engineering
University of Southern California
Java, C++, and Python Review
*/

#pragma once

#include <string>  //needed for string objects

#include "Shape.h"  //needed to refer to Shape objects

/*
Inheritance
The Rectangle class will be derived from the Shape class
  AKA Rectangle is the child / sub class, and Shape is the parent / super class
  The notation to indicate this is the following

    class CHILD_CLASS : ACCESS_SPECIFIER PARENT_CLASS
    {
      // rest of class definition
    };

  The access specifiers (public, protected, and private) will be covered in TAC
365, but it affects the derived class' access to the base class' members.  For
now we will use "public", which is the easiest to understand


Overloaded Methods (new for Python)
  Overloading a method (or a function) means you create two functions
    with identical names--the only difference is that the number and data type
    of the arguments changes
  For example, you could create two methods called averageNumbers--one which
takes two arguments and one with takes three

      double averageNumbers (double n1, double n2);

      double averageNumbers (double n1, double n2, double n3);


  We would say that the averageNumbers method has been overloaded to take 2 or 3
arguments. You can now use either version in your program. Note that you must
still provide method implementations for each version separately in the .cpp
file

Overloaded Constructors (new for Python)
  Overloading constructors is the same as overloading methods, but there are
some useful terms to know

  Default constructor: constructor that takes no input arguments
  Overloaded constructor: constructor takes take input arguments

*/
class Rectangle : public Shape {
   private:  // new instance variables for Rectangle objects
    double length;
    double width;

   public:
    // default constructor
    Rectangle();

    // overloaded constructor
    Rectangle(std::string& inputName, double inputlength, double inputWidth);

    // accessor / mutator
    void setLength(double inputlength);
    void setWidth(double inputWidth);

    double getLength();
    double getWidth();

    // methods
    double calcArea();

    void display();
};  // class ends with a semi-colon