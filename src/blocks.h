#pragma once

extern const int bit_changer[9];
extern const int box_splitter[9][2];

extern const int all_candidates;

extern const int board_size;

struct Cell {
    int value, possibility, fixed, marked;
};
typedef Cell Cell;

struct Box {
    Cell** memberArray;
    int eliminations;
};
typedef Box Box;

struct Lines {
    Cell** memberArray;
    int eliminations;
};
typedef Lines Lines;

struct Reduce {
    int blank;
    Cell** appliedCells;
    int* exceptions;
    struct Reduce* next;
};
typedef Reduce Reduce;