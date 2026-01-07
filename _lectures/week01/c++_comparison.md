---
title: C++ Syntax Comparison with Python and Java
layout: single
classes: wide
week: 1
category: lectures  # this is needed so show_in_list: false will cause page to be hidden
show_in_list: false

toc: true
toc_label: "Quick Links"
toc_icon: "bookmark"  # corresponding Font Awesome icon name (without fa prefix)
toc_sticky: true

---

Below are examples of complete programs using functions, arrays / lists, and classes in C++, Python, and Java. Each group of programs performs the same functionality so you can compare C++ to a language you might be more familiar with.

You can also download all the [source code](resources\c++_comparison\c++_comparison.zip) directly.

**Note:** In programming the Photon 2 for this course, we will not use the standard input / output in C++ (e.g. `cin` and `cout`) and we will be creating custom classes, but they are included below.



## Basic Syntax

### Basic Syntax: C++ ([driver.cpp](resources\c++_comparison\1_syntax\c++\driver.cpp))

```c++
// Comments: single line
/*
  Comments: Multi-line

*/

/*
Importing libraries
  To include a library or file in your code, use #include at the top of the file
  Angle brackets (<...>) indicate that the library/file is a standard
    C++ library (and stored in Visual Studio's path somewhere)
  For example, to import the C++ iostream library, use
    #include <iostream>

  Quotations marks ("...") indicate that the file is something you
    created (and in the same directory as this current code)
  For example, to import a file you wrote called "coffee.cpp", use
    #include "coffee.cpp"

Useful libraries
  iosteam    -    input (keyboard) and output (console)
  string    -    creating, accessing, manipulating std::strings


Program structure
  The "int main()" function is where the program starts, which is equivalent to 
    "public static void main" in Java or "main()" in Python
    Python: note that you do NOT have to call main() yourself
  One difference is that the main function MUST return a value
    Hence at the end of every "main" you will return 0
      int main()
      {
        ...
        ...
        return 0;
      }

Basic syntax
  C++ is caSe-SeNiSiTiVe
  You can name variables/classes however you want to, but in these examples:
    - Variables and functions are named usingCamelCase
    - Classes are named with EveryWordCapitalized
  All statements (e.g. variable declarations, function calls, etc.)
    end with a semi-colon
  Blocks of code are denoted with curly braces { }
    Python: White space is ignored--curly braces are the only way to 
      enclose a block
Namespaces
  Objects that are part of the standard library are in the "std" namespace
    this is why we use std::string, std::cout, std::cin, etc.

Variables
  Variables must explicitly be given a type when declaredd
  For example,
    int a;
    float x = 9.8;
  Common variables primitives (i.e. simple variables, not objects)
    int    -    integers (see also long)
    double  -    floating point numbers (see also float)
    bool  -    booleans (either true or false)
    char  -    number that represents an ASCII character (letter)

  std::strings are objects (not primitives) and enclosed with "..."
    Java: note the lowercase 's'

Output
  To print to the console, use std::cout
    std::cout << "SOME std::string TO PRINT"
  Multiple statements can be chained together
    std::cout << "Hello" << " " << "World";
  Variables can be concatenated to the output also
    int num = 8;
    std::cout << "The value of variable num is " << num;

Input
  To read input from the keyboard, use std::cin
    int a;
    std::cin >> a;
  Multiple input can be chained together
    int a;
    double x;
    std::string message;
    std::cin >> a >> x >> message;
  Note how you do not need to specify the type of input you are reading
    and it works with primitives and std::strings
  std::cin will read until it encounters any white space 
  std::getline will read until there is a '\n' so use it to read in multiple words
      std::string sentence;
      std::getline(std::cin, sentence);
  Quirk (particularly for Python programmers): 
    Just like nextInt() in Java, std::cin >> ... reads the user input but leaves the
    '\n' on the input buffer (here the '\n' is the user hitting enter.
    This means that if a std::getline() follows a std::cin >> ..., 
      the std::getline() will see the leftover '\n' and not the new input.
    Thus, whenever you have std::cin >> ... followed by std::getline(), you need
      to remove the leftover '\n' using std::cin.ignore()
    For example
      int a;
      std::string sentence;
      std::cin >> a;
      std::cin.ignore();
      std::getline(std::cin, sentence);

If / else if / else
  Virtually the same as in Java / Python
  Python: Note that "elif" is replaced with "else if"

While
  Virtually the same as in Java / Python
  C++ also has also has a variation called "do while" 
    see http://www.cplusplus.com/doc/tutorial/control/

For loops
  Java: virtually the same
  Python: for loops operate very differently in C++
    see http://www.cplusplus.com/doc/tutorial/control/
  
*/
#include <iostream>    //needed for std::cout and std::cin
#include <string>    //needed for std::string objects

int main()
{
  // variable declarations
  int a = 8;
  double x;
  x = 3.14;
  std::string message = "Hello World!";
  bool gotMilk = true;

  // Output
  std::cout << "This will print to the console\n";
  std::cout << message << std::endl;
  std::cout << "The value of X is " << x << std::endl;
  std::cout << "---------------------------\n";

  // input
  std::cout << "Enter a integer: ";
  std::cin >> a;
  std::cout << a << std::endl;

  std::cout << "Enter a single word: ";
  std::cin >> message;
  std::cin.ignore(); // clear extra newline
  std::cout << message << std::endl;

  std::cout << "Enter multiple words: ";
  std::getline(std::cin, message);
  std::cout << message << std::endl;
  std::cout << "---------------------------\n";

  // If statements
  if (gotMilk == true)
  {
    std::cout << "You've got milk\n";
  }
  else if (gotMilk == false)
  {
    std::cout << "There is an absence of milk!\n";
  }
  else
  {
    std::cout << "This will never execute because boolean variables can only be T or F\n";
  }
  std::cout << "---------------------------\n";

  // while loops
  a = 7;
  while (a != 0)
  {
    std::cout << "This loop will continue until you enter 0." << std::endl;
    std::cout << "Enter a number: ";
    std::cin >> a;
  }
  std::cout << "----------------------------\n";

    
  // for loops
  std::cout << "Enter a positive number to sum: ";
  std::cin >> a;
  int total = 0;
  for (int i = 0; i <= a; i++)
  {
    total += i;
  }
  std::cout << "The summation of " << a << " is " << total << std::endl;
  std::cout << "---------------------------\n";

  return 0;
}

```

