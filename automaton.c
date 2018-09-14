#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define GENERATION_SIZE 80

typedef unsigned char byte;

void display(bool generation[], int size);
void evolve(bool generation[], int size, int rule);
/* Convert a array of booleans or bits into a decimal number,
 * where the rightmost bit is the least significant
 */
int bool_to_num(bool bits[], int size);
bool new_state(bool *neighbours, byte rule);
void sleep(int ms);

int main(int argc, char **argv) {
    int rule;
    if (argc != 2) {
        fprintf(stderr, "Usage: ./automaton <rule>\n");
        return -1;
    }
    rule = atoi(argv[1]);
    bool current_generation[GENERATION_SIZE] = { 0 };
    current_generation[GENERATION_SIZE/2] = true;

    for (;;) {
        display(current_generation, GENERATION_SIZE);
        evolve(current_generation, GENERATION_SIZE, rule);
        sleep(500);
    }
    return 0;
}

int bool_to_num(bool bits[], int size) {
    int res = 0;
    for (int i = 0; i < size; i++) {
        res |= bits[i] << (size - (i + 1));
    }
    return res;
}

bool new_state(bool *neighbours, byte rule) {
    return rule & 1 << bool_to_num(neighbours, 3);
}

void display(bool generation[], int size) {
    for (int i = 0; i < size; i++) {
        putchar(generation[i] ? '#' : ' ');
    }
    putchar('\n');
}

void evolve(bool generation[], int size, int rule) {
    bool new_generation[size];
    bool *neighbours;
    for (int i = 0; i < size; i++) {
        if (i == 0)
            neighbours = (bool []){false, generation[i], generation[i+1]};
        else if (i == size-1)
            neighbours = (bool []){generation[i-1], generation[i], false};
        else
            neighbours = &generation[i-1];
        new_generation[i] = new_state(neighbours, rule);
    }
    memcpy(generation, new_generation, size); // TODO: Make this a bit more efficient later
}

void sleep(int ms) {
    clock_t delta = 0, delta_in_ms = 0;
    clock_t start_time = clock();
    assert(start_time != -1);
    while (delta_in_ms < ms) {
        delta = clock() - start_time;
        delta_in_ms = (delta / CLOCKS_PER_SEC) * 1000;
    }
}
