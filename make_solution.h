#ifndef MAKE_SOLUTION_H_
#define MAKE_SOLUTION_H_

#include "general_definitions.h"

enum Adjacent {adjacent = 1, notAdjacent = 0, ignored = -1};

void createEqualVersesList(Verse *verses, int listSize, int **equalVersesList);
// this function creates a list which stores data about which verses are equal
// to which

void printSolution(int listSize, int **equalVersesList);

#endif /* MAKE_SOLUTION_H_ */