### Basic Syntax: Python ([main.cpp](resources\c++_comparison\1_syntax\python\main.py))

```python
#define main function

def main():
    # variable declarations
    a = 8
    # x     # there is no point in Python to declare a variable 
            # without initializing it
    x = 3.14
    message = "Hello World!"
    gotMilk = True

    #  Output
    print("This will print to the console")
    print(message)
    print("The value of X is " + str(x))
    print("----------------------------")

    #  input
    a = int(input("Enter a integer: "))
    print(a)

    message = input("Enter a single word: ")
    print(message)

    message = input("Enter multiple words: ")
    print(message)
    print("----------------------------")

    #  If statements
    if gotMilk == True:
        print("You've got milk!")
    elif gotMilk == False:
        print("There is an absence of milk!")
    else:
        print("This will never execute because boolean variables can only be T or F")
    
    print("----------------------------")

    #  while loops
    a = 7
    while a != 0:
        print("This loop will continue until you enter 0.")
        a = int(input("Enter a number: "))
    print("----------------------------")

    
    #  for loops
    a = int(input("Enter a positive number to sum: "))
    total = 0
    for i in range(a + 1):
        total += i
    
    print("The summation of " + str(a) + " is " + str(total))
    print("----------------------------")


# call main function
main()
```



### Basic Syntax: MATLAB ([main.m](resources\c++_comparison\1_syntax\matlab\main.m))

