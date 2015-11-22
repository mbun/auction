/*
 * PublicBoard.cpp
 *
 *  Created on: May 8, 2015
 *      Author: Yi-Hsiu
 */


#include "PublicBoard.h"

PublicBoard::PublicBoard(ZZ prime, ZZ maxBid) {
    this->prime = prime;
    this->maxBid = maxBid;
    dsa = new DSA(); // Use default length
}

void PublicBoard::setAuctionInfo(PublicAuctionInfo *auctionInfo) {
    auctionInfos[auctionInfo->getAuctionID()] = auctionInfo;
}

PublicAuctionInfo* PublicBoard::getAuctionInfo(int auctionID) {
    return auctionInfos[auctionID];
}

ZZ PublicBoard::getPublicKey(int playerID) {
    if (publicKeys.count(playerID) == 0) {
		cerr << "Public key for player " << playerID << " not found" << endl;
		return ZZ(-1);
	}
	return publicKeys[playerID];
}

void PublicBoard::setPublicKey(int playerID, ZZ publicKey) {
	publicKeys[playerID] = publicKey;
}

ZZ PublicBoard::getPrime() {
    return prime;
}

ZZ PublicBoard::getMaxBid() {
    return maxBid;
}

DSA* PublicBoard::getDSA() {
	return dsa;
}
