/*
 * Player.h
 *
 *  Created on: Apr 23, 2015
 *      Author: Tom
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "PublicBoard.h"
#include <vector>
#include "Auctioneer.h"
#include "ComparisonProofCommitments.h"
#include "RevealComparisonAddition.h"
#include "RevealComparisonMultiplication.h"
using namespace std;


class Player
{
private:
	bool checkAdditions(ComparisonProofCommitments* commits, RevealComparisonAddition *reveal, int& bit);
	bool checkMultiplications(RevealComparisonMultiplication *reveal, int& bit);
protected:
    vector<Auctioneer*> auctioneers;
    ZZ signingKey;
public:
	PublicBoard* board;
    void assignPublicBoard(PublicBoard *pb);

	int id;

    Player(int i);

    int addAuctioneer(Auctioneer* auctioneer);

	bool verifyAuction(Auctioneer* auctioneer, int auctionID); //returns success/fail

	bool verifyAuction(Auctioneer* auctioneer, int auctionID, size_t& communication); //returns success/fail
};


#endif /* PLAYER_H_ */