```matlab
% Comments: single line
%{
  Comments: Multi-line
%}

% Program structure
%  MATLAB scripts execute commands in order
%  No explicit "main" function is strictly required for simple scripts,
%  but you can define one to match the C++/Java structure.

function main()
% variable declarations
% Variables are dynamically typed (no int/double declaration needed)
    a = 8;
    x = 3.14;
    message = "Hello World!"; % String using double quotes 
    gotMilk = true;

    % Output
    disp("This will print to the console");
    disp(message);
    fprintf("The value of X is %f\n", x); % using fprintf for formatted output
    disp("---------------------------");

    % Input
    % input() parses the input. 
    a = input("Enter a integer: ");
    disp(a);

    % Reading a string
    % The "s" argument tells MATLAB to read as a string/character array
    message = input("Enter a single word: ", "s");
    disp(message);

    % MATLAB input reads the whole line if "s" is used, effectively like getline
    message = input("Enter multiple words: ", "s");
    disp(message);
    disp("---------------------------");

    % If statements
    if gotMilk == true
        disp("You've got milk");
    elseif gotMilk == false
        disp("There is an absence of milk!");
    else
        disp("This will never execute");
    end
    disp("---------------------------");

    % while loops
    a = 7;
    while a ~= 0
        disp("This loop will continue until you enter 0.");
        a = input("Enter a number: ");
    end
    disp("----------------------------");

    % for loops
    a = input("Enter a positive number to sum: ");
    total = 0;
    % MATLAB loops are inclusive of the end range (0 to a)
    for i = 0:a
        total = total + i;
    end

    % output result
    fprintf("The summation of %d is %d\n", a, total);
    disp("---------------------------");

% call main
main()
```



### Basic Syntax: Java ([Program.java](resources\c++_comparison\1_syntax\java\Program.java))

```java
import java.util.Scanner;

public class Program {

  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);

    // variable declarations
    int a = 8;
    double x;
    x = 3.14;
    String message = "Hello World!";
    boolean gotMilk = true;

    // Output
    System.out.println("This will print to the console");
    System.out.println(message);
    System.out.println("The value of X is " + x);
    System.out.println("----------------------------");

    // input
    System.out.println("Enter a integer: ");
    a = input.nextInt();
    System.out.println(a);

    System.out.println("Enter a single word: ");
    message = input.next();
    input.nextLine(); // clear extra newline
    System.out.println(message);

    System.out.println("Enter multiple words: ");
    message = input.nextLine();
    System.out.println(message);
    System.out.println("----------------------------");

    // If statements
    if (gotMilk == true) {
      System.out.println("You've got milk!");
    } else if (gotMilk == false) {
      System.out.println("There is an absence of milk!");
    } else {
      System.out
          .println("This will never execute because boolean variables can only be T or F");
    }
    System.out.println("----------------------------");

    // while loops
    a = 7;
    while (a != 0) {
      System.out.println("This loop will continue until you enter 0.");
      System.out.println("Enter a number: ");
      a = input.nextInt();
    }
    System.out.println("----------------------------");

    
    // for loops
    System.out.println("Enter a positive number to sum: ");
    a = input.nextInt();
    int total = 0;
    for (int i = 0; i <= a; i++) {
      total += i;
    }
    System.out.println("The summation of " + a + " is " + total);
    System.out.println("----------------------------");

  }
}

```



## Functions

### Functions: C++ ([driver.cpp](resources\c++_comparison\2_functions\c++\driver.cpp))

