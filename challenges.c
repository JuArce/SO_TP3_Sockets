#include "challenges.h"

static void printQuest(char *quest) {
    printf("----- PREGUNTA PARA INVESTIGAR -----\n");
    printf("%s\n", quest);
}

static int checkAnswer(char *answer, char *correctOption) {
    return strcmp(answer, correctOption) == 0;
}

static int validateChallenge(char *answer, size_t n, FILE *serverInput, char *correctAnswer) {
    if (getline(&answer, &n, serverInput) == -1) {//TODO Ver el errno getline es medio especial con el -1
        perror("getline");
        exit(EXIT_FAILURE);;
    }
    return checkAnswer(answer, correctAnswer);
}

int challenge1(char *answer, size_t n, FILE *serverInput) {
    printf(
            "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\n"
            "En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\n"
            "Además tendrán que investigar otras preguntas para responder durante la defensa.\n"
            "El desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los\n"
            "mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\n"
            "Además, deberán implementar otro programa para comunicarse conmigo.\n\n"
            "Deberán estar atentos a los easter eggs.\n\n"
            "Para verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\\n'\n\n"
    );

    printQuest("¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?");

    return validateChallenge(answer, n, serverInput, "entendido\n");
}

int challenge2(char *answer, size_t n, FILE *serverInput) {
    printf("The Wire S1E5\n"
           "5295 888 6288\n\n");
    printQuest("¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?");

    return validateChallenge(answer, n, serverInput, "itba\n");

}

int challenge3(char *answer, size_t n, FILE *serverInput) {
    printf("https://ibb.co/tc0Hb6w\n\n");
    printQuest(
            "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?");

    return validateChallenge(answer, n, serverInput, "M4GFKZ289aku\n");
}

int challenge4(char *answer, size_t n, FILE *serverInput) {
    printf("EBADF...\n\n");

    if (write(69, "La respuesta es fk3wfLCm3QvS", 28) == -1) {
        perror("write");
    }

    printQuest(
            "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?");

    return validateChallenge(answer, n, serverInput, "fk3wfLCm3QvS\n");
}

int challenge5(char *answer, size_t n, FILE *serverInput) {
    printf("respuesta = strings:277\n\n"); //TODO fijarse en donde aparece en realidad xdxd
    printQuest("¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?");

    return validateChallenge(answer, n, serverInput, "too_easy\n");
}

int challenge6(char *answer, size_t n, FILE *serverInput) {
    printf(".data .bss .comment ? .shstrtab .symtab .strtab\n\n"); //TODO esto falta
    printQuest(
            "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?");

    return validateChallenge(answer, n, serverInput, ".RUN_ME\n");
}

int challenge7(char *answer, size_t n, FILE *serverInput) {
    //TODO esto tambien falta
    printf("Filter error\n\n"
           "?L%%]vKqaTm\n"
           "?L%%]vKqaTm O:%%hV#UBD6y/7>AL:yaIrejx\"'Ywh:ujGsBcfya$Jrpq[`_NwF6]G36V rm2:<DA[3Huo9WxenN& N:!-=F)sJytoFva|8~ q*(7.zj\\2:)e>xE#f!UwTy!pj~@s\\bZ1AO5vD XjKRu~]5@pt:lj1$1L#O2`~Ln28ZGh(18f<\"L*D@E),-,bm?5hmU:?FH*{fpsYJ0,=F#>\"btf\"Px$-t/MMhHCUvql?%%~N N:+>jhWB!||&\n\n");

    printQuest("¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?");

    return validateChallenge(answer, n, serverInput, "K5n2UFfpFMUN\n");
}

int challenge8(char *answer, size_t n, FILE *serverInput) {
    printf("¿?\n\n");
    printf("\033[0;30;40m La respuesta es BUmyYq5XxXGt \033[0m");
    printQuest("¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?");

    return validateChallenge(answer, n, serverInput, "BUmyYq5XxXGt\n");
}

int challenge9(char *answer, size_t n, FILE *serverInput) {
    printf("Latexme\n\n"
           "Si\n"
           "\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u})\n"
           "entonces\n"
           "y = \n\n");
    printQuest("Sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?");

    return validateChallenge(answer, n, serverInput, "u^v\n");
}

int challenge10(char *answer, size_t n, FILE *serverInput) {
    printf("quine\n\n");

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
        printf("ENTER para reintentar\n");
    }

    printQuest("¿Cuáles son las características del protocolo SCTP?");

    return validateChallenge(answer, n, serverInput, "chin_chu_lan_cha\n");
}

int challenge11(char *answer, size_t n, FILE *serverInput) {
    printf("b gdbme y encontrá el valor mágico\n\n"
           "ENTER para reintentar\n\n");
    printQuest("¿Qué es un RFC?");

    //TODO hacer funcion gdbme con getpid()

    return validateChallenge(answer, n, serverInput, "gdb_rules\n");
}

int challenge12(char *answer, size_t n, FILE *serverInput) {
    printf("Me conoces\n\n");
    //TODO distribucion normal
    printQuest("¿Fue divertido?");

    return validateChallenge(answer, n, serverInput, "normal\n");
}