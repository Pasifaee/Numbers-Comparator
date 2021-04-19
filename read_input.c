#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "general_definitions.h"
#include "word_recognition.h"
#include "verse_comparison.h"

static void setVerseDefaultValues(Verse *verse) {
	verse->is_ignored = 0;
	verse->size = 0;
}

static bool isRegularASCIICharacter (char letter) {
	if(letter < 33 || letter > 126) return 0;
	else return 1;
}

static void getVerseDataFromLine(char *line, Verse *verse, int verseNumber) {
	size_t currentSize = INITIAL_ARRAY_SIZE;
	setVerseDefaultValues(verse);
	verse->words = malloc(currentSize * sizeof(WordData));
	int index = 0; // current [words] array index

	if(line[0] == '#') {
		verse->is_ignored = 1;
		return;
	}

	char *newWord = NULL; // stores last found word in the line
	bool errorOccurred = 0; // is set to 1 if a character in verse isn't regular
	int lineLength = (int) strlen(line);
	for(int i = 0; i < lineLength; i++) { // searching for a new word
		if(errorOccurred) break;

		if(!isspace(line[i])) { // new word found
			newWord = (line + i);

			for(int j = i; j < lineLength; j++) { // dealing with [newWord]
				if(isspace(line[j])) {
					// putting newWord to new location
					char newWordNewLocation[strlen(newWord)]; // setting array
					// size to [strlen(newWord)] so it can be copied safely
					strcpy(newWordNewLocation, newWord);
					newWord = newWordNewLocation;
					newWord[j - i] = '\0'; // mark [newWord] ending

					i = j; // start searching for the next word from [j] position
							// in outer loop
					verse->words[index] = getWordData(newWord);

					// reallocate [words] array if needed
					index++;
					if(index == (int) currentSize) {
						currentSize *= 2;
						verse->words =
								realloc(verse->words, currentSize * sizeof(WordData));
					}
					break;
				}
				if(!isRegularASCIICharacter(line[j])) {
					fprintf(stderr, "ERROR %d\n", verseNumber);
					errorOccurred = 1;
					verse->is_ignored = 1;
					break;
				}
			}
		}
	}

	if(index == 0) {
		verse->is_ignored = 1; // verse with no words is ignored
	}

	verse->size = index;
}

VerseArray loadVerses() {

	VerseArray verseArray; // this will be returned
	Verse *verses = NULL;
	int versesSize = INITIAL_ARRAY_SIZE;
	verses = malloc(versesSize * sizeof(Verse));

	int index = 1;
	char *line = NULL;
	size_t getlineSize;
	while(getline(&line, &getlineSize, stdin) != -1) {
		// reallocate [verses] if needed
		if(index == versesSize) {
			versesSize *= 2;
			verses = realloc(verses, versesSize * sizeof(Verse));
		}

		getVerseDataFromLine(line, &verses[index], index);
		qsort(verses[index].words, verses[index].size,
				sizeof(WordData), compareWordDatas);

		index++;
	}
	verseArray.verses = verses;
	verseArray.size = index; // [verseArray.size] is equal to number of verses + 1
	// which makes indexing verses from 1 easier
	free(line);

	return verseArray;
}
