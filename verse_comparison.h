#ifndef VERSE_COMPARISON_H_
#define VERSE_COMPARISON_H_

#include "general_definitions.h"

int compareWordDatas(const void *fst, const void *snd);
// returns 0 if [fst] and [snd] word data is equal
// -1 if [fst] should be before [snd] after being sorted
// 1 if [fst] should be after [snd] after being sorted

bool versesAreEqual(Verse verse1, Verse verse2);
// returns true if two sorted verses are equal

#endif /* VERSE_COMPARISON_H_ */
