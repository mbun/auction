/*
 * PublicBoard.h
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#ifndef PUBLICBOARD_H_
#define PUBLICBOARD_H_

#include <map>
using namespace std;

#include <NTL/ZZ.h>
using namespace NTL;

#include "Auction.h"

class PublicBoard {
private:
	map<int,ZZ> publicKeys;
	map<int,PublicAuctionInfo*> auctionInfos;
	DSA* dsa;
	ZZ prime;
	ZZ maxBid;
public:
	PublicBoard(ZZ prime, ZZ maxBid);

	void setPublicKey(int playerID, ZZ publicKey);

	ZZ getPublicKey(int playerID);

	void setAuctionInfo(PublicAuctionInfo* auctionInfo);

	PublicAuctionInfo* getAuctionInfo(int auctionID);

	vector<int> getAuctionIDs;

	ZZ getPrime();

	ZZ getMaxBid();
	
	DSA* getDSA();

};

#endif /* PUBLICBOARD_H_ */
