/*
 * Buyer.h
 *
 *  Created on: Apr 23, 2015
 *      Author: Tom
 */

#ifndef SELLER_H_
#define SELLER_H_

#include "Player.h"
#include "Article.h"

using namespace std;

class Seller: public Player
{
private:
    Auctioneer *auctioneer;
    vector<Article*> articles;
public:
    Seller(int i);

    int addArticle (Article *article);

	int startAuction (size_t auctioneer_index, size_t article_index, int soundness); //return auctionID
};


#endif /* SELLER_H_ */
