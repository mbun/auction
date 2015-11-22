/*
 * RevealComparisonMultiplication.h
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#ifndef REVEALCOMPARISONMULTIPLICATION_H_
#define REVEALCOMPARISONMULTIPLICATION_H_

#include "ComparisonProof.h"

class RevealComparisonMultiplication {
public:
	PairCR Y; //to prove that Y is 0 (when applicable)

	PairCR A, B, C, D; //A is either (A1[0], A2[1]) or (A1[1],A2[0])
	PairCR MA, MB, MC, MD; //MA is either MA1 or MA2 from proof, should have that MA[0]+MA[1] = A[0]*A[1]

	PairCR W0A, W0B, W0C, W0D;
	PairCR W1A, W1B, W1C, W1D;

	RevealComparisonMultiplication();
	RevealComparisonMultiplication(ComparisonProof *proof, int bit, bool revealY);

	size_t size();
};

#endif /* REVEALCOMPARISONMULTIPLICATION_H_ */
