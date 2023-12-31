#include "hiddentriple.h"

int hiddenTripleSpotter(Cell*** board, Lines* group, Reduce** head) {
    int counter = 0;

    int placeholder, rangeA, rangeB, rangeC;

    for (int i = 0; i < 9; i++) {
        if (group -> memberArray[i] -> value != -1) continue;
        rangeA = group -> memberArray[i] -> possibility;

        for (int j = 0; j < 9; j++) {
            if (group -> memberArray[j] -> value != -1) continue;
            rangeB = group -> memberArray[j] -> possibility;
            
            for (int k = 0; k < 9; k++) {
                if (group -> memberArray[k] -> value != -1) continue;
                rangeC = group -> memberArray[k] -> possibility;

                placeholder = 0;

                for (int m = 0; m < 9; m++) {
                    if (m == i || m == j || m == k) continue;

                    placeholder != group -> memberArray[m] -> possibility;
                }

                placeholder = ~placeholder & all_candidates;
                if(bitCounter(rangeA & placeholder) < 2) continue;
                if(bitCounter(rangeB & placeholder) < 2) continue;
                if(bitCounter(rangeC & placeholder) < 2) continue;

                placeholder = (rangeA & placeholder) | (rangeB & placeholder) | (rangeC & placeholder);

                if((rangeA | rangeB | rangeC) == placeholder) continue;

                if (bitCounter(placeholder) == 3) {
                    if (group -> memberArray[i] -> marked != 1 && group -> memberArray[j] -> marked != 1 && group -> memberArray[k] -> marked != 1)
                        counter++;
                    
                    group -> memberArray[i] -> marked = 1;
                    group -> memberArray[j] -> marked = 1;
                    group -> memberArray[k] -> marked = 1;

                    int* exclude = malloc(sizeof(int) * 9);
                    
                    for (int m = 0; m < 9; m++) {
                        if (m == i || m == j || m == k) continue;

                        exclude[m] = 1;
                    }

                    newBlank(head, placeholder, group -> memberArray, exclude);
                }
            }
        }
    }

    return counter;
}

int hiddenTripleChecker(Cell*** board, Lines** box, Lines** rows, Lines** columns) {
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