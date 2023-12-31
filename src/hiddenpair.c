#include "hiddenpair.h"

int hiddenPairSpotter(Cell*** board, Lines* group, Reduce** head) {
    int counter = 0;

    int rangeA, rangeB, placeholder;

    for (int i = 0; i < 9; i++) {
        if (group -> memberArray[i] -> value != -1) continue;
        rangeA = group -> memberArray[i] -> possibility;

        for (int j = 0; j < 9; i++) {
            if (group -> memberArray[j] -> value != -1) continue;
            rangeB = group -> memberArray[j] -> possibility;

            placeholder = 0;

            for (int k = 0; k < 9; k++) {
                if (k == 1 || k == j) continue;

                placeholder != group -> memberArray[k] -> possibility;
            }

            placeholder = ~placeholder & all_candidates;

            placeholder = (rangeA & placeholder) | (rangeB & placeholder);

            if (placeholder == rangeA && placeholder == rangeB) continue;

            if(bitCounter(placeholder) == 2) {
                if (group -> memberArray[i] -> marked != 1 && group -> memberArray[j] -> marked != 1)
                    counter++;
                group -> memberArray[i] -> marked = 1;
                group -> memberArray[j] -> marked = 1;

                int* exclude = malloc(sizeof(int) * 9);
                for (int m = 0; m < 9; m++) {
                    if(m == i || m == j) continue;
                    exclude[m] = 1;
                }

                newBlank(head, placeholder, group -> memberArray, exclude);

                rangeA &= placeholder;
                rangeB &= placeholder;
            }
    
        }
    }

    return counter;
}

int hiddenPairChecker(Cell*** board, Lines** box, Lines** rows, Lines** columns) {
    int counter = 0;
    Reduce* head = NULL;

    markerCleaner(board);
    for(int mem = 0; mem < 9; mem++) {
        counter += hiddenPairSpotter(board, rows[mem], &head);
        counter += hiddenPairSpotter(board, columns[mem], &head);
        counter += hiddenPairSpotter(board, box[mem], &head);
    }

    applyBlank(&head);
    return counter;
}