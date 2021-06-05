// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "client.h"

#define PORT 8080

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid arguments\n");
        exit(0);
    }

    int sock = 0;
    struct sockaddr_in servAddr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        handleError("Socket creation failed");
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(atoi(argv[2]));

//    struct addrinfo *res;
//    int error = 0;
//    error = getaddrinfo(argv[1], NULL, NULL, &res);
//    if(error) {
//        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(error));
//        exit(EXIT_FAILURE);
//    }

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr) <= 0) {
        handleError("Invalid address/ Address not supported");
    }

    if (connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        handleError("Connection Failed");
    }

    char *buffer;
    size_t n = MAX_INPUT;
    if ((buffer = calloc(n, sizeof(char))) == NULL){
        handleError("Mem Allocation Failed");
    }

    while (1) {
        memset(buffer, 0, n);

        getline(&buffer, &n, stdin);

        if(write(sock, buffer, strlen(buffer)) == ERROR) {
            handleError("Write failed");
        }
    }

    free(buffer);

    return 0;
}
