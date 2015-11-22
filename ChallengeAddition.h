/*
 * ChallengeAddition.h
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#ifndef CHALLENGEADDITION_H_
#define CHALLENGEADDITION_H_

#include <vector>
#include "Challenge.h"
#include "RevealComparisonAddition.h"
#include "ComparisonProof.h"

class ChallengeAddition: public Challenge {
public:
	int bit;
	vector<RevealComparisonAddition *> validityReveals;
	vector<RevealComparisonAddition *> orderingReveals;
	ChallengeAddition(int bit,
			const vector<ComparisonProof *>& validityProofs,
			const vector<ComparisonProof *>& orderingProofs,
			int winner);

	size_t size();
};

#endif /* CHALLENGEADDITION_H_ */
