#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include "general_definitions.h"
#include "word_recognition.h"

static void setWordDataDefaultValues(WordData *wordData) {
	wordData->positiveInteger = 0;
	wordData->negativeInteger = 0;
	wordData->floatingNumber = 0;
	wordData->notNumber = NULL;
}

static bool isInteger(long double x) {
	if(floorl(x) == x) return 1;
	return 0;
}

static bool startsWith0X(char *word) {
	if(strlen(word) >= 2 && word[0] == '0' && (word[1] == 'x' || word[1] == 'X')) {
		return 1;
	}
	if(strlen(word) >= 3 && (word[0] == '-' || word[0] == '+') && word[1] == '0'
			&& (word[2] == 'x' || word[2] == 'X')) {
		return 1;
	}

	return 0;
}

static bool stringSuccessfullyConverted(char *unconvertedString) {
	// check if ERANGE or EINVAL errors occured and check if the string
	// was fully converted after strto_() function
	if(errno == ERANGE || errno == EINVAL ||
			strcmp(unconvertedString, "") != 0) {
		errno = 0; // reset errno value before next use of strto_()
		return 0;
	}

	errno = 0; // reset errno value
	return 1;
}

static void setWordData(WordData *wordData, char *wordToConvert, int wordType,
		int conversionBase) {
	char *endptr = NULL;

	switch(wordType) {
	case 0:
		wordData->wordType = negativeInt;
		long double number;
		number = strtold(wordToConvert, &endptr);
		wordData->negativeInteger = (long long) number;
		break;

	case 1:
		wordData->wordType = positiveInt;
		if(conversionBase == 8 || conversionBase == 16) {
			unsigned long long numberULL;
			numberULL = strtoull(wordToConvert, &endptr, conversionBase);
			wordData->positiveInteger = numberULL;
		}
		else { // word is decimal
			long double number;
			number = strtold(wordToConvert, &endptr);
			wordData->positiveInteger = (unsigned long long) number;
		}
		break;
	case 2:
		wordData->wordType = floatNumber;
		number = strtold(wordToConvert, &endptr);
		wordData->floatingNumber = number;
		break;
	case 3:
		wordData->wordType = notANumber;

		int wordToConvertLength = (int) strlen(wordToConvert);
		for(int i = 0; i < wordToConvertLength; i++) {
			wordToConvert[i] = tolower(wordToConvert[i]);
		}

		wordData->notNumber = malloc(strlen(wordToConvert) + 1);
		strcpy(wordData->notNumber, wordToConvert);
		break;
	}
}

WordData getWordData(char *word) {
	WordData wordData; // this will be returned
	char *unconvertedWordPart = NULL; // part of word that is not converted
	// after using strto_() function
	setWordDataDefaultValues(&wordData);

	// checking if [word] is a positive integer in octal format
	strtoull(word, &unconvertedWordPart, 8);
	if(stringSuccessfullyConverted(unconvertedWordPart) && word[0] == '0') {
		setWordData(&wordData, word, positiveInt, 8);
		return wordData;
	}
	else {

		// checking if [word] is a positive integer in hexadecimal format
		strtoull(word, &unconvertedWordPart, 16);
		if(stringSuccessfullyConverted(unconvertedWordPart) && startsWith0X(word)
				&& word[0] != '-' && word[0] != '+') {
			setWordData(&wordData, word, positiveInt, 16);
			return wordData;
		}
		else if(startsWith0X(word) && strlen(word) == 2) { // "0x" = 0, but
			// strtoull doesn't convert "0x" to 0 hence this condition
			setWordData(&wordData, "0x0", positiveInt, 16);
			return wordData;
		}
		else {

			// checking if [word] is a floating/integer number in decimal format
			long double number = strtold(word, &unconvertedWordPart);
			if(stringSuccessfullyConverted(unconvertedWordPart)) {

				if(isnan(number)) {
					setWordData(&wordData, word, notANumber, 0);
					return wordData;
				}
				if(startsWith0X(word)) {
					setWordData(&wordData, word, notANumber, 0);
					return wordData;
				} // strtold() converts hexadecimal values which we don't want
				// to be converted

				if(isInteger(number)) {
					if(number < 0) {
						if(number >= (long double) LLONG_MIN) { // checking
							// if [number] is in range of negativeInt
							setWordData(&wordData, word, negativeInt, 10);
							return wordData;
						}
						else {
							setWordData(&wordData, word, floatNumber, 10);
							return wordData;
						}
					}
					else {
						if(number <= (long double) ULLONG_MAX) { // checking
							// if [number] is in range of positiveInt
							setWordData(&wordData, word, positiveInt, 10);
							return wordData;
						}
						else {
							setWordData(&wordData, word, floatNumber, 10);
							return wordData;
						}
					}
				}
				else {
					setWordData(&wordData, word, floatNumber, 10);
					return wordData;
				}
			}
			else {
				// [word] didn't meet any previous conditions so it's not a number
				setWordData(&wordData, word, notANumber, 0);
				return wordData;
			}
		}
	}
}

