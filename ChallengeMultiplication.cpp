/*
 * ChallengeMultiplication.cpp
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#include "ChallengeMultiplication.h"

ChallengeMultiplication::ChallengeMultiplication(int bit,
		const vector<ComparisonProof *>& validityProofs,
		const vector<ComparisonProof *>& orderingProofs,
		int winner)
		: Challenge(bit+3) {
	this->bit = bit;

	for (int i = 0; i < (int)validityProofs.size(); ++i)
		validityReveals.push_back(new RevealComparisonMultiplication(validityProofs[i], bit, 1));
	for (int i = 0; i < (int)orderingProofs.size(); ++i) {
		if (winner == i)
			orderingReveals.push_back(new RevealComparisonMultiplication());
		else
			orderingReveals.push_back(new RevealComparisonMultiplication(orderingProofs[i], bit, 0));
	}
}

size_t ChallengeMultiplication::size() {
	size_t out = sizeof(ChallengeMultiplication);

	for (int i = 0; i < (int)validityReveals.size(); ++i)
		out += validityReveals[i]->size();

	for (int i = 0; i < (int)orderingReveals.size(); ++i)
		out += orderingReveals[i]->size();

	return out;
}
