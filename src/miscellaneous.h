#pragma once

#include "blocks.h"
#include <stdlib.h>
#include <stdio.h>


void displayBoard(Cell*** boardPointer);
void possibilityCleaner(Cell*** board, Lines** box, Lines** rows, Lines** columns);
void markerCleaner(Cell*** board);
int BoardChecker(Cell*** board);
int bitCounter (int flow);
int bitChecker(Cell*** board, Lines** box, Lines** rows, Lines** columns, int bit, int i, int j);
int cellChecker(Cell*** board, Lines** box, Lines** rows, Lines** columns);
Cell* createCell();
Cell*** createBoard();
Lines** createBox(Cell*** board);
Lines** createLines(Cell*** board, int aspect);
void newBlank(Reduce** head, int blank, Cell** appliedCells, int* exceptions);
Reduce* getBlank(Reduce** head);
void applyBlank(Reduce** head);
void memoryCleaner(Cell*** board, Lines** box, Lines** row, Lines** column);