```c++

/*
Creating and using functions
  As in Java/Python, C++ has "function declarations" where you specify what the function does
    and "function calls" where you actually use the function
  Functions must be declared before they are used. So if the functions are used in main
    they must be declared before main.
 
  If two functions call each other, this issue can be solved, using something called
    "function prototypes". But don't worry about that just yet.
 
  A program in a single file will typically be structured as:

    #include ...
    
    // any function declarations

    int main()
    {
      ...
    }

  

Function syntax
  RETURN_TYPE NAME_OF_FUNCTION (INPUT_TYPE1 INPUT_PARAMETER1, ... )
  {
    BODY_OF_FUNCTION
  }
 
  For example,
    int calcSquare(int numberToSquare)
    {
      return numberToSquare * numberToSquare;
    }

Return type
  Every function must specify a return type (e.g. int, bool, string)
    and should end with a return statement
  If the function does not return anything, the return type must be "void"
    In this case, the return statement is optional
    
Input parameters
  Functions can take zero or more input parameters
  Every input parameter must have a data type specified
  For example,
    void printThings(string word, int num, double pi)

Functions vs. Methods
  Technically, functions are free-standing executing blocks
    while methods are blocks that a part of a class (just like Python)
  Notice that this file defines functions WITHOUT using classes

  Java:
    Java does not have this concept of functions because all "executing blocks"
      are part of some class of everything is a method.
    You can consider "functions" to be similar to "public static void"
      methods you created--basically you can call the functions without
      creating an instance of a class

Default Values
  Python: Generally, C++ doesn't use default values in functions.
    Instead, the preferred approach is to "overload functions,"
    which is explained in the "Inheritance" example

*/

#include <iostream>

// Function declarations

// CalcSumSquares
// Takes two parameters (the numbers to square and then sum)
// Returns the result of the computation as an integer
int calcSumSquares(int num1, int num2)
{
  return num1 * num1 + num2 * num2;
}

// displayResult
// Takes three parameters to display to cout
// Returns nothing (void)
void displayResult(int num1, int num2, int result)
{
  std::cout << "The sum of squares of " << num1 << " and " << num2 << " is " << result;
  std::cout << std::endl << std::endl;
  
  //since this function returns void, there is no need for a return statement
}

// main
int main()
{
  int a = 0, b = 0, result = 0;

  std::cout << "Enter two integers: ";
  std::cin >> a >> b;

  //calling function calcSumSquares with inputs a and b
  //and storing the return value in result
  result = calcSumSquares(a, b);  

  //calling function display result
  //return type is void so there is not result to store
  displayResult(a, b, result);
  return 0;
}
```



### Functions: Python ([main.py](resources\c++_comparison\2_functions\python\main.py))

```python
#define main function

def main():
  a = 0
  b = 0
  result = 0

  print("Enter two integers: ")
  a = int(input())
  b = int(input())

  result = calcSumSquares(a, b)
  displayResult(a, b, result)


def calcSumSquares(num1, num2):
  return num1 * num1 + num2 * num2


def displayResult(num1, num2, result):
  print("The sum of squares of " +
      str(num1) + " and " + str(num2) +
      " is " + str(result))


# call main function
main()
```



### Functions: MATLAB ([main.m](resources\c++_comparison\2_functions\java\main.m))

```matlab
% define main function
% In MATLAB, if a script contains local functions (like calcSumSquares below), 
% the script itself must be implemented as a function (like main here).

function main()
  a = 0;
  b = 0;
  result = 0;

  disp("Enter two integers: ");
  a = input("");
  b = input("");

  % calling function calcSumSquares with inputs a and b
  result = calcSumSquares(a, b);

  % calling function display result
  displayResult(a, b, result);

end

% calcSumSquares
% Takes two parameters
% Returns the result of the computation
function result = calcSumSquares(num1, num2)
  result = num1 * num1 + num2 * num2;
end


% displayResult
% Takes three parameters to display to command window
% Returns nothing (so no return variable specified in function definition)
function displayResult(num1, num2, result)
  fprintf("The sum of squares of %d and %d is %d\n", num1, num2, result);
end

% call main function
main()
```



### Functions: Java ([Program.java](resources\c++_comparison\2_functions\java\Program.java))

```java

import java.util.Scanner;

public class Program {

  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    int a = 0, b = 0, result = 0;

    System.out.println("Enter two integers: ");
    a = input.nextInt();
    b = input.nextInt();

    result = calcSumSquares(a, b);

    displayResult(a, b, result);

  }

  public static int calcSumSquares(int num1, int num2) {
    return num1 * num1 + num2 * num2;
  }

  public static void displayResult(int num1, int num2, int result) {
    System.out.println("The sum of squares of " + num1 + " and " + num2
        + " is " + result);
  }
}

```

## Arrays / Lists

### Arrays / Lists: C++

