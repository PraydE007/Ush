#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc == 2) {
        for (int i = 0; argv[1][i] != '\0'; i++)
            fprintf(stdout, "%i ", argv[1][i]);
        fprintf(stdout, "0\n");
    }
    return 0;
}
