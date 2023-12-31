#include "blocks.h"
#include <stdlib.h>

void displayBoard(Cell*** boardPointer) {
    char board[9][9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                board[i][j][k] = 32;
            }
        }
    }

    int placeholder;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (boardPointer[i][j] -> value != -1) {
                board[i][j][4] = (char) boardPointer[i][j] -> value + 49;
                continue;
            }

            placeholder = boardPointer[i][j] -> possibility;

            for (int k = 0; k < 9; k++) {
                board[i][j][k] = (char) (placeholder % 2 ? k + 49 : 32);
                placeholder /= 2;
            }
        }
    }
}

void possibilityCleaner(Cell*** board, Lines** box, Lines** rows, Lines** columns){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(board[i][j] -> value > -1) {
                board [i][j] -> possibility = 0;
                continue;
            }

            board[i][j] -> possibility &= ~(box[(i/3)*3 + (j/3)] -> eliminations);
            board[i][j] -> possibility &= ~(rows[i] -> eliminations);
            board[i][j] -> possibility &= ~(columns[j] -> eliminations);
        }
    }
}

void markerCleaner(Cell*** board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] -> marked = 0;
        }
    }
}

int BoardChecker(Cell*** board) {
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sum += board[i][j] -> possibility;
        }
    }
    return sum;
}

int bitCounter (int flow) {
    int counter = 0;

    while (flow != 0) {
        counter += flow % 2;
        flow /= 2;
    }

    return counter;
}

int bitChecker(Cell*** board, Lines** box, Lines** rows, Lines** columns, int bit, int i, int j) {
    if (bit == 0) return 0;

    if (bit == (bit & (~bit + 1))) {
        int val = -1;
        while (bit != 0) {
            val++;
            bit >>= 1;
        };
        
        board[i][j] -> value = val;
        box[(i/3)*3 + (j/3)] -> eliminations += bit_changer[val];
        rows[i] -> eliminations += bit_changer[val];
        columns[j] -> eliminations += bit_changer[val];
        return 1;
    }
    return 0;
}

int cellChecker(Cell*** board, Lines** box, Lines** rows, Lines** columns) {
    int counter = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] -> value > -1) continue;
            int placeholder = board[i][j] -> possibility;

            if (bitChecker(board, box, rows, columns, placeholder, i, j)) {
                counter++;
                continue;
            }
        }
    }

    return counter;
}

Cell* createCell() {
    Cell* cell = malloc(sizeof(Cell));

    cell -> value = -1;
    cell -> possibility = all_candidates;
    cell -> fixed = 0;
    return cell;
}

Cell*** createBoard() {
    Cell*** board = malloc(sizeof(Cell**)*9);

    for (int i = 0; i < 9; i++) {
        board[i] = malloc(sizeof(Cell*)*9);
        
        for (int k = 0; k < 9; k++) {
            board[i][k] = create();
        }
    }

    return board;
}

Lines** createBox(Cell*** board) {
    Cell* box = malloc(sizeof(Cell**) * 9);

    for (int i = 0; i < 9; i++) {
        box[i] = malloc(sizeof(Lines));
        box[i] -> memberArray = malloc(sizeof(Cell*) * 9);

        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                box[i] -> memberArray[j*3 + 1] = board[box_splitter[i][0] + j][box_splitter[i][1] + k];
            }
        }

        box[i] -> eliminations = 0;
    }

    return box;

}

Lines** createLines(Cell*** board, int aspect) {
    Lines** lines = malloc(sizeof(Lines*) * 9);
    if (aspect == 0) {
        for (int i = 0; i < 9; i++) {
            lines[i] = malloc(sizeof(Lines));
            lines[i] -> memberArray = malloc(sizeof(Cell*) * 9);

            for (int j = 0; j < 9; j++) {
                lines[i] -> memberArray[j] =board[i][j];
            }
            lines[i] -> eliminations = 0;
        }
    }
    else {
        for (int i = 0; i < 9; i++) {
            lines[i] = malloc(sizeof(Lines));
            lines[i] -> memberArray = malloc(sizeof(Cell*) * 9);

            for (int j = 0; j < 9; j++) {
                lines[i] -> memberArray[j] = board[j][i];
            }
            lines[i] -> eliminations = 0;
        }
    }
    return lines;
}

void newBlank(Reduce** head, int blank, Cell** appliedCells, int* exceptions) {
    Reduce* newBlank = malloc(sizeof(Reduce));

    newBlank -> blank = blank;
    newBlank -> appliedCells = appliedCells;
    newBlank -> exceptions = exceptions;
    newBlank -> next = *head;
    *head = newBlank;
}

Reduce* getBlank(Reduce** head) {
    Reduce* blank = (*head);
    *head = (*head) -> next;
    return blank;
}

void applyBlank(Reduce** head) {
    while (*head != NULL) {
        Reduce* blank = getBlank(head);
        for (int i = 0; i < 9; i++) {
            if (blank -> exceptions[i] == 1) continue;
            blank -> appliedCells[i] -> possibility &= blank -> blank;
        }
        free(blank -> exceptions);
        free(blank);
    }
}

void memoryCleaner(Cell*** board, Lines** box, Lines** row, Lines** column) {
    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 9; k++) {
            free(board[i][k]);
        }

        free(board[i]);
    }

    free(board);

    for (int i = 0; i < 9; i++) {
        free(box[i] -> memberArray);
        free(box[i]);
        free(row[i] -> memberArray);
        free(row[i]);
        free(column[i] -> memberArray);
        free(column[i]);
    }

    free(box);
    free(row);
    free(column);
}
