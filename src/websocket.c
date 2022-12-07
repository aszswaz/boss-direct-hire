#include "websocket.h"
#include "error.h"

#include <stddef.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>


struct websocket {
    const char *hostname;
    uint16_t port;
    const char *path;
    int socketfd;
};

static int open_socket(const char *hostname, uint16_t port) {
    struct sockaddr_in server_addr = {};
    struct hostent *host;
    int socketfd;
    int code;

    host = gethostbyname(hostname);
    if (!host) {
        printf("%s %d: %s\n", __FILE_NAME__, __LINE__, hstrerror(h_errno));
        goto exception;
    }
    printf("hostname: %s, ip: %s\n", hostname, inet_ntoa(*((struct in_addr *) host->h_addr)));

    server_addr.sin_family = host->h_addrtype;
    server_addr.sin_addr.s_addr = host->h_addr;
    server_addr.sin_port = htons(port);

    socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SYSCALL_ERR(socketfd == -1);
    code = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    SYSCALL_ERR(code == -1);

    return socketfd;
exception:
    if (socketfd != -1) close(socketfd);
    return -1;
}

websocket_t *websocket_open(const char *hostname, uint16_t port, const char *path) {
    int code = 0;
    websocket_t *self;

    self = malloc(sizeof(websocket_t));
    SYSCALL_ERR(!self);
    memset(self, 0, sizeof(websocket_t));
    self->socketfd = open_socket(hostname, port);
    if (self->socketfd != -1) goto exception;
    // TODO: DO an SSL handshake.

    return 0;
exception:
    if (self) websocket_close(self);
    return NULL;
}

void websocket_close(websocket_t *self) {
    if (!self) return;
    if (self->socketfd != -1) close(self->socketfd);
    free(self);
}