```c++
/*
Array concept
  Arrays in C++ are similar to very arrays in Java and "somewhat" similar lists in Python
  One major difference in C++ is that arrays are not objects
    This means they are a little more difficult to work with

  Arrays are a data structure that store variables which can be accessed by an integer index
  Indices start at zero and go up to (ARRAY_SIZE - 1)

  Python: 
    Arrays can NOT be resized after they are created
      As a result, you can not create empty arrays and then append to them
    Every element of an array MUST hold the same type of data (unlike lists)
  Java / Python:
    Arrays can NOT tell you their own size (since they are not objects)
    This means you must always keep track of the size yourself

Creating arrays
  DATA_TYPE NAME_OF_ARRAY [ARRAY_SIZE];
  For example,
    int numbers [5];
    string words [26];
  
  Java / Python:
    The size of the array can NOT be determined at run-time.
      It must be a known constant size in the code.
      This means you can NOT ask the user for a size and THEN create the array
    In the below example, you can use a variable for the size of "numbers" only 
      because SIZE_OF_ARRAY is a constant

Accessing arrays
  Use the [ ] operator
    int numbers [5];
    numbers[0] = 36;
    cout << numbers[0];

Arrays as arguments to functions
  To pass an array as input to a function, simply use the name of the array
    int numbers[5];
    ...
    int result = calcSum(numbers);

  To write a function prototype with an array input, use the following syntax
    int calcSum(int numArray[])
 
unsigned
  unsigned is a type modifier for integral types, that specifies the number is
    greater than or equal to zero, and cannot be negative.
  
  To declare an integer as unsigned, simply add unsigned in front of int:
    unsigned int myUnsignedInt;
 
const
  const means that the variable cannot be modified after declaration. So
    if you create a const integral value, you can use that as a size of the
    array, since it is a known constant size.

*/
#include <iostream>

//function defintion
// calcSum takes in two parameters:
//    - The integer array
//    - The size of the array
int calcSum(int numArray[], unsigned int size)
{
  int sum = 0;
  for (unsigned int i = 0; i < size; i++)
  {
    sum += numArray[i];
  }
  return sum;
}

//main
int main()
{
  const unsigned int SIZE_OF_ARRAY = 4; // array MUST be initalized with constant values

  int numbers[SIZE_OF_ARRAY];    // do not need to use NEW to initialize
                  // however, you can not have the size be dynamically
                  // assigned (i.e. by user input at run-time

  //fill array with user input
  for (unsigned int i = 0; i < SIZE_OF_ARRAY; i++)  // note that arrays in C++ are not objects
  {                          // so they have no mechanism to store
    std::cout << "Enter num: ";            // the array size
    std::cin >> numbers[i];
  }

  //print array
  std::cout << "The numbers in the array are: ";
  for (unsigned int i = 0; i < SIZE_OF_ARRAY; i++)
  {
    std::cout << numbers[i] << " ";
  }
  std::cout << std::endl;

  int sum = calcSum(numbers, SIZE_OF_ARRAY);
  std::cout << "The sum of the numbers is " << sum << std::endl << std::endl;

  return 0;
}
```



### Arrays / Lists: Python

```python
# define main function
def main():
  numbers = []  # create empty list (no size necessary)
  sizeOfList = 4
  
  # fill list with user input
  for i in range(sizeOfList):
    numbers.append(int(input("Enter num: ")))

  # print list
  print("The numbers in the list are:" )
  for i in range(len(numbers)):
    print(numbers[i])

  # # the following for loop also works
  # # but in C++, a for loop is more similar
  # # to the loop above
  # print("The numbers in the list are:" )
  # for num in numbers:
  #   print(num)


  # call function calcSum and store the return value
  total = calcSum(numbers)
  print("The sum of the numbers is " + str(total))


'''
  calcSum
  input: list of ints
  output: int
  desc: adds all the values in the list and returns the sum
'''
def calcSum(nums):
  total = 0
  for i in range(len(nums)):
    total += nums[i]

  return total


# call main function
main()
```



### Arrays / Lists: MATLAB

