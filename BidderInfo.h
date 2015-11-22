/*
 * BidderInfo.h
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#ifndef BIDDERINFO_H_
#define BIDDERINFO_H_

#include "ComparisonProofCommitments.h"
#include "BidPackage.h"
#include "SignedCommitment.h"

typedef pair<Signature, Signature> PairSigSig;

class BidderInfo {
public:
	int playerID;
	vector<PairSS> repComs;
	vector<PairSigSig> repSigs;
	BidderInfo(const BidPackage &bidpack);
};

#endif /* BIDDERINFO_H_ */
