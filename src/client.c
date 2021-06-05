// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/client.h"

static void getClientAnswers(int serverFd);

int main(int argc, char const *argv[]) {
    int sock;
    SocketAddressData servAddr;

    sock = openSocket(&servAddr);
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