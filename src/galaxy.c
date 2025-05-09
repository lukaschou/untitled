#include "galaxy.h"
#include "command.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Planet *galaxy[MAP_SIZE][MAP_SIZE];

/* Print a map and legend of surrounding planets */
void c_map(Command cmd) {
    (void) cmd;
    char legend = 'a';
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (!galaxy[i][j]) {
                printf("* ");
            } else {
                printf("\033[1;31m%c\033[0m ", legend++);
            }
        }
        printf("\n");
    }

    printf("\n\033[1mLegend:\033[22m\n");
    char key = 'a';
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (galaxy[i][j]) {
                printf("\033[1;31m%c\033[0m: %s\n", key++, galaxy[i][j]->name);
            }
        }
    }

    if (fflush(stdout)) {
        perror("fflush");
        exit(EXIT_FAILURE);
    }
}

// THIS IS A TEMP FUNC WITH HARD CODED SHIT
void generate_galaxy() {
    memset(galaxy, 0, sizeof(galaxy));

    const char* planets_names[] = {
        "Jupiter",
        "Pluto",
        "florpus-17 $-^&",
        "Xenora Prime",
        "Zorbax-9",
        "Nova Terra",
        "Gliese-581c",  
        "Vorticon IV",
        "Cryon-7",
        "Elysium Drift" 
    };

    for (int i = 0; i < 3; ++i) {
        Planet *p = calloc(1, sizeof(Planet));
        if (!p) {
            perror("calloc");
            exit(EXIT_FAILURE);
        }
        p->name = planets_names[i];
        galaxy[i+2][i+2] = p;
    }
}
