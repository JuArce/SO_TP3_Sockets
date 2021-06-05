// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/client.h"

static void getClientAnswers(int serverFd);

int main(int argc, char const *argv[]) {
    int sock;
    SocketAddressData servAddr;

//    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//        handleError("Socket creation failed");
//    }
//
//    servAddr.sin_family = AF_INET;
//    servAddr.sin_port = htons(atoi(argv[2]));

    sock = openSocket(&servAddr);

//    struct addrinfo *res;
//    int error = 0;
//    error = getaddrinfo(argv[1], NULL, NULL, &res);
//    if(error) {
//        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(error));
//        exit(EXIT_FAILURE);
//    }

    // Convert IPv4 and IPv6 addresses from text to binary form
//    if (inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr) <= 0) {
//        handleError("Invalid address/ Address not supported");
//    }

    connectToServer(sock, &servAddr, sizeof(servAddr));

    getClientAnswers(sock);

    return 0;
}

static void getClientAnswers(int serverFd) {
    char *buffer;
    size_t bufferLen = MAX_INPUT;
    if ((buffer = calloc(bufferLen, sizeof(char))) == NULL) {
        handleError("Mem Allocation Failed");
    }

    while (1) {
        memset(buffer, 0, bufferLen);

        getline(&buffer, &bufferLen, stdin);

        int readChars = strlen(buffer);
        if (readChars > 0 && write(serverFd, buffer, readChars) == ERROR) {
            handleError("Write failed");
        }
    }

    //free(buffer);
}