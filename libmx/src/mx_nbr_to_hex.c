#include "libmx.h"

static void nbr_to_hex_cycle(unsigned long store, int i, char *hex) {
    unsigned long hexSymbol;

    while (store) {
        hexSymbol = store % 16;
        if (hexSymbol >= 0 && hexSymbol <= 9)
            hex[i] = hexSymbol + 48;
        else
            hex[i] = hexSymbol + 87;
        store = store / 16;
        i--; 
    }
}

char *mx_nbr_to_hex(unsigned long nbr) {
    unsigned long store = nbr;
    int counter = 0;
    int i;
    char *hex = NULL;

    if (nbr == 0) {
        hex = mx_strnew(1);
        hex[0] = 48;
        return hex;
    }
    while (store) {
        store = store / 16;
        counter++;
    }
    hex = mx_strnew(counter);
    store = nbr;
    i = counter - 1;
    nbr_to_hex_cycle(store, i, hex);
    return hex;
}
