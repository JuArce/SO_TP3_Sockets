#ifndef SO_TP3_SOCKETS_SERVER_H
#define SO_TP3_SOCKETS_SERVER_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "challenges.h"
#include "defs.h"

#define PORT 8080
#define SO_REUSEPORT 15

#define SECONDS_WAIT 1

typedef struct sockaddr_in socketAddressData;

#endif //SO_TP3_SOCKETS_SERVER_H