```matlab
% define main function
function main()
    % create array of numbers
    % Unlike C++, MATLAB arrays are dynamic and can be resized
    numbers = []; 
    sizeOfArray = 4;
    
    % fill array with user input
    for i = 1:sizeOfArray
        % Note: MATLAB Indices start at 1, unlike C++ which starts at 0
        prompt = "Enter num: ";
        numbers(i) = input(prompt);
    end
    
    % print array
    disp("The numbers in the array are:");
    for i = 1:length(numbers)
        disp(numbers(i));
    end
    
    % call method calcSum and store the return value
    sumVal = calcSum(numbers);
    fprintf("The sum of the numbers is %d\n", sumVal);
end
  
%{
   calcSum
   input: array of ints
   output: int
   desc: adds all the values in the array and returns the sum
%}
function sumVal = calcSum(nums)
    sumVal = 0;
    for i = 1:length(nums)
        sumVal = sumVal + nums(i);
    end
end

% call main
main()
```



### Arrays / Lists: Java

```java
import java.util.Scanner;

public class Program {

  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    
    //create array of numbers of size 4
    int sizeOfArray = 4;
    int [] numbers = new int [sizeOfArray];
    
    //fill array with user input
    for (int i = 0; i < numbers.length; i++) {
      System.out.println("Enter num: ");
      numbers[i] = input.nextInt();
    }
    
    //print array
    System.out.println("The numbers in the array are:" );
    for (int i = 0; i < numbers.length; i++){
      System.out.println(numbers[i]);
    }
    
    //call method calcSum and store the return value
    int sum = calcSum(numbers);
    System.out.println("The sum of the numbers is " + sum);
  }
  
  /*
   * calcSum
   * input: array of ints
   * output: int
   * desc: adds all the values in the array and returns the sum
   */
  public static int calcSum(int[] nums) {
    int sum = 0;
    for (int i = 0; i < nums.length; i++) {
      sum += nums[i];
    }
    return sum;
  }

}
```

## Creating Class Definitions

### Class definition: C++ (`Order.h`)

```c++
/*
Rob Parke
Viterbi School of Engineering
University of Southern California
Java, C++, and Python Review
*/

// This file defines the prototype (aka outline) of the Order class
 
#pragma once      // Required at the top of new header (.h) files

public class Order {
  // variables declaration
  private:
    String name;
    int pounds;
    double costPerPound;
  
  public:
    //default constructor
    Order();
    
    // get / set methods
    string getName();
    int getPounds();
    double getCostPerPound();
    
    void setName(string newName);
    void setPounds(int newPounds);
    void setCostPerPound(double newCostPerPound);
    
    // methods
    /* calcCost
     * input: none
     * output: returns pounds * costPerPound
     */
    double calcCost();
    
    /* displayOrder
     * input: none
     * output: none
     * side-effect: prints a summary of the order to the screen
     */
    void displayOrder();
}
```



### Class definition: Python (`Order.py`)

```python
class Order(object):
  # default constructor
  def __init__(self):
    # create instance variables for the objects
    self.__name = ""
    self.__pounds = 0
    self.__costPerPound = 0.0
	
	# get / set methods
  def getName(self):
    return self.__name

  def getPounds(self):
    return self.__pounds

  def getCostPerPound(self):
    return self.__costPerPound

  def setName(self, newName):
    self.__name = newName

  def setPounds(self, newPounds):
    self.__pounds = newPounds

  def setCostPerPound(self, newCostPerPound):
    self.__costPerPound = newCostPerPound


  # methods
  '''
   calcCost
   input: none
   output: returns pounds * costPerPound
  '''
  def calcCost(self):
    return self.__pounds * self.__costPerPound


  '''
   displayOrder
   input: none
   output: none
   side-effect: prints a summary of the order to the screen
  '''
  def displayOrder(self):
    print("Order: " + self.__name + " for " +
        str(self.__pounds) + " lbs @ $" +
        str(self.__costPerPound) + "/lb")
```



## Class definition: MATLAB

