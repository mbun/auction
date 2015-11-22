/*
 * BidPackage.cpp
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#include "BidPackage.h"
/*
BidPackage::BidPackage() {
}
*/
BidPackage::BidPackage(int playerID, ZZ bid, SignedCommitment bidSC,
		vector<PairRep> reps, vector<PairSC> repSCs) {
	this->playerID = playerID;
	this->bid = bid;
	this->bidSC = bidSC;
	this->reps = reps;
	this->repSCs = repSCs;
}

size_t BidPackage::size() {
	size_t out = sizeof(BidPackage) + bid.size() + bidSC.size();

	for (int i = 0; i < (int)reps.size(); ++i)
		out += reps[i].first.size() + reps[i].second.size();

	for (int i = 0; i < (int)repSCs.size(); ++i)
		out += repSCs[i].first.size() + repSCs[i].second.size();
    return out;
}

