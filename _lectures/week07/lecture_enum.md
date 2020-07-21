---
marp: true
theme: itp

week: 7
category: lectures
title: enum in C++
---

<!-- headingDivider: 2 -->

# `enum ` in C++

## Recall

In an early discussion, we were trying to give driving direction, and there was a finite set of actions:

* turn right
* turn left
* continue straight
* arrive



## Recall

* We found `switch` provided a convenient way to choose among specific, finite values
* We could have used `if...else` as well but `switch` is often more convenient for finite values



## Switch 

```c++
int action = ...; 	
switch (action) {			
    case 0:					//turn right
    	Serial.println("Turn right (you can turn on red)");
    break; 
    case 1:					//turn left
    	Serial.println("Turn left (wait for arrow)");
    break;
    case 2:	 				//continue
    	Serial.println("Keep going straight");
    break;
    case 3:	 				//arrived
    	Serial.println("You have arrived!");
    break;
    default:
	    Serial.println("Error!");
}
```

## Another improvement

* This was cleaning and easier to read
* However, the actions *(or states*) are still a little confusing 
  * Ex: We need to remember that **case 2** means **continue straight**

```c++
case 2:	 				//continue
	Serial.println("Keep going straight");
 
```
* These is another improvement we can make

## `enum`

* `enum` is a user-defined data type 
  * This means **we** get to decide what its values will be
* `enum` that allows us to give labels to literal (constant) values
* It can make our code much more self-explanatory and logical

## `enum` Syntax

```c++
enum <<enum_name>> { <<value1>>, <<value2>>, ...}
```

* `enum` is the type keyword 
* `<<enum_Name>>` is a name we define (it will become like `int` or `String`)
* `<<value1>>` ... `<<value2>>` are the allowed value we will let our variable take
* By default, C++ treats each of these **values** as starting at `0` and increasing by 1

## Recall

```c++
int action = ...; 	
switch (action) {			
    case 0:					//turn right
    	Serial.println("Turn right (you can turn on red)");
    break; 
    case 1:					//turn left
    	Serial.println("Turn left (wait for arrow)");
    break;
    case 2:	 				//continue
    	Serial.println("Keep going straight");
    break;
    case 3:	 				//arrived
    	Serial.println("You have arrived!");
    break;
    default:
	    Serial.println("Error!");
}
```

## `enum ` Example

* There are four actions or states we need to represent
  * Turn Left, Turn Right, Go Straight, Arrive
* Let's define our `enum` and call it `Operation`

```c++
enum Operation {LEFT, RIGHT, STRAIGHT, ARRIVE};
```

* `Operation` value of `LEFT` is equivalent to `0`
* `Operation` value of `RIGHT` is equivalent to `1`
* `Operation` value of `STRAIGHT` is equivalent to `2`
* `Operation` value of `ARRIVE` is equivalent to `3`

## `enum ` Example

* Now we can create a `Operation` variable

```c++
Operation action;
```

* `action` would be given a value from some function we write
* You could also assign a literal value to `action` like this

```c++
Operation action = STRAIGHT;	//equivalent to int value of 2
```

* We can now use our `Operation` value to control the `switch`

## `enum ` Example

```c++
Operation action = ...; 	
switch (action) {			
    case RIGHT:					
    	Serial.println("Turn right (you can turn on red)");
    break; 
    case LEFT:
    	Serial.println("Turn left (wait for arrow)");
    break;
    case STRAIGHT:
    	Serial.println("Keep going straight");
    break;
    case ARRIVE:
    	Serial.println("You have arrived!");
    break;
    default:
	    Serial.println("Error!");
}
```
