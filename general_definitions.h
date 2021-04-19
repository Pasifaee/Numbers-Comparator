#ifndef STRUCT_DEFINITIONS_H_
#define STRUCT_DEFINITIONS_H_

#include <stdbool.h>

#define INITIAL_ARRAY_SIZE 4

typedef struct WordData { // stores information about a word
	enum {negativeInt, positiveInt, floatNumber, notANumber} wordType;
	union {
		unsigned long long positiveInteger;
		long long negativeInteger;
		long double floatingNumber;
		char *notNumber;
	};
} WordData;

typedef struct Verse { // stores information about words in a verse
	bool is_ignored;
	int size;
	WordData *words;
} Verse;

typedef struct VerseArray { // stores array of all verses from input
	Verse *verses;
	int size;
} VerseArray;

#endif /* STRUCT_DEFINITIONS_H_ */
