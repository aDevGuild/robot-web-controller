# Contributing

## .env

Run susbstituting 'websocket.org' with the server you want to connect to:
  
```bash
echo "" | openssl s_client -showcerts -connect websocket.org:443 | sed -n "1,/Root/d; /BEGIN/,/END/p" | openssl x509 -outform PEM >websocket_org.pem 
```

to get the certificate for the websocket.org server and substitute the contents of the `WEBSOCKET_PEM` define in the `.env` file with the contents of the `websocket_org.pem` file.


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
