#include <stdio.h>
#include <stdlib.h>
#include "read_input.h"
#include "general_definitions.h"
#include "make_solution.h"

void freeMemory(VerseArray verseArray, int *equalVersesList[]) { // this function
	// frees memory allocated inside [verseArray] and [equalVersesList]

	for(int i = 1; i < verseArray.size; i++) {
		Verse currentVerse = verseArray.verses[i];
		for(int j = 0; j < currentVerse.size; j++) {
			if(currentVerse.words[j].wordType == notANumber) { // [notNumber]
			// pointer has been allocated only if [words[j].wordType == notANumber]
				free(currentVerse.words[j].notNumber);
			}
		}
		free(currentVerse.words);
	}
	free(verseArray.verses);

	for(int i = 1; i < verseArray.size; i++) {
		free(equalVersesList[i]);
	}
}

int main() {
	VerseArray verseArray = loadVerses();
	Verse *verses = verseArray.verses;

	int *equalVersesList[verseArray.size]; // equalVersesList will store data about
	// which verses are equal to which
	createEqualVersesList(verses, verseArray.size, equalVersesList);

	printSolution(verseArray.size, equalVersesList);

	freeMemory(verseArray, equalVersesList);

	exit(0);
}



