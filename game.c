#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

void print_options(char *options[], int num_options) {
    for (int i = 0; i < num_options; i++) {
        printf("%d: %s\n", i+1, options[i]);
    }
}

int read_input(char input[MAX_INPUT_SIZE]) {
  if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
    if (feof(stdin)) {
        return 0;
    } else if (ferror(stdin) && errno != EINTR) {
        perror("fgets");
        exit(EXIT_FAILURE);
    }
  }
  return 1;
}

int read_options(char *options[], int num_options) {
  char input[MAX_INPUT_SIZE];
  print_options(options, num_options);
  read_input(input);
  strtol();
}

int main() {
  while (1) {
    char *options[] = {"apple", "banana", "orange"};
    read_options(options, 3);
  }
}
