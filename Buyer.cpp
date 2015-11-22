/*
 * Buyer.cpp
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#include "Buyer.h"
#include "PublicBoard.h"
#include "Bidpackage.h"
#include "SignedCommitment.h"

Buyer::Buyer(int i) : Player(i) {

}

bool Buyer::placeBid (size_t auctioneer_index, int auctionID, ZZ amount) {
	ZZ p = board->getPrime();
	DSA* dsa = board->getDSA();
	int soundness = board->getAuctionInfo(auctionID)->getSoundness();
	SignedCommitment bidSC(amount, signingKey, dsa);

	vector<PairRep> reps;
	vector<PairSC> repSCs;

	for (int i = 0; i < soundness; ++i) {
		PairRep rep = PairRep(amount, p);
		PairSC repSC(SignedCommitment(rep[0], signingKey, dsa), SignedCommitment(rep[1], signingKey, dsa));
		reps.push_back(rep);
		repSCs.push_back(repSC);
	}
	return auctioneers[auctioneer_index]->requestBid(auctionID, BidPackage(id, amount, bidSC, reps, repSCs));
}
