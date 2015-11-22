/*
 * Buyer.h
 *
 *  Created on: May 8, 2015
 *      Author: Yi-Hsiu
 */

#include "Seller.h"
#include "Player.h"

Seller::Seller(int i) : Player(i) {

}

int Seller::addArticle(Article *article) {
    articles.push_back(article);
    return articles.size()-1;
}

int Seller::startAuction (size_t auctioneer_index, size_t article_index, int soundness=40) {
    cout << "Selling " << *(articles[article_index]) << " to " << *(auctioneers[auctioneer_index]) << endl;;
    return auctioneers[auctioneer_index]->requestAuction(id, articles[article_index], soundness);
}
