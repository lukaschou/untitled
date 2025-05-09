#include "galaxy.h"
#include "command.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

Planet *galaxy[MAP_SIZE][MAP_SIZE];

/* Print a map and legend of surrounding planets */
void c_map(Command cmd, GameContext *ctx) {
    (void) cmd;
    (void) ctx;
    generate_galaxy();

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

    int placed = 0;
    int num_planets = 10;

    int attempts = 0;
    int max_attempts = 1000;
    int min_distance = 5;
    Planet *planets[10];

    srand(time(NULL));
    
    while (placed < num_planets && attempts < max_attempts) {
        int x = rand() % MAP_SIZE;
        int y = rand() % MAP_SIZE;

        int too_close = 0;
        for (int i = 0; i < placed; i++) {
            // printf("i: %d\n", i);
            Planet *p = planets[i];
            double distance = sqrt(pow(p->coord[0] - x, 2) + pow(p->coord[1] - y, 2));
            if (distance < min_distance) {
                too_close = 1;
                break;
            }
        }

        if (!too_close) {
            Planet *p = calloc(1, sizeof(Planet));
            if (!p) {
                perror("calloc");
                exit(EXIT_FAILURE);
            }
            p->name = planets_names[placed];
            p->coord[0] = x;
            p->coord[1] = y;
            planets[placed] = p;
            galaxy[x][y] = p;
            placed++;
            // printf("Placing at %d, %d\n", x, y);
        }
    }
}
