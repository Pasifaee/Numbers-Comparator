#ifndef WORD_RECOGNITION_H_
#define WORD_RECOGNITION_H_

#include "general_definitions.h"

WordData getWordData(char *word);
// this function gets word data from a given word - it defines its type
// (positive integer / negative integer / floating number / not a number)
// and value

#endif /* WORD_RECOGNITION_H_ */
