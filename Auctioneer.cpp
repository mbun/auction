/*
 * Auctioneer.cpp
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#include <NTL/ZZ.h>
using namespace NTL;

#include "BidPackage.h"
#include "Auctioneer.h"
#include "ChallengeAddition.h"
#include "ChallengeMultiplication.h"

typedef pair<Commitment,Commitment> PairCom;

bool Auctioneer::verifyBidPackage(int auctionID, BidPackage bidPack) { //returns 1 if valid, 0 otherwise
	if (bidPack.bid > board->getMaxBid()) {
		cerr << "Bid exceed maxBid\n";
		return false;
	}

	ZZ key = board->getPublicKey(bidPack.playerID);

	if (!bidPack.bidSC.verify(key)) {
		cerr << "Key verification failed\n";
		return false;
	}

	if (!SHACommit::checkReveal(bidPack.bid, bidPack.bidSC.value, bidPack.bidSC.opening))
		return false;

	int soundness = auctions[auctionID]->getSoundness();

	if ((int)bidPack.reps.size() != soundness)
		return false;
	if ((int)bidPack.repSCs.size() != soundness)
		return false;

	for (int i = 0; i < soundness; ++i) {

		if ((bidPack.reps[i].first + bidPack.reps[i].second) % board->getPrime() != bidPack.bid)
			return false;
		SignedCommitment repSC1 = bidPack.repSCs[i].first;
		SignedCommitment repSC2 = bidPack.repSCs[i].second;
		if (!repSC1.verify(key) || !repSC2.verify(key))
			return false;
		if (!SHACommit::checkReveal(bidPack.reps[i].first, repSC1.value, repSC1.opening))
			return false;
		if (!SHACommit::checkReveal(bidPack.reps[i].second, repSC2.value, repSC2.opening))
			return false;
	}
	return true;
}

Auctioneer::Auctioneer(ZZ priceLimit) {
	this->priceLimit = priceLimit;
	auctionCounter = 0;
	proofCount = 0;
}

ostream& operator<<(ostream& os, const Auctioneer& auctioneer) {
	os << "Auctioneer " << &auctioneer;
	return os;
}

void Auctioneer::assignPublicBoard(PublicBoard *pb) {
	board = pb;
}

int Auctioneer::requestAuction(int seller_id, Article *article, int soundness) {
	int auctionID = auctionCounter;
	auctionCounter += 1;

	Auction *auction = new Auction(auctionID, soundness, seller_id, article);
	cout << "[Auctioneer] Created the auction: \n" << (*auction);

	auctions[auctionID] = auction;
	board->setAuctionInfo(new PublicAuctionInfo(auction));

	return auctionID;
}

vector<int> Auctioneer::getAuctionIDs() {
	vector<int> auctionIDs;
	for(map<int,Auction*>::iterator it = auctions.begin(); it != auctions.end(); ++it) {
  		auctionIDs.push_back(it->first);
	}
	return auctionIDs;
}

bool Auctioneer::requestBid(int auctionID, BidPackage bidPack) {
	if (auctions.find(auctionID) == auctions.end()) {
		return false;
	}
	if (!verifyBidPackage(auctionID, bidPack)) {
		return false;
	}
	auctions[auctionID]->addBid(bidPack);
	return true;
}

bool Auctioneer::resolveAuction(int auctionID) {
	Auction *auction = auctions[auctionID];
	int bidders = auction->getBidders();

	if (bidders < 1) {
		cerr << "No bidders in auction " << auctionID <<"\n";
		return false;
	}

	vector<BidPackage> bidPacks = auction->getBidPackages();

	ZZ maxBid = bidPacks[0].bid;
	int winningIndex = 0;

	for (int i = 1; i < bidders; ++i) {
		if (bidPacks[i].bid > maxBid) {
			maxBid = bidPacks[i].bid;
			winningIndex = i;
		}
	}

	auction->close(winningIndex);
	return 1;
}

bool Auctioneer::requestProof(int auctionID, AuctionProofCommitments *&proofCommitments) {
	if (auctions.find(auctionID) == auctions.end()) {
		cout << "Auctioneer: auction not found" << endl;
		return false;
	}
	Auction *auction = auctions[auctionID];
	if (auction->getOpen()) {
		cout << "Auctioneer: auction still running" << endl;
		return false;
	}


	int bidders = auction->getBidders();
	vector<BidPackage> bidPacks = auction->getBidPackages();
	int winner = auction->getWinningIndex();

	ZZ maxBid = board->getMaxBid();
	ZZ prime = board->getPrime();

	int proofID = proofCount++;
	AuctionProof* proof = new AuctionProof(proofID);

	// First price auction

	for (int i = 0; i < auction->getSoundness(); ++i) {
		// create an SLC to prove winning index won
/*
		vector<ComparisonProof> validity;
		vector<ComparisonProof> ordering;
		for (int j = 0; j < bidders; ++j) {
			validity.push_back(ComparisonProof(bidPacks[j].bid, ZZ(0), bidPacks[j].reps[i], PairRep(ZZ(0), prime), prime, maxBid));
			if (j != winner)
				ordering.push_back(ComparisonProof(bidPacks[j].bid, bidPacks[winner].bid, bidPacks[j].reps[i], bidPacks[winner].reps[i], prime, maxBid));
		}
		proof.validityProofs.push_back(validity);
		proof.orderingProofs.push_back(ordering);

*/
		vector<ComparisonProof *> bidsInRange(bidders);
		vector<ComparisonProof *> diffsInRange(bidders);


		for (int j = 0; j < bidders; ++j) {
			PairRep rep = PairRep(ZZ(0), prime);
			PairCom repCom = PairCom(Com(rep.first), Com(rep.second));
			bidsInRange[j] = new ComparisonProof(bidPacks[j].reps[i], bidPacks[j].repSCs[i],
					rep, repCom, prime, maxBid);
			if (j != winner) {
				diffsInRange[j] = new ComparisonProof(bidPacks[winner].reps[i], bidPacks[winner].repSCs[i],
						bidPacks[j].reps[i], bidPacks[j].repSCs[i], prime, maxBid);
			} else {
				diffsInRange[j] = new ComparisonProof(true);
			}
		}

		proof->bidsInRanges.push_back(bidsInRange);
		proof->diffsInRanges.push_back(diffsInRange);
	}

	proofs[proofID] = proof;

	proofCommitments = new AuctionProofCommitments(proof);

	return true;
}

