// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/challenges.h"

#define MAGIC_PID 0x12345678

static void printQuest(char *quest);

static int validateChallenge(char *answer, size_t answerLen, FILE *serverInput, char *correctAnswer);

static int checkAnswer(char *answer, char *correctOption);

static void obfuscateAnswer();

static void checkQuine();

static void gdbme();

static void boxMuller(double m, double s);


static void printQuest(char *quest) {
    printf("----- PREGUNTA PARA INVESTIGAR -----\n");
    printf("%s\n", quest);
}

static int checkAnswer(char *answer, char *correctOption) {
    return strcmp(answer, correctOption) == 0;
}

static int validateChallenge(char *answer, size_t answerLen, FILE *serverInput, char *correctAnswer) {
    if (getline(&answer, &answerLen, serverInput) == ERROR) {
        handleError("Getline failed");
    }
    return checkAnswer(answer, correctAnswer);
}

int challenge1(char *answer, size_t answerLen, FILE *serverInput) {
    printf("Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\n"
           "En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\n"
           "Además tendrán que investigar otras preguntas para responder durante la defensa.\n"
           "El desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los\n"
           "mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\n"
           "Además, deberán implementar otro programa para comunicarse conmigo.\n\n"
           "Deberán estar atentos a los easter eggs.\n\n"
           "Para verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\\n'\n\n"
    );

    printQuest("¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?");

    return validateChallenge(answer, answerLen, serverInput, "entendido\n");
}

int challenge2(char *answer, size_t answerLen, FILE *serverInput) {
    printf("The Wire S1E5\n"
           "5295 888 6288\n\n");

    printQuest("¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?");

    return validateChallenge(answer, answerLen, serverInput, "itba\n");

}

int challenge3(char *answer, size_t answerLen, FILE *serverInput) {
    printf("https://ibb.co/tc0Hb6w\n\n");

    printQuest(
            "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?");

    return validateChallenge(answer, answerLen, serverInput, "M4GFKZ289aku\n");
}

int challenge4(char *answer, size_t answerLen, FILE *serverInput) {
    printf("EBADF...\n\n");

    if (write(69, "La respuesta es fk3wfLCm3QvS", 28) == ERROR) {
        perror("write"); //ESTE NO CAMBIA; SE QUEDA ASI
    }

    printf("\n");
    printQuest(
            "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?");

    return validateChallenge(answer, answerLen, serverInput, "fk3wfLCm3QvS\n");
}

int challenge5(char *answer, size_t answerLen, FILE *serverInput) {
    printf("respuesta = strings:100\n\n"); //TODO fijarse en donde aparece en realidad xdxd

    printQuest("¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?");

    return validateChallenge(answer, answerLen, serverInput, "too_easy\n");
}

int challenge6(char *answer, size_t answerLen, FILE *serverInput) {
    printf(".plt .plt.got .text ? .fini\n\n");

    printQuest(
            "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?");

    return validateChallenge(answer, answerLen, serverInput, ".RUN_ME\n");
}

int challenge7(char *answer, size_t answerLen, FILE *serverInput) {
    printf("Filter error\n\n");
    obfuscateAnswer();
    printf("\n\n");

    printQuest("¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?");

    return validateChallenge(answer, answerLen, serverInput, "K5n2UFfpFMUN\n");
}

static void obfuscateAnswer() {
    char *challengeAnswer = "La respuesta es K5n2UFfpFMUN";
    int answerLen = strlen(challengeAnswer);

    for (int i = 0; i < answerLen; i++) {
        int limit = (rand() % 11);
        for (int j = 0; j < limit; j++) {
            char toPrint[2] = {0};
            toPrint[0] = (rand() % (126 - 32 + 1) + 32);
            write(STDERR, toPrint, 1);
        }

        write(STDOUT, challengeAnswer + i, 1);
    }
}

int challenge8(char *answer, size_t answerLen, FILE *serverInput) {
    printf("¿?\n\n");
    printf("\033[0;30;40m La respuesta es BUmyYq5XxXGt \033[0m\n");

    printQuest("¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?");

    return validateChallenge(answer, answerLen, serverInput, "BUmyYq5XxXGt\n");
}

int challenge9(char *answer, size_t answerLen, FILE *serverInput) {
    printf("Latexme\n\n"
           "Si\n"
           "\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u})\n"
           "entonces\n"
           "y = \n\n");

    printQuest("Sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?");

    return validateChallenge(answer, answerLen, serverInput, "u^v\n");
}

int challenge10(char *answer, size_t answerLen, FILE *serverInput) {
    printf("quine\n\n");

    checkQuine();

    printQuest("¿Cuáles son las características del protocolo SCTP?");

    return validateChallenge(answer, answerLen, serverInput, "chin_chu_lan_cha\n");
}

static void checkQuine() {
    int systemResponse = system("gcc quine.c -o quine");

    if (!systemResponse) {
        printf("¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde.\n");
        systemResponse = system("./quine | diff - quine.c");

        if (!systemResponse) {
            printf("La respuesta es chin_chu_lan_cha\n");
        } else {
            printf("diff encontró diferencias\n");
        }
    }

    if (systemResponse) {
        printf("ENTER para reintentar\n\n");
    }
}

int challenge11(char *answer, size_t answerLen, FILE *serverInput) {
    printf("b gdbme y encontrá el valor mágico\n\n");

    gdbme();

    printQuest("¿Qué es un RFC?");

    return validateChallenge(answer, answerLen, serverInput, "gdb_rules\n");
}

static void gdbme() {
    if (getpid() == MAGIC_PID) {
        printf("La respuesta es gdb_rules\n\n");
    } else {
        printf("ENTER para reintentar\n\n");
    }
}

int challenge12(char *answer, size_t answerLen, FILE *serverInput) {
    printf("Me conoces\n\n");

    for (int i = 0; i < 100; i++) {
        boxMuller(0, 1);
    }

    printf("\n\n");

    printQuest("¿Fue divertido?");

    return validateChallenge(answer, answerLen, serverInput, "normal\n");
}

/*
    (c) Copyright 1994, Everett F. Carter Jr.
    Permission is granted by the author to use
    this software for any application provided this
	copyright notice is preserved.
    https://github.com/ingenthr/memcachetest/blob/master/boxmuller.c
 */
/* normal random variate generator */
/* mean m, standard deviation s */
static void boxMuller(double m, double s) {
    double x1, x2, w, y1;
    static double y2;
    static int useLast = 0;

    if (useLast) /* use value from previous call */
    {
        y1 = y2;
        useLast = 0;
    } else {
        do {
            x1 = 2.0 * drand48() - 1.0;
            x2 = 2.0 * drand48() - 1.0;
            w = x1 * x1 + x2 * x2;
        } while (w >= 1.0);

        w = sqrt((-2.0 * log(w)) / w);
        y1 = x1 * w;
        y2 = x2 * w;
        useLast = 1;
    }

    double result = (m + y1 * s);

    printf("%.6f ", result);
}