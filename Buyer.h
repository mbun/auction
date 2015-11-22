/*
 * Buyer.h
 *
 *  Created on: Apr 23, 2015
 *      Author: Tom
 */

#ifndef BUYER_H_
#define BUYER_H_

#include "Player.h"
#include "Auctioneer.h"
#include "DSA.h"

class Buyer: public Player
{
public:
    Buyer(int i);

	bool placeBid (size_t auctioneer_index, int auctionID, ZZ amount); //return success/fail
};


#endif /* BUYER_H_ */