bool Auctioneer::challenge(int auctionID, int proofID, vector<int> challengeTypes,
		vector<ChallengeAddition*>& responseAdds, vector<ChallengeMultiplication*>& responseMults) {
	if (auctions.find(auctionID) == auctions.end())
		return false;
	Auction *auction = auctions[auctionID];
	if (auction->getOpen())
		return false;
	if (proofs.find(proofID) == proofs.end())
		return false;
	if ((int)challengeTypes.size() != auction->getSoundness())
		return false;
	for (int i = 0; i < (int)challengeTypes.size(); ++i)
		if (challengeTypes[i] < 1 || challengeTypes[i] > 4)
			return false;

	AuctionProof *proof = proofs[proofID];

	int winner = auction->getWinningIndex();

	responseAdds.clear();
	responseMults.clear();
	for (int i = 0; i < (int)challengeTypes.size(); ++i) {
		int type = challengeTypes[i];
		if (type == 1) {
			responseAdds.push_back(new ChallengeAddition(0, proof->bidsInRanges[i], proof->diffsInRanges[i], winner));
			responseMults.push_back(NULL);
		} else if (type == 2) {
			responseAdds.push_back(new ChallengeAddition(1, proof->bidsInRanges[i], proof->diffsInRanges[i], winner));
			responseMults.push_back(NULL);
		} else if (type == 3) {
			responseAdds.push_back(NULL);
			responseMults.push_back(new ChallengeMultiplication(0, proof->bidsInRanges[i], proof->diffsInRanges[i], winner));
		} else if (type == 4) {
			responseAdds.push_back(NULL);
			responseMults.push_back(new ChallengeMultiplication(1, proof->bidsInRanges[i], proof->diffsInRanges[i], winner));
		}
	}

	proofs.erase(proofs.find(proofID));
	return 1;
}
