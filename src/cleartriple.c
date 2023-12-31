#include "cleartriple.h"

int clearTripleSpotter(Cell*** board, Lines* group, Reduce** head) {
    int counter = 0;
    int rangeA, rangeB, rangeC;

    for (int i = 0; i < 9; i++) {
        if (group -> memberArray[i] -> value != -1) continue;
        rangeA = group -> memberArray[i] -> possibility;

        for (int j = i + 1; j < 9; j++) {
            if (group -> memberArray[j] -> value != -1) continue;
            rangeB = rangeA | group -> memberArray[j] -> possibility;

            for (int k = 0; k < 9; k++) {
                if (group -> memberArray[k] -> value != -1) continue;
                rangeC = rangeA | rangeB | group -> memberArray[k] -> possibility;

                if (bitCounter(rangeC) == 3) {
                    if (group -> memberArray[i] -> marked != 1 && group -> memberArray[j] -> marked != 1 && group -> memberArray[k] -> marked != 1)
                    counter++;

                    group -> memberArray[i] -> marked = 1;
                    group -> memberArray[j] -> marked = 1;
                    group -> memberArray[k] -> marked = 1;

                    int* exclude = malloc(sizeof(int) * 9);
                    exclude[i] = 1;
                    exclude[j] = 1;
                    exclude[k] = 1;

                    newBlank(head, (~rangeC) & all_candidates, group -> memberArray, exclude);
                }
            }
        }
    }
    return counter;
}

int clearTripleChecker(Cell*** board, Lines** box, Lines** rows, Lines** columns) {
    int counter = 0;
    Reduce* head = NULL;

    markerCleaner(board);
    for (int mem = 0; mem < 9; mem++) {
        counter += clearTripleSpotter(board, rows[mem], &head);
        counter += clearTripleSpotter(board, columns[mem], &head);
        counter += clearTripleSpotter(board, box[mem], &head);
    }

    applyBlank(&head);
    return counter;
}