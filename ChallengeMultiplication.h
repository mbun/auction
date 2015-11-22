/*
 * ChallengeMultiplication.h
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#ifndef CHALLENGEMULTIPLICATION_H_
#define CHALLENGEMULTIPLICATION_H_

#include <vector>
#include "Challenge.h"
#include "RevealComparisonMultiplication.h"
#include "ComparisonProof.h"

class ChallengeMultiplication: public Challenge {
public:
	int bit;
	vector<RevealComparisonMultiplication *> validityReveals;
	vector<RevealComparisonMultiplication *> orderingReveals;
	ChallengeMultiplication(int bit,
			const vector<ComparisonProof *>& validityProofs,
			const vector<ComparisonProof *>& orderingProofs,
			int winner);

	size_t size();
};

#endif /* CHALLENGEMULTIPLICATION_H_ */
