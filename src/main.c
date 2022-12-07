#include "websocket.h"

int main() {
    websocket_t *ws;

    if ((ws = websocket_open("ws.zhipin.com", 443, "/ws"))) return 1;
    websocket_close(ws);
    return 0;
}
