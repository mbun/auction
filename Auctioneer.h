/*
 * Auctioneer.h
 *
 *  Created on: Apr 23, 2015
 *      Author: Tom
 */

#ifndef AUCTIONEER_H_
#define AUCTIONEER_H_

#include <vector>
#include <map>
using namespace std;

#include <NTL/ZZ.h>
using namespace NTL;

#include "Article.h"
#include "Auction.h"
#include "PublicBoard.h"
#include "AuctionProofCommitments.h"
#include "ChallengeAddition.h"
#include "ChallengeMultiplication.h"

class Auctioneer {
private:
	map<int,Auction*> auctions;
	int auctionCounter;
	PublicBoard* board;
	map<int,AuctionProof*> proofs;
	int proofCount;
	ZZ priceLimit;

	bool verifyBidPackage(int auctionID, BidPackage bid);

public:
	Auctioneer(ZZ priceLimit);
	friend ostream& operator<<(ostream& os, const Auctioneer& auctioneer);

	void assignPublicBoard(PublicBoard *pb);

	int requestAuction(int seller_id, Article* article, int soundness); //returns auctionID

	vector<int> getAuctionIDs();

	bool requestBid(int auctionID, BidPackage bid); //returns accept/reject

	bool resolveAuction(int auctionID); //returns success/failure

	bool requestProof(int auctionID, AuctionProofCommitments *&proofCommitments);

	bool challenge(int auctionID, int proofID, vector<int> challengeTypes,
			vector<ChallengeAddition*>& responseAdds, vector<ChallengeMultiplication*>& responseMults);
};

#endif /* AUCTIONEER_H_ */
