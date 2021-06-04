#include "server.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "challenges.h"

#define PORT 8080
#define SO_REUSEPORT 15


challenge challenges[TOTAL_CHALLENGES] = {challenge1, challenge2, challenge3, challenge4, challenge5,
                                          challenge6, challenge7, challenge8, challenge9,challenge10,
                                          challenge11, challenge12};

int main(int argc, char const *argv[]) {
    int serverFd, newSocket;//, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(serverFd, (struct sockaddr *) &address,
             sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(serverFd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((newSocket = accept(serverFd, (struct sockaddr *) &address,
                            (socklen_t * ) & addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    FILE *serverInput = fdopen(newSocket, "r");
    size_t n = 64;
    char *answer = calloc(n, sizeof(char));
    srand((int) time(NULL));

    int challenge = 0;
    int correct = 0;
    while (challenge < TOTAL_CHALLENGES) {
        printf("------------- DESAFIO -------------\n");

        correct = challenges[10](answer, n, serverInput); //TODO cambiar por challenge (esta asi para testeo)
        if (correct) {
            challenge++;
        } else {
            printf("\nRespuesta incorrecta: %s\n", answer);
            sleep(1);
        }
        system("clear");
        //TODO pensar en agregar un sleep
    }

    free(answer);

    close(newSocket);

    close(serverFd);
    //TODO fijarse si falta limpiar algo y manejo de errores

    printf("\n");
    return 0;
}