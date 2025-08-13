---
marp: true
theme: itp
paginate: true

week: 1
category: lectures
title: C++ Syntax

---

<!-- headingDivider: 2 -->

# C++ Syntax Overview

## C++ Compared to Python and Java

* For comparison of programs side-by-side using functions, arrays / lists, and functions using C++, Python, and Java, see this page:
  [C++ comparison](https://reparke.github.io/TAC348-Making-Smart-Devices/c++_comparison)

## C++ and Other Languages

* C++ are **conceptually** similar to other languages
  - Loops, functions, variables, etc. are in both
* The biggest difference is the specific **syntax** is new
* There are a few other things to note that we will discuss as we go
  

## Example program

```c++
/* Awesome 
Photon 2 Program
*/
#include "OLED_screen.h"	//library

const int MAX_PRESSES = 4;	//globcal constant
int numPresses = 0;			//global variable
bool areDone = false;

void loop() {
  if (numPresses >= MAX_PRESSES) {
      areDone = true;
  }
}
```
## Comments

* `//` are single line comments
* `/* ... */`are multiple line comments

```c++
/* Awesome 
Photon 2 Program
*/
#include "OLED_screen.h"	//library
```
## Ending Lines

* Every executable line of code ends with a semi-colon `;`

```
int age = 4;
String animal = "cat";
```

* Code blocks (e.g. loops, functions, ifs) **do not** end with semi-colons

```c++
void loop() {
  if (numPresses >= MAX_PRESSES) {
      areDone = true;
  }
}
```
## Code Blocks

* Blocks of code are started and ended with `{ }`
* Whitespace is doesn't matter

```c++
void loop() {
  if (numPresses >= MAX_PRESSES) {
      areDone = true;
  }
}
```

```c++
void loop() {  if (numPresses >= MAX_PRESSES) {areDone = true;  }}
```

Both of the code blocks are correct and equivalent

## Variables

```c++
type variableName = value

int numPresses = 0;
```

* You must always specify the type of a variable when you declare it
* Ex: `int`, `double`, `String`, `bool`

## Constants

```c++
const type variableName = value;

const int MAX_PRESSES = 4;
```

* `const` means the variable is a constant and **cannot** change after you initialize it

## Aside: C++ Typing

* Python and JavaScript are called **weakly typed** languages: 
  - A variable can be hold a string, and then later hold an int

```python
age = "Jurassic"
age = 34
```

* C++ is called **strongly typed** language: 
  - A variable must be declared as a type and **cannot**  change

```c++
String age = "Jurassic";
age = 34		//Error!;
```

## Functions: Return Values

```c++
returnType functionName (parameterType parameterName, ...) { ...}
```

* Functions can may or may not return a value
* Always specify the return type before the function name

```c++
double thisFunctionReturnsADouble() { ... }
```

* `void` means the function **does not** return a value 

```c++
void setup() { ... }
```

## Functions: Input Parameters

```c++
returnType functionName (parameterType parameterName, ...) { ...}
```

* Functions can may or may not take an input parameters

```c++
double squareRoot(int num) {...}
int sumNumbers(int num1, int num2) {...}
void loop() {...}
```



## If Statements

Basic Syntax

```c++
if (condition){
  statement(s); //do this if condition is true
}
```

```c++
if (condition){
  statement(s); //do this if condition is true
} else {
  statement(s); //do this if false
}
```

  * Useful to execute code only under certain condition

## Conditional Statement

* Conditional statements are logical expressions that evaluate to `true` or `false` (*think "yes" or "no"*)

```c++
int x = 3, y = 10;
if (x == 2) {
    //this will be true because "x is equal to 3"
}
if (y != 10) {
    //this will NOT execute because 
}
```



## While Loop Example

```c++
while (condition){
	statement(s);
}
```

* Useful for code that repeats until a condition is true (especially if the number of iteration is unknown)
* Though `while` loops are perfectly valid in C++, we will typically use `for` loops instead



## For Loops

Basic Syntax

```c++
for (initialization; condition; update){
	statement(s);
}
```

* Useful for code that repeats a set number of times
* Uses a counter to control the loop


## Basic Syntax

```c++
for (initialization; condition; update)
```

##### Initialization

* Create and initialize variables only at the beginning of loop (ofter a counter)

## Basic Syntax

```c++
for (initialization; condition; update)
```

##### Condition

* Boolean expression that is checked at the end of each loop iteration.
* Continue looping as long as this is true

## Basic Syntax

```c++
for (initialization; condition; update)
```

##### Update

* Increment (or decrement) your loop variables at the end of each loop iteration.


## Example

for (<span style="color:#990000">**int i = 0**</span>; i < 10; i++) {

<span style="color:#0000">____</span>if (i % 2 == 0) {

<span style="color:#0000">________</span>Serial.println(i);




**Initialize variables**

## Example

for (int i = 0; <span style="color:#990000">**i < 10**</span>; i++) {

<span style="color:#0000">____</span>if (i % 2 == 0) {

<span style="color:#0000">________</span>Serial.println(i);




**Iteration #1: Check condition (even the first time)**

* If true, run loop
* If false, exit loop

## Example

for (int i = 0; i < 10; i++) {

<span style="color:#0000">____</span><span style="color:#990000">**if (i % 2 == 0) {**</span>

<span style="color:#0000">__________</span><span style="color:#990000">**Serial.println(i);**</span>



**Iteration #1: Run loop body (all the code in the loop)**

## Example

for (int i = 0; i < 10; <span style="color:#990000">**i++**</span>) {

<span style="color:#0000">____</span>if (i % 2 == 0) {

<span style="color:#0000">________</span>Serial.println(i);





**Iteration #1: Update the variable**

## Example

for (int i = 0; <span style="color:#990000">**i < 10**</span>; i++) {

<span style="color:#0000">____</span>if (i % 2 == 0) {

<span style="color:#0000">________</span>Serial.println(i);




**Iteration #2: Check condition again**

* If true, run loop
* If false, exit loop

## Resources on C++ Language

* [C plus plus](http://www.cplusplus.com/)
* [C++ Reference](https://en.cppreference.com/w/)