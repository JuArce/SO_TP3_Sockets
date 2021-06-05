#ifndef SO_TP3_SOCKETS_SOCKETSAPI_H
#define SO_TP3_SOCKETS_SOCKETSAPI_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "defs.h"

#define PORT 8080

typedef struct sockaddr_in SocketAddressData;

int openSocket(SocketAddressData *address);

int createServer(SocketAddressData *address);

int bindSocketAndWaitConnection(int serverFd, SocketAddressData *address, int addrLen);

void connectToServer(int sock, SocketAddressData *address, int addrLen);

void closeSocket(int socketFd);

#endif //SO_TP3_SOCKETS_SOCKETSAPI_H
