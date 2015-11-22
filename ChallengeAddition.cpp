/*
 * ChallengeAddition.cpp
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#include "ChallengeAddition.h"

ChallengeAddition::ChallengeAddition(int bit,
		const vector<ComparisonProof *>& validityProofs,
		const vector<ComparisonProof *>& orderingProofs,
		int winner)
		: Challenge(bit+1) {
	this->bit = bit;

	for (int i = 0; i < (int)validityProofs.size(); ++i)
		validityReveals.push_back(new RevealComparisonAddition(validityProofs[i], bit));

	for (int i = 0; i < (int)orderingProofs.size(); ++i) {
		if (i == winner)
			orderingReveals.push_back(new RevealComparisonAddition());
		else
			orderingReveals.push_back(new RevealComparisonAddition(orderingProofs[i], bit));
	}
}

size_t ChallengeAddition::size() {
	size_t out = sizeof(ChallengeAddition);

	for (int i = 0; i < (int)validityReveals.size(); ++i)
		out += validityReveals[i]->size();

	for (int i = 0; i < (int)orderingReveals.size(); ++i)
		out += orderingReveals[i]->size();

	return out;
}
