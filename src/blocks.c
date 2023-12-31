#include <blocks.h>


const int bit_changer[9] ={1, 2, 4, 8, 16, 32, 64, 128, 256};
const int box_splitter[9][2] = {{0, 0}, {3, 0}, {6, 0}, {0, 3}, {3, 3}, {6, 3}, {0, 6}, {3, 6}, {6, 6}};

const int all_candidates = 511;
const int board_size = 9;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Error.");
        return 1;
    }

    Cell*** board = createBoard();
    Lines** box = createBox(board);
    Lines** rows = createLines(board, 0);
    Lines** columns = createLines(board, 1);

    int placeholder;
    char* input = argv[1];
    int solveCounter = 0;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            placeholder = input[9*i + j] - 49;

            if (placeholder > -1) {
                solveCounter++;
                box[(i/3)*3 + (j/3)] -> eliminations += bit_changer[placeholder];
                rows[i] -> impossibleValue += bit_changer[placeholder];
                columns[j] -> impossibleValue += bit_changer[placeholder];
                board[i][j] -> possibility = 0;
            }
            board[i][j] -> value = placeholder;
        }
    }

    while (solveCounter < 81) {
        possibilityCleaner(board, box, rows, columns);

        placeholder = cellChecker(board, box, rows, columns);
        if (placeholder != 0) {
            solveCounter += placeholder;
            continue;
        }

        placeholder = hiddensingles(board, box, rows, columns);
        if (placeholder != 0) {
            continue;
        }

        placeholder = clearpair(board, box, rows, columns);
        if (placeholder != 0) {
            continue;
        }

        placeholder = hiddenpair(board, box, rows, columns);
        if (placeholder != 0) {
            continue;
        }

        placeholder = cleartriple(board, box, rows, columns);
        if (placeholder != 0) {
            continue;
        }

        placeholder = hiddentriple(board, box, rows, columns);
        if (placeholder != 0) {
            continue;
        }

        solveCounter = 81;
    }
    displayBoard(board);
    memoryCleaner(board, box, rows, columns);
}
