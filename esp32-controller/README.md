# Contributing

## Guidelines

### Don't give an important behavior to the Super Loop / Default Task

FreeRTOS considers the Arduino super loop to be the default task.

When using the super loop paradigm, it doesn't make any difference because it will be the only task running by definition.

However, it means that when an operating system is used to design, the default task runs only when the microcontroller is idle. It is the only task not guaranteed to run per tasking iteration.

The only behavior that should be given to this task is when nothing more is running, like sleeping mode. Even then, it is unusual for the default task to have anything other than an empty loop.

## Standard File Templates

### Header Files

```cpp
/**
 * @file MyFile.h
 * @brief This file contains the prototypes of the functions that will be used
 * in MyFile.c.
 */

#ifndef MY_FILE_H
#define MY_FILE_H

// Framework Includes //
#include <Arduino.h>

// External Includes //

// Internal Includes //
#include "env.h"

// Define Constants //
#define TRUE 1
#define FALSE 0

// Function Prototypes //
/**
 * @brief This function does something.
 * @param void
 * @return void
 */
void myFunction();

#endif  // MY_FILE_H
```