```matlab
% In MATLAB, classes are defined in a 'classdef' block.
% We inherit from 'handle' so that the object behaves like a Reference type 
% (like Java/Python/C++ objects). If we don't, it behaves like a Value type 
% (like a C++ struct passed by value).

classdef Order < handle
   properties (Access = private)
      name
      pounds
      costPerPound
   end
   
   methods
      % default constructor
      function obj = Order()
          obj.name = "";
          obj.pounds = 0;
          obj.costPerPound = 0.0;
      end
      
      % get / set methods
      function n = getName(obj)
          n = obj.name;
      end
      
      function p = getPounds(obj)
          p = obj.pounds;
      end
      
      function c = getCostPerPound(obj)
          c = obj.costPerPound;
      end
      
      function setName(obj, newName)
          obj.name = newName;
      end
      
      function setPounds(obj, newPounds)
          obj.pounds = newPounds;
      end
      
      function setCostPerPound(obj, newCost)
          obj.costPerPound = newCost;
      end
      
      % methods
      %{
        calcCost
        input: none
        output: returns pounds * costPerPound
      %}
      function c = calcCost(obj)
          c = obj.pounds * obj.costPerPound;
      end
      
      %{
        displayOrder
        input: none
        output: none
        side-effect: prints a summary of the order to the screen
      %}
      function displayOrder(obj)
          fprintf("Order: %s for %d lbs @ $%0.2f/lb\n", ...
              obj.name, obj.pounds, obj.costPerPound);
      end
   end
end
```



### Class definition: Java (`Order.java`)

```java
public class Order {
  // variables declaration
  private String name;
  private int pounds;
  private double costPerPound;
  
  //default constructor
  public Order() {
    name = "";
    pounds = 0;
    costPerPound = 0.0;
  }
  
  // get / set methods
  public String getName(){ return name;   }
  public int getPounds() { return pounds; }
  public double getCostPerPound() { return costPerPound;   }
  
  public void setName(String newName) { name = newName;   }
  public void setPounds(int newPounds) {  pounds = newPounds;  }
  public void setCostPerPound(double newCostPerPound){ costPerPound = newCostPerPound;
  }
  
  // methods
  /* calcCost
   * input: none
   * output: returns pounds * costPerPound
   */
  public double calcCost(){
    return pounds * costPerPound;
  } 
  
  /* displayOrder
   * input: none
   * output: none
   * side-effect: prints a summary of the order to the screen
   */
  public void displayOrder(){
    System.out.println("Order: " + name + " for " + pounds +
              " lbs @ $" + costPerPound + "/lb");
  }
}
```

## Using Classes to Create Objects

### Using classes: C++

```c++
/*
Rob Parke
Viterbi School of Engineering
University of Southern California
Java, C++, and Python Review
*/


/*
Classes concept
  Very similar to Java / Python with most syntax changes
  
  Class can contain instance variables and instance methods
  Methods and variables can have an access level (public, private, or protected)
 
Definition
  As in Java / Python, classes are defined in a block of code and begin with the word "class"
 
  Class definitions end with a SEMI-COLON;
 
Constructor
  The constructor method always has the same name as the class
 
  Python: There is no __init__.  Instead, the class name serves as the constructor.
    For instance, the class "Coffee" would have a constructor called
    Coffee()
 
Public / Private and declaring instance variables
  Classes in C++ have a public and private section.
  Within each section you specify all the methods and variables that are either public or private
 
  For example, if a class has private int variable foo and public methods getFoo and setFoo, use
    private:
      int foo;
    public:
      int getFoo()
        ...
      void setFoo(int num)
        ...
 
  Java: You do not specify "public" or "private" for every variable / method.
    Rather, you include all relevant variables / methods with section.

  Python: A major difference in C++ is that you MUST define all instance variables
    in the class defintion (i.e. OUTSIDE of the constructor).
    For example, instead of creating private variale "self.__foo" in __init__,
      you instead use "int foo" in the private section of the class.
    This follows the C++ principle that you must define ahead of time all
      variables / functions before using them
 
Parameters by value vs. by reference
  When parameters are passed to functions, there are two primary options:
    - If a parameter is passed by value, a copy of the parameter is passed
      to the function. Generally, basic types (such as int, double, etc)
      should be passed by value.
    - If a parameter is passed by reference, the variable is handed off to the
      class, and no copy is made. Generally, object types (such as std::string,
      and custom classes) should be passed by reference.
    ** A major exception to this is arrays. Arrays are never copied, and are
      more or less "automatically" passed by reference
  
  We have been passing parameters by value in our functions so far. So for
    example, calcSquare takes in the parameter num by value:
      int calcSquare(int num)
      {
        return num * num;
      }
 
  To pass a parameter by reference, an ampersand & is placed between the type and the
    parameter name. So for example, this function takes in a std::string by reference:
      void printString(std::string& toPrint)
      {
        std::cout << toPrint << std::endl;
      }
 
Note: In this example, we declare our class and use it in the same file.
  Typically, this is not the case and we create separate .h/.cpp files for each class
  (as in the Inheritance example #5).
 
As with functions, classes must be declared before any code that uses them.
 
*/

#include "Order.h"  // This is our custom Rectangle 
#include <iostream>    //needed for cin / cout
#include <string>    //needed for strings


// function prototype
void finalizeOrder(Order& newOrder) // Pass by reference!
{
  double cost = 0;
  
  newOrder.displayOrder();
  cost = newOrder.calcCost();
  std::cout << "Your order costs $" << cost;
  
}

int main() {
  //const means the variable is a CONSTANT and can not change
  const double COST_PER_POUND = 7.99;

  //create an order object
  //Java: note we do not use NEW in the basic case of constructing
  // a class as a local variable
  Order order1;
  std::string tempName = "";
  int tempPounds = 0;
  
  std::cout << "Enter coffee name (one word please): ";
  std::cin >> tempName;
  order1.setName(tempName);

  std::cout <<"Enter # of pounds: ";
  std::cin >> tempPounds;
  order1.setPounds(tempPounds);

  order1.setCostPerPound(COST_PER_POUND);

  finalizeOrder(order1);

  std::cout << std::endl << std::endl;

  return 0;
}
```



