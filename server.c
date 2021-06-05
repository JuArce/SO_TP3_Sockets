#include "server.h"

static int createServerSocket(socketData *address);

static int bindAndWaitConnection(int serverFd, socketData *address, int addrLen);

static void runChallenges(int connectedFd);

static int createServerSocket(socketData *address) {
    int serverFd;
    int opt = 1;

    // Creating socket file descriptor
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        handleError("Socket creation failed");
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        handleError("Socket attaching failed");
    }

    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(PORT);

    return serverFd;
}

static int bindAndWaitConnection(int serverFd, socketData *address, int addrLen) {
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

static void runChallenges(int connectedFd) {
    challenge challenges[TOTAL_CHALLENGES] = {challenge1, challenge2, challenge3, challenge4, challenge5,
                                              challenge6, challenge7, challenge8, challenge9, challenge10,
                                              challenge11, challenge12};

    FILE *serverInput;
    if((serverInput = fdopen(connectedFd, "r")) == NULL) {
        handleError("Fdopen failed");
    }

    char *answer;
    size_t n = MAX_INPUT;
    if ((answer = calloc(n, sizeof(char))) == NULL) {
        handleError("Memory Allocation failed");
    }

    srand((int) time(NULL));

    int challenge = 0;
    int correct = 0;
    while (challenge < TOTAL_CHALLENGES) {
        printf("------------- DESAFIO -------------\n");

        memset(answer, 0, n);

        correct = challenges[challenge](answer, n, serverInput);
        if (correct) {
            challenge++;
        } else {
            printf("\nRespuesta incorrecta: %s\n", answer);
        }
        sleep(SECONDS_WAIT);
        system("clear");
    }

    printf("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto\n\n");

    if(fclose(serverInput) == ERROR){ //fclose también cierra el fd
        handleError("Fclose failed");
    }

    free(answer);
}

int main(int argc, char const *argv[]) {
    int serverFd, connectedFd;
    socketData address;

    serverFd = createServerSocket(&address);
    connectedFd = bindAndWaitConnection(serverFd, &address, sizeof(address));

    runChallenges(connectedFd);

    if (close(serverFd) == ERROR) {
        handleError("Close failed");
    }

    sleep(10);

    return 0;
}