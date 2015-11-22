/*
 * BidPackage.h
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#ifndef BIDPACKAGE_H_
#define BIDPACKAGE_H_

#include <vector>
#include <utility>
#include <NTL/ZZ.h>
#include "PairRep.h"
#include "SignedCommitment.h"
using namespace NTL;
using namespace std;

typedef pair<SignedCommitment,SignedCommitment> PairSC;

class BidPackage {
public:
	int playerID;
	ZZ bid;
	SignedCommitment bidSC;
	vector<PairRep> reps;
	vector<PairSC> repSCs;

	BidPackage(int playerID, ZZ bid, SignedCommitment bidSC,
			vector<PairRep> reps, vector<PairSC> repSCs);

	size_t size();
};

#endif /* BIDPACKAGE_H_ */
