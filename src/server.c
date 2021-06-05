// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/server.h"

static void runChallenges(int connectedFd);

static void prepareAndWaitAnswers(char *answer, size_t answerLen, FILE *serverInput);


int main(int argc, char const *argv[]) {
    int serverFd, connectedFd;
    SocketAddressData address;

    serverFd = createServer(&address);
    connectedFd = bindSocketAndWaitConnection(serverFd, &address, sizeof(address));

    runChallenges(connectedFd);

    closeSocket(serverFd);

    return 0;
}

static void runChallenges(int connectedFd) {
    FILE *serverInput;
    if ((serverInput = fdopen(connectedFd, "r")) == NULL) {
        handleError("Fdopen failed");
    }

    char *answer;
    size_t answerLen = MAX_INPUT;
    if ((answer = calloc(answerLen, sizeof(char))) == NULL) {
        handleError("Memory Allocation failed");
    }

    prepareAndWaitAnswers(answer, answerLen, serverInput);

    printf("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto\n\n");

    if (fclose(serverInput) == ERROR) { //fclose también cierra el fd
        handleError("Fclose failed");
    }

    free(answer);
}

static void prepareAndWaitAnswers(char *answer, size_t answerLen, FILE *serverInput) {
    challenge challenges[TOTAL_CHALLENGES] = {challenge1, challenge2, challenge3, challenge4, challenge5,
                                              challenge6, challenge7, challenge8, challenge9, challenge10,
                                              challenge11, challenge12};

    srand((int) time(NULL));

    int challenge = 0;

    while (challenge < TOTAL_CHALLENGES) {
        int correct;

        printf("------------- DESAFIO -------------\n");

        memset(answer, 0, answerLen);

        correct = challenges[challenge](answer, answerLen, serverInput);
        if (correct) {
            challenge++;
        } else {
            printf("\nRespuesta incorrecta: %s\n", answer);
            sleep(SECONDS_WAIT);
        }
        system("clear");
    }
}