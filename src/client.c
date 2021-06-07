// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/client.h"

extern int errno;

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

    int leave = 0;
    while (!leave) {
//        printf("Ingrese su respuesta: ");

        memset(buffer, 0, bufferLen);

        int previousErrno = errno;
        if (getline(&buffer, &bufferLen, stdin) == ERROR) {
            if (previousErrno == errno) {
                leave = 1;
            } else {
                handleError("Getline failed");
            }
        }

        if (!leave) {
            int readChars = strlen(buffer);
            if (readChars > 0) {
                int sentChars = write(serverFd, buffer, readChars);
                if (sentChars == ERROR) {
                    handleError("Write failed");
                }
                if (sentChars == 0) {
                    leave = 1;
                }
            }
        }
    }

    printf("Terminating client\n");

    closeSocket(serverFd);
    free(buffer);
}