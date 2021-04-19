#include <string.h>
#include "general_definitions.h"

int compareWordDatas(const void *fst, const void *snd) {
	// function made primarly to sort arrays of word datas and then compare them;
	// word types values order is:
	// negativeInt < positiveInt < floatNumber < notANumber
	// and this is the order in which word datas will be sorted

	WordData fstWordData = *(WordData*)fst;
	WordData sndWordData = *(WordData*)snd;

	if(fstWordData.wordType < sndWordData.wordType) {
		return -1;
	}
	else if(fstWordData.wordType > sndWordData.wordType) {
		return 1;
	}
	else { // wordTypes of the wordDatas are equal
		switch(fstWordData.wordType) {
		case negativeInt:
			if(fstWordData.negativeInteger < sndWordData.negativeInteger)
				return -1;
			else if(fstWordData.negativeInteger > sndWordData.negativeInteger)
				return 1;
			else
				return 0;
			break;
		case positiveInt:
			if(fstWordData.positiveInteger < sndWordData.positiveInteger)
				return -1;
			else if(fstWordData.positiveInteger > sndWordData.positiveInteger)
				return 1;
			else
				return 0;
			break;
		case floatNumber:
			if(fstWordData.floatingNumber < sndWordData.floatingNumber)
				return -1;
			else if(fstWordData.floatingNumber > sndWordData.floatingNumber)
				return 1;
			else
				return 0;
			break;
		case notANumber:
			return strcmp(fstWordData.notNumber, sndWordData.notNumber);
			break;
		default:
			return 0;
		}
	}
}

bool versesAreEqual(Verse verse1, Verse verse2) { // checks if two verses
		// consist of the same multisets of words, given that verses are sorted
	if(verse1.size != verse2.size) {
		return 0;
	}

	int versesSize = verse1.size;
	for(int i = 0; i < versesSize; i++) {
		if(compareWordDatas(&verse1.words[i], &verse2.words[i]) != 0) return 0;
	}

	return 1;
}
