/*
 * AuctionProof.h
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#ifndef AUCTIONPROOF_H_
#define AUCTIONPROOF_H_

#include <vector>
#include "ComparisonProof.h"

using namespace std;

class AuctionProof {
public:
	int proofID;
	vector<vector<ComparisonProof *> > bidsInRanges; //proof that 0 <= xi <= p/2
	vector<vector<ComparisonProof *> > diffsInRanges; //proof that 0 <= x1-xi <= p/2
    //vector<vector<ZZ > > tsValues; // prove of n_i = x_1 - x_i (for prover)
//    vector<vector<Com > > tcomsValues; // prove of n_i = x_1 - x_i (for verifier)

	AuctionProof(int proofID);
};

#endif /* AUCTIONPROOF_H_ */
