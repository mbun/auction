#include <iostream>
#include <string>
using namespace std;

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
using namespace NTL;

#include "NTAlgorithm.h"

#include "Player.h"
#include "Seller.h"
#include "Buyer.h"
#include "Auctioneer.h"
#include "PublicBoard.h"

#define PRICE_LIMIT 100000
#define N_BUYERS 100
#define SOUNDNESS 10

void test_four_square(int bitLength=160, int times=500);

int main(int argc, char *argv[]) {
    //test_four_square();

    int playerCounter = 1;
    ZZ prime = NextPrime(conv<ZZ>(64) * PRICE_LIMIT * PRICE_LIMIT, PRICE_LIMIT);
    cout << "prime = " << prime << "\n";
    PublicBoard *board = new PublicBoard(prime, ZZ(PRICE_LIMIT));

    Seller *seller = new Seller(playerCounter++);

    Auctioneer *auctioneer = new Auctioneer(ZZ(PRICE_LIMIT));
    auctioneer->assignPublicBoard(board);

    seller->addAuctioneer(auctioneer);
    seller->addArticle(new Article("pencil"));
    seller->startAuction(0, 0, SOUNDNESS);

    int auctionID = auctioneer->getAuctionIDs()[0];

    Buyer *buyers[N_BUYERS];
    for (int i = 0; i < N_BUYERS; i++) {
        ZZ bid = RandomBnd(conv<ZZ>(PRICE_LIMIT));
        cout << "Buyer #" << playerCounter << " is placing bid $" << bid
                << " for auction #" << auctionID;
        buyers[i] = new Buyer(playerCounter++);
        buyers[i]->addAuctioneer(auctioneer);
        buyers[i]->assignPublicBoard(board);
        if (buyers[i]->placeBid(0, auctionID, bid)) {
            cout << " .... SUCCESS in placing bid.\n";
        } else {
            cout << " .... FAIL in placing bid\n";
        }
    }
    cout << flush;

    auctioneer->resolveAuction(auctionID);
    cout << "Auction Resolved\n";

    size_t communication;
    if (buyers[0]->verifyAuction(auctioneer, auctionID, communication))
        cout << "SUCCESS in verifying auction with " << communication << " bytes of communication.\n";
    else
    	cout << "FAIL in verifying auction.\n";
    return 0;
}

void test_four_square(int bitLength, int times) {
    cerr << "=== Four Square Algorithm Testing ===\n";
    cerr << "bit length: " << bitLength << "; repeat times: " << times << endl;
    ZZ n;
    ZZ x, y, z, w;
    for (int i = 0; i < times; i++) {
        RandomBits(n, bitLength);
        NTAlgorithm::FourSquare(n, x, y, z, w); 
        if (n != x*x + y*y + z*z + w*w) {
            cerr << "WRONG ANSWER!! n = " << n << "\n";
            cerr << "(x, y, z, w) = (" << x;
            cerr << ", " << y ;
            cerr << ", " << z ;
            cerr << ", " << w << ")\t";
            cerr << "sum of square: " << x*x + y*y + z*z + w*w << endl;
        }

        if ((i+1) % 10 == 0) {
            cout << "\r" << i+1 << "/" << times << " PASS" << flush;
        }
    }
    cout << endl;
}
