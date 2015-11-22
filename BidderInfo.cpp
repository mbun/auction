/*
 * BidderInfo.cpp
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#include "BidderInfo.h"

BidderInfo::BidderInfo(const BidPackage &bidpack) {
	this->playerID = bidpack.playerID;
	for (int i = 0; i < (int)bidpack.repSCs.size(); ++i)
		repComs.push_back(PairSS(bidpack.repSCs[i].first.value, bidpack.repSCs[i].second.value));
	for (int i = 0; i < (int)bidpack.repSCs.size(); ++i)
		repSigs.push_back(PairSigSig(bidpack.repSCs[i].first.signature, bidpack.repSCs[i].second.signature));
}