### Using classes: Python

```python
# import Order class
from Order import Order

# define CONSTANT
COST_PER_POUND = 7.99

# define main function
def main():

  order1 = Order()
  tempName = ""
  tempPounds = 0

  tempName = input("Enter coffee name (one word please): ")
  order1.setName(tempName)

  tempPounds = int(input("Enter # of pounds: "))
  order1.setPounds(tempPounds)

  order1.setCostPerPound(COST_PER_POUND)

  finalizeOrder(order1)



def finalizeOrder(newOrder):
  cost = 0

  newOrder.displayOrder()
  cost = newOrder.calcCost()
  print("Your order costs $" + str(cost))



# call main function
main()
```



### Using classes: MATLAB

```matlab
% define CONSTANT
% In MATLAB functions, variables are local, so we define this in main
function main()
    COST_PER_POUND = 7.99;
    
    % create an order object
    order1 = Order();
    
    tempName = input("Enter coffee name (one word please): ", "s");
    order1.setName(tempName);
    
    tempPounds = input("Enter # of pounds: ");
    order1.setPounds(tempPounds);
    
    order1.setCostPerPound(COST_PER_POUND);
    
    finalizeOrder(order1);
end

function finalizeOrder(newOrder)
    cost = 0;
    
    newOrder.displayOrder();
    cost = newOrder.calcCost();
    fprintf("Your order costs $%0.2f\n", cost);
end

% call main
main()
```



### Using classes: Java

```java
/*
Rob Parke
Viterbi School of Engineering
University of Southern California
Java, C++, and Python Review
*/

import java.util.Scanner;
public class Program {

  public static void main(String[] args) {
    final double COST_PER_POUND = 7.99;
    
    Scanner input = new Scanner(System.in);
    Order order1 = new Order();
    String tempName = "";
    int tempPounds = 0;
    
    System.out.println("Enter coffee name (one word please): ");
    tempName = input.next();
    order1.setName(tempName);
    
    System.out.println("Enter # of pounds: ");
    tempPounds = input.nextInt();
    order1.setPounds(tempPounds);
    
    order1.setCostPerPound(COST_PER_POUND);

    finalizeOrder(order1);
    
  }
  
  public static void finalizeOrder(Order newOrder){
    double cost = 0;
    
    newOrder.displayOrder();
    cost = newOrder.calcCost();
    System.out.println("Your order costs $" + cost);
    
  }
}
```