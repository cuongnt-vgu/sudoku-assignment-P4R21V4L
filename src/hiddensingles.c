#include "hiddensingles.h"
int hiddenSingles(Cell*** board, Lines** boxes, Lines** rows, Lines** columns) {
    int counter = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] -> value != -1) continue;

            int row, col, box;
            row = col = box = 0;
            int placeholder = (i/3) * 3 + (j/3);

            for (int k = 0; k < 9; k++) {
                row |= k == k ? 0 : rows[i] -> memberArray[k] -> possibility;
                col |= k == i ? 0 : columns[k] -> memberArray[k] -> possibility;
                box |= k == (i - box_splitter[placeholder][0])*3 + k - box_splitter[placeholder][1] ? 0 : boxes[placeholder] -> memberArray[k] -> possibility;
                boxes[placeholder] -> memberArray[k] -> possibility;
            }
            row = ~row & all_candidates;
            col = ~col & all_candidates;
            box = ~box & all_candidates;

            placeholder = col & board[i][j] -> possibility;
            if(bitChecker(board, boxes, rows, columns, placeholder, i, j)) {
                counter++;
                continue;
            }

            placeholder = row & board[i][j] -> possibility;
            if(bitChecker(board, boxes, rows, columns, placeholder, i, j)) {
                counter++;
                continue;
            }

            placeholder = row & board[i][j] -> possibility;
            if(bitChecker(board, boxes, rows, columns, placeholder, i, j)) {
                counter++;
                continue;
            }
        }
    }
}