#include <stdio.h>
#include <stdlib.h>
#include "general_definitions.h"
#include "verse_comparison.h"

void createEqualVersesList(Verse *verses, int numberOfVerses, int **equalVersesList) {
	// This function creates a two-dimensional list indicating which verses are
	// equal to which.
	// In the equalVersesList[i] there'll be stored a list of numbers of verses
	// that are equal to the i_th verse.
	// In the equalVersesList[i][0] there'll be stored information if i_th verse
	// should be ignored. -1 -> ignored; 0 -> not ignored
	// The verse should be ignored if
	// - verse.is_ignored == 1
	// - a previous verse has already been found equal to this verse - because
	// this means that this verse is equal to each verse that the previous one
	// was equal to, and there's no other verse that is equal to this verse.
	// After numbers of verses equal to i_th verse there'll be placed a [0]
	// to indicate list ending.
	for(int i = 1; i < numberOfVerses; i++) {
		equalVersesList[i] = malloc(sizeof(int));
		if(verses[i].is_ignored) {
			equalVersesList[i][0] = -1;
		}
		else {
			equalVersesList[i][0] = 0;
		}
	}

	for(int i = 1; i < numberOfVerses; i++) {
		if(equalVersesList[i][0] == -1) continue;

		int index = 1;
		int currentSize = INITIAL_ARRAY_SIZE;
		equalVersesList[i] = realloc(equalVersesList[i], currentSize * sizeof(int));

		for(int j = i; j < numberOfVerses; j++) {
			if(!verses[j].is_ignored && versesAreEqual(verses[i], verses[j])) {
				equalVersesList[i][index] = j;
				if(i != j) {
					equalVersesList[j][0] = -1;
				}
				if(index == currentSize) {
					currentSize *= 2;
					equalVersesList[i] = realloc(equalVersesList[i], currentSize * sizeof(int));
				}
				index++;
			}
		}

		equalVersesList[i][index] = 0; // adding 0 at the end to indicate array ending
	}

}

void printSolution(int numberOfVerses, int **equalVersesList) {
	// To print a solution in ascending order we only need to go through the
	// [equalVersesList] and print [equalVersesList[i]] if its first position
	// isn't set to -1

	bool firstVersePrinted = 0; // we need to know if any verse was printed
	// to print "\n" otherwise

	for(int i = 1; i < numberOfVerses; i++) {
		if(equalVersesList[i][0] != -1) {
			bool firstWordPrinted = 0;
			int j = 1;
			while(equalVersesList[i][j] != 0) {
				if(!firstWordPrinted) {
					printf("%d", equalVersesList[i][j]);
					firstWordPrinted = 1;
				}
				else {
					printf(" %d", equalVersesList[i][j]);
				}
				j++;
			}
			if(!firstVersePrinted) firstVersePrinted = 1;
			printf("\n");
		}
	}

	if(!firstVersePrinted) printf("\n"); // if no verse has been printed
	// print new line so the output always ends with newline

}
