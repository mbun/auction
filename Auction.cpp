/*
 * Auctioneer.cpp
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#include "Auction.h"

Auction::Auction(int id, int soundness, int seller_id, Article *article) {
    this->id = id;
	this->soundness = soundness;
    this->seller_id = seller_id;
    this->article = article;
	this->open = true;
    this->bidders = 0;
}

ostream& operator<<(ostream& os, const Auction& auction) {
    os << "====== Auction ======\n" << "article: " << *(auction.article)
            << "\nseller: #" << auction.seller_id
            << "\nsecure parameter: " << auction.soundness
            << "\nbidders: " << auction.bidders
            << "\n" << "=====================" << "\n";
    return os;
}

void Auction::addBid(BidPackage bid) {
    bidPacks.push_back(bid);
    bidders += 1;
}

void Auction::close(int winningIndex) {
    open = false;
    this->winningIndex = winningIndex;
}

int Auction::getSoundness() {
    return soundness;
}

int Auction::getID() {
    return id;
}

int Auction::getSellerID() {
    return seller_id;
}

bool Auction::getOpen() {
    return open;
}

int Auction::getBidders() {
    return bidders;
}

vector<BidPackage> Auction::getBidPackages() {
    return bidPacks;
}

int Auction::getWinningIndex() {
    return winningIndex;
}

size_t Auction::getBidPackagesSize() {
	size_t out = 0;
	for (int i = 0; i < bidders; ++i)
		out += bidPacks[i].size();

	return out;
}
