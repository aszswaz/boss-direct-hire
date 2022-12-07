#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <stdint.h>

struct websocket;
typedef struct websocket websocket_t;

/**
  * Open a websocket connection.
  * @return Returns a pointer on success, a null pointer on failure.
  */
websocket_t *websocket_open(const char *hostname, uint16_t port, const char *path);

void websocket_close(websocket_t *self);

#endif
