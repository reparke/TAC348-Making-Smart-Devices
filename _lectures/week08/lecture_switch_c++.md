---
marp: true
theme: itp

week: 8
order: 2
category: lectures
title: Switch / Enum Part 2 (Switch)
---

<!-- headingDivider: 2 -->

# `switch` Statements in C++

## Consider

We are trying to design a self-driving car, and it has a finite set of actions *(these are simplified)*:

* turn right
* turn left
* continue straight
* arrive

## Consider

To give instructions to the user, we need conditional logic

```c++
int action = ...; 	
if (action == 1) {			//turn right
    Serial.println("Turn right (you can turn on red)");
} else if (action == 2)  { 	//turn left
    Serial.println("Turn left (wait for arrow)");
} else if (action == 3)  { 	//continue
    Serial.println("Keep going straight");
} else if (action == 4)  { 	//arrived
    Serial.println("You have arrived!");
}
else {
    Serial.println("Error!")
}
```

## Consider

* Using `if` this way is a perfectly fine way to handle conditional logic
* However, for a finite set of options, there is an easier way
* `switch` statements provide a way to choose between specific, finite values

## `switch` Statement Syntax

```c++
switch (<<variable>>) {
    case <<FIRST_VALUE>>:
        # do some code if variable == VALUE_1
    break;
    case <<SECOND_VALUE>>:
        # do some code if variable == VALUE_2
    break;
    default:
        # do some code if variable is anything else 
}
```

## `switch`Statement Syntax

```c++
switch (<<variable>>)
```

* `variable` can be an `int ` (or `short`, `byte`, `char`)
* `variable` can **not** be a `string`

## `switch` Statement Syntax

```c++
switch (<<variable>>) {
    case <<FIRST_VALUE>>:
        # do some code if variable == FIRST_VALUE
    break;
```

* `switch` will attempt to match `variable` to the value specified by each case label (e.g. `VALUE_3`)
* When a match is found, the code is executed
* This is the equivalent of `if ... else if`
* `break;` **is required** after executing the code for that case

## `switch` Statement Syntax

```c++
switch (<<variable>>) {
	# ...
    default:
    # do some code if variable is anything else 
```

* `default` will execute if none of the cases match `variable`
* This is the equivalent of `else`

## Partially Code: `switch`compared to `if`
```c++
if (action == 0) {			//turn right
    Serial.println("Turn right");
} else if (action == 1)  { 	        //turn left
    Serial.println("Turn left");     //...more else if...
else {
    Serial.println("Error!")
}
```
```c++
switch (action) {			
    case 0:					//turn right
    	Serial.println("Turn right (you can turn on red)");
    break;      //...more cases...
    default:
	    Serial.println("Error!");
}
```

## Full `switch` Example

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



## Summary

* `switch` provides a simplified structure to decided between a small number fixed values (`int` typically)
* `switch` does not work with `string`
