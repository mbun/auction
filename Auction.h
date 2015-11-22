/*
 * Auction.h
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#ifndef AUCTION_H_
#define AUCTION_H_

#include <vector>
#include "BidPackage.h"
#include "Article.h"
#include "BidderInfo.h"
using namespace std;

class Auction {
private:
	int soundness;
	int id;
	int seller_id;
	Article* article;
	bool open;
	int bidders;
	int winningIndex;
	vector<BidPackage> bidPacks;
public:
	Auction(int id, int soundness, int seller_id, Article *article);
	friend ostream& operator<<(ostream& os, const Auction& auction);

	void addBid(BidPackage bid);

	void close(int winningIndex);

	int getSoundness();

	int getID();

	int getSellerID();

	bool getOpen();

	int getBidders();

	vector<BidPackage> getBidPackages();

	int getWinningIndex();

	size_t getBidPackagesSize();

};

class PublicAuctionInfo {
private:
	Auction *auction;
public:
	PublicAuctionInfo(Auction *auction) {
		this->auction = auction;
	}

	int getAuctionID() {
		return auction->getID();
	}

	int getSoundness() {
		return auction->getSoundness();
	}

	int getSellerID() {
		return auction->getSellerID();
	}

	bool auctionFinished() {
		return !auction->getOpen();
	}

	int getBidders() {
		return auction->getBidders();
	}

	int getWinningIndex() {
		return auction->getWinningIndex();
	}

	vector<BidderInfo> getBidderInfos() {
		vector<BidPackage> bidpacks = auction->getBidPackages();
		vector<BidderInfo> info;
		for (int i = 0; i < (int)bidpacks.size(); ++i)
			info.push_back(BidderInfo(bidpacks[i]));

		return info;
	}

	size_t getBidPackagesSize() {
		return auction->getBidPackagesSize();
	}
};

#endif /* AUCTION_H_ */
