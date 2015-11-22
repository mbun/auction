/*
 * AuctionProofCommitments.h
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#ifndef AUCTIONPROOFCOMMITMENTS_H_
#define AUCTIONPROOFCOMMITMENTS_H_

#include <vector>
#include "ComparisonProofCommitments.h"
#include "AuctionProof.h"
using namespace std;

class AuctionProofCommitments {
public:
	int proofID;
	vector<vector<ComparisonProofCommitments *> > bidsInRangeComs;
	vector<vector<ComparisonProofCommitments *> > diffsInRangeComs;
//    vector<vector<string> > tComs;
	//AuctionProofCommitments();
	AuctionProofCommitments(AuctionProof *proof);

	size_t size();
};

#endif /* AUCTIONPROOFCOMMITMENTS_H_ */
