#ifndef CREATE_HTTP_HANDLERS_H
#define CREATE_HTTP_HANDLERS_H

// Framework Includes //
#include <ESPAsyncWebServer.h>
#include <Ultrasonic.h>

// Internal Includes //
#include "env.h"
#include "main.h"

void createHttpHandlers(AsyncWebServer *server);

#endif  // CREATE_HTTP_HANDLERS_H
