---
marp: true
theme: tac

week: 2
category: lectures
title: For Loops in C++
---

<!-- headingDivider: 2 -->

# For Loops in C++

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