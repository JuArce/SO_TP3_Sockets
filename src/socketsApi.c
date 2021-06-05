#include "../include/socketsApi.h"

int openSocket(SocketAddressData *address) {
    int serverFd;

    memset(address, 0, sizeof(SocketAddressData));

    // Creating socket file descriptor
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        handleError("Socket creation failed");
    }

    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(PORT);

    return serverFd;
}

int createServer(SocketAddressData *address) { //también se podría manejar con un flag en openSocket
    int serverFd = openSocket(address);
    int opt = 1;

    // Forcefully attaching socket to the port 8080
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        handleError("Socket attaching failed");
    }

    return serverFd;
}

int bindSocketAndWaitConnection(int serverFd, SocketAddressData *address, int addrLen) {
    // Forcefully attaching socket to the port 8080
    int connectedFd;

    if (bind(serverFd, (struct sockaddr *) address, addrLen) < 0) {
        handleError("Socket binding failed");
    }

    if (listen(serverFd, 3) < 0) {
        handleError("Socket listening failed");
    }

    if ((connectedFd = accept(serverFd, (struct sockaddr *) address, (socklen_t * ) & addrLen)) < 0) {
        handleError("Accept failed");
    }

    return connectedFd;
}

void connectToServer(int sock, SocketAddressData *address, int addrLen) {
    if (connect(sock, (struct sockaddr *) address, addrLen) < 0) {
        handleError("Connection Failed");
    }
}

void closeSocket(int socketFd) {
    if (close(socketFd) == ERROR) {
        handleError("Close failed");
    }
}