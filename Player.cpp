/*
 * Buyer.h
 *
 *  Created on: May 8, 2015
 *      Author: Yi-Hsiu
 */

#include <ctime>

#include "Player.h"
#include "Challenge.h"
#include "ChallengeAddition.h"
#include "ChallengeMultiplication.h"
#include "AuctionProofCommitments.h"
#include "Macros.h"

#define FlipT(t, bit, p) (bit == 0 ? (t) : ((p) - (t)))

Player::Player(int i) : id(i) {
}

void Player::assignPublicBoard(PublicBoard *pb) {
    board = pb;
    ZZ verificationKey;
    pb->getDSA()->keyGen(verificationKey, signingKey);
    SignedCommitment bidSC(ZZ(123), signingKey, pb->getDSA());
    pb->setPublicKey(id, verificationKey);
}

int Player::addAuctioneer (Auctioneer *auctioneer) {
    auctioneers.push_back(auctioneer);
    return auctioneers.size()-1;
}

bool Player::verifyAuction (Auctioneer* auctioneer, int auctionID) {
	size_t throwAway;
	return verifyAuction(auctioneer, auctionID, throwAway);
}

bool Player::verifyAuction (Auctioneer* auctioneer, int auctionID, size_t& communication) {
	double start = clock();
	
	communication = 0;
	AuctionProofCommitments *proofCommitments;
	if (!auctioneer->requestProof(auctionID, proofCommitments)) {
		cout << "Failed to get proof" << endl;
		return false;
	}
	
	double end = clock();
	cout << "Proof Preparation Time (CPU): " << (double)(end - start)/CLOCKS_PER_SEC << " secs\n";
	
	start = clock();

	communication += proofCommitments->size();

	PublicAuctionInfo* auctionInfo = board->getAuctionInfo(auctionID);
	int soundness = auctionInfo->getSoundness();
	int bidders = auctionInfo->getBidders();

	communication += auctionInfo->getBidPackagesSize();

	vector<int> challengeTypes;
	for (int i = 0; i < soundness; ++i)
		challengeTypes.push_back(RandomBnd(4)+1);

	vector<ChallengeAddition*> challengeAdds;
	vector<ChallengeMultiplication*> challengeMults;
	if (!auctioneer->challenge(auctionID, proofCommitments->proofID, challengeTypes, challengeAdds, challengeMults)) {
		cout << "Failed to get challenge" << endl;
		return false;
	}
//	cout << "got challenge" << endl;

	if ((int)challengeAdds.size() != soundness || (int)challengeMults.size() != soundness) {
		cout << "Challenge response is wrong size" << endl;
		return false;
	}

	int winningIndex = auctionInfo->getWinningIndex();
	vector<BidderInfo> bidderInfos = auctionInfo->getBidderInfos();
	ZZ prime = board->getPrime();
	DSA* dsa = board->getDSA();

	for (int i = 0; i < soundness; ++i) {
		int type = challengeTypes[i];

		if (type == 1 || type == 2) {
			int bit = type - 1;
			ChallengeAddition* challenge = challengeAdds[i];
			if (challenge == NULL) {
				cout << "Challenge response is wrong type" << endl;
				return false;
			}
			communication += challenge->size();

			vector<ComparisonProofCommitments *> bidsInRangeComs = proofCommitments->bidsInRangeComs[i];
			vector<RevealComparisonAddition *> bidsInRangeReveals = challenge->validityReveals;

			for (int j = 0; j < bidders; ++j) {
				if (!checkAdditions(bidsInRangeComs[j], bidsInRangeReveals[j], bit)) {
					cout << "Bid in range additions check failed" << endl;
					return false;
				}
			}

			//check bidder commitments against these halves and check signing halves
			for (int j = 0; j < bidders; ++j) {
				if (PairIndex(bidderInfos[j].repComs[i], bit) != PairIndex(bidsInRangeComs[j]->Xcom, bit)) {
					cout << "Bid representation in proof not the same as posted by bidder" << endl;
					return 0;
				}

				if (!dsa->verify(board->getPublicKey(bidderInfos[j].playerID),
						PairIndex(bidderInfos[j].repComs[i], bit), PairIndex(bidderInfos[j].repSigs[i], bit))) {
					cout << "Bid signing verification failed" << endl;
					return 0;
				}
			}

			vector<ComparisonProofCommitments *> diffsInRangeComs = proofCommitments->diffsInRangeComs[i];
			vector<RevealComparisonAddition *> diffsInRangeReveals = challenge->orderingReveals;

			for (int j = 0; j < bidders; ++j) {
				if (j == winningIndex)
					continue;
//				cout << "MEEEP " << j << endl;
				if (!checkAdditions(diffsInRangeComs[j], diffsInRangeReveals[j], bit)) {
					cout << "Diffs in range additions check failed" << endl;
					return false;
				}
			}

//			for (int j = 0; j < bidders; ++j) {
//				if (j == winningIndex)
//					continue;
//				if (type == 1) {
//					//check n[j].first + x[j].first = x[winning].first + t[j].first
//				} else if (type == 2) {
//					//check n[j].second + x[j].second = x[winning].second - t[j].second
//				}
//			}

			//check accordance between ordering and validity inputs (includes checking winner)
			for (int j = 0; j < bidders; ++j) {
				if (j == winningIndex)
					continue;
				if (diffsInRangeReveals[j]->Xhalf.message != bidsInRangeReveals[winningIndex]->Xhalf.message) {
					cout << "Diffs in range not checking winner" << endl;
					return 0;
				}
				if (diffsInRangeReveals[j]->Yhalf.message != bidsInRangeReveals[j]->Xhalf.message) {
					cout << "Diffs in range not checking against right loser" << endl;
					return 0;
				}
			}
		}
		else if (type == 3 || type == 4) {
			int bit = type - 3;
			ChallengeMultiplication* challenge = challengeMults[i];
			if (challenge == NULL) {
				cout << "Challenge response is wrong type" << endl;
				return 0;
			}
			communication += challenge->size();

			vector<RevealComparisonMultiplication *> validityReveals = challenge->validityReveals;

			for (int j = 0; j < bidders; ++j) {
				if (!checkMultiplications(validityReveals[j], bit)) {
					cout << "Bids in range multiplication check failed" << endl;
					return 0;
				}
			}

			vector<RevealComparisonMultiplication *> orderingReveals = challenge->orderingReveals;

			for (int j = 0; j < bidders; ++j) {
				if (j == winningIndex)
					continue;
				if (!checkMultiplications(orderingReveals[j], bit)) {
					cout << "Diffs in range multiplication check failed" << endl;
					return 0;
				}
			}

			// check that the ys are zero for the validity proofs
			for (int j = 0; j < bidders; ++j) {
				if ((validityReveals[j]->Y.first.message + validityReveals[j]->Y.second.message) % prime != ZZ(0)) {
					cout << "Bids in range not using a real zero" << endl;
					return 0;
				}
			}
		}
	}
	end = clock();
	cout << "Proof Verification Time (CPU): " << (double)(end - start)/CLOCKS_PER_SEC << " secs\n";
    return 1;
}

bool Player::checkAdditions (ComparisonProofCommitments* commits, RevealComparisonAddition* reveal, int& bit) {
	ZZ prime = board->getPrime();
	ZZ maxBid = board->getMaxBid();

//	cout << "a" << endl;

	//check commitments of all halves
	if (!SHACommit::checkReveal(reveal->Xhalf.message, PairIndex(commits->Xcom, bit), reveal->Xhalf.opening))
		return 0;
//	cout << "a1" << endl;
	if (!SHACommit::checkReveal(reveal->Yhalf.message, PairIndex(commits->Ycom, bit), reveal->Yhalf.opening))
		return 0;
//	cout << "a2" << endl;
	if (!SHACommit::checkReveal(reveal->Nhalf.message, PairIndex(commits->Ncom, bit), reveal->Nhalf.opening))
		return 0;

//	cout << "b" << endl;

	if (!SHACommit::checkReveal(reveal->A1half.message, PairIndex(commits->A1com, bit), reveal->A1half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->A2half.message, PairIndex(commits->A2com, bit), reveal->A2half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->B1half.message, PairIndex(commits->B1com, bit), reveal->B1half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->B2half.message, PairIndex(commits->B2com, bit), reveal->B2half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->C1half.message, PairIndex(commits->C1com, bit), reveal->C1half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->C2half.message, PairIndex(commits->C2com, bit), reveal->C2half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->D1half.message, PairIndex(commits->D1com, bit), reveal->D1half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->D2half.message, PairIndex(commits->D2com, bit), reveal->D2half.opening))
		return 0;

//	cout << "c" << endl;

	if (!SHACommit::checkReveal(reveal->AAhalf.message, PairIndex(commits->AAcom, bit), reveal->AAhalf.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->BBhalf.message, PairIndex(commits->BBcom, bit), reveal->BBhalf.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->CChalf.message, PairIndex(commits->CCcom, bit), reveal->CChalf.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->DDhalf.message, PairIndex(commits->DDcom, bit), reveal->DDhalf.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->MA1half.message, PairIndex(commits->MA1com, bit), reveal->MA1half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->MA2half.message, PairIndex(commits->MA2com, bit), reveal->MA2half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->MA3half.message, PairIndex(commits->MA3com, bit), reveal->MA3half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->MB1half.message, PairIndex(commits->MB1com, bit), reveal->MB1half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->MB2half.message, PairIndex(commits->MB2com, bit), reveal->MB2half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->MB3half.message, PairIndex(commits->MB3com, bit), reveal->MB3half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->MC1half.message, PairIndex(commits->MC1com, bit), reveal->MC1half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->MC2half.message, PairIndex(commits->MC2com, bit), reveal->MC2half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->MC3half.message, PairIndex(commits->MC3com, bit), reveal->MC3half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->MD1half.message, PairIndex(commits->MD1com, bit), reveal->MD1half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->MD2half.message, PairIndex(commits->MD2com, bit), reveal->MD2half.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->MD3half.message, PairIndex(commits->MD3com, bit), reveal->MD3half.opening))
		return 0;

//	cout << "d" << endl;

	if (!SHACommit::checkReveal(reveal->W0Ahalf.message, PairIndex(commits->W0Acom, bit), reveal->W0Ahalf.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->W0Bhalf.message, PairIndex(commits->W0Bcom, bit), reveal->W0Bhalf.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->W0Chalf.message, PairIndex(commits->W0Ccom, bit), reveal->W0Chalf.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->W0Dhalf.message, PairIndex(commits->W0Dcom, bit), reveal->W0Dhalf.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->W1Ahalf.message, PairIndex(commits->W1Acom, bit), reveal->W1Ahalf.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->W1Bhalf.message, PairIndex(commits->W1Bcom, bit), reveal->W1Bhalf.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->W1Chalf.message, PairIndex(commits->W1Ccom, bit), reveal->W1Chalf.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->W1Dhalf.message, PairIndex(commits->W1Dcom, bit), reveal->W1Dhalf.opening))
		return 0;

//	cout << "e" << endl;

	if (!SHACommit::checkReveal(reveal->RA.first.message, commits->RAcom.first, reveal->RA.first.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->RA.second.message, commits->RAcom.second, reveal->RA.second.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->RB.first.message, commits->RBcom.first, reveal->RB.first.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->RB.second.message, commits->RBcom.second, reveal->RB.second.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->RC.first.message, commits->RCcom.first, reveal->RC.first.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->RC.second.message, commits->RCcom.second, reveal->RC.second.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->RD.first.message, commits->RDcom.first, reveal->RD.first.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->RD.second.message, commits->RDcom.second, reveal->RD.second.opening))
		return 0;

//	cout << "f" << endl;

	//check commitments to all ts
	if (!SHACommit::checkReveal(reveal->t.message, commits->t_com, reveal->t.opening))
		return 0;

	if (!SHACommit::checkReveal(reveal->ta.message, commits->ta_com, reveal->ta.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->tb.message, commits->tb_com, reveal->tb.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->tc.message, commits->tc_com, reveal->tc.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->td.message, commits->td_com, reveal->td.opening))
		return 0;

	if (!SHACommit::checkReveal(reveal->tma.message, commits->tma_com, reveal->tma.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->tmb.message, commits->tmb_com, reveal->tmb.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->tmc.message, commits->tmc_com, reveal->tmc.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->tmd.message, commits->tmd_com, reveal->tmd.opening))
		return 0;

	if (!SHACommit::checkReveal(reveal->twa.message, commits->twa_com, reveal->twa.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->twb.message, commits->twb_com, reveal->twb.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->twc.message, commits->twc_com, reveal->twc.opening))
		return 0;
	if (!SHACommit::checkReveal(reveal->twd.message, commits->twd_com, reveal->twd.opening))
		return 0;

//	cout << "g" << endl;

//	cout << reveal->Xhalf.message << " - " << reveal->Yhalf.message << " = " << reveal->Nhalf.message << endl;

	//check additions
	//n = x-y
	if ((prime + reveal->Xhalf.message - reveal->Yhalf.message) % prime != reveal->Nhalf.message)
		return 0;

//	cout << "g1" << endl;

	//n = a^2 + b^2 + c^2 + d^2
	if ((reveal->AAhalf.message + reveal->BBhalf.message + reveal->CChalf.message +
			reveal->DDhalf.message + FlipT(reveal->t.message, bit, prime)) % prime != reveal->Nhalf.message)
		return 0;

//	cout << "g2" << endl;

//	cout << reveal->A2half.message << " " << FlipT(reveal->ta.message, bit, prime) << " " << reveal->A1half.message;

	if ((reveal->A2half.message + FlipT(reveal->ta.message, bit, prime)) % prime != reveal->A1half.message)
		return 0;
//	cout << "g2a" << endl;
	if ((reveal->B2half.message + FlipT(reveal->tb.message, bit, prime)) % prime != reveal->B1half.message)
		return 0;
	if ((reveal->C2half.message + FlipT(reveal->tc.message, bit, prime)) % prime != reveal->C1half.message)
		return 0;
	if ((reveal->D2half.message + FlipT(reveal->td.message, bit, prime)) % prime != reveal->D1half.message)
		return 0;

//	cout << "g3" << endl;

	if ((reveal->MA1half.message + reveal->MA2half.message +
			reveal->MA3half.message + FlipT(reveal->tma.message, bit, prime)) % prime != reveal->AAhalf.message)
		return 0;
	if ((reveal->MB1half.message + reveal->MB2half.message +
			reveal->MB3half.message + FlipT(reveal->tmb.message, bit, prime)) % prime != reveal->BBhalf.message)
		return 0;
	if ((reveal->MC1half.message + reveal->MC2half.message +
			reveal->MC3half.message + FlipT(reveal->tmc.message, bit, prime)) % prime != reveal->CChalf.message)
		return 0;
	if ((reveal->MD1half.message + reveal->MD2half.message +
			reveal->MD3half.message + FlipT(reveal->tmd.message, bit, prime)) % prime != reveal->DDhalf.message)
		return 0;

//	cout << "h" << endl;

	//check relevant piece of multiplication
	if ((reveal->A1half.message * reveal->A2half.message) % prime != reveal->MA1half.message)
		return 0;
	if ((reveal->B1half.message * reveal->B2half.message) % prime != reveal->MB1half.message)
		return 0;
	if ((reveal->C1half.message * reveal->C2half.message) % prime != reveal->MC1half.message)
		return 0;
	if ((reveal->D1half.message * reveal->D2half.message) % prime != reveal->MD1half.message)
		return 0;

	//check Rs
	if ((reveal->RA.first.message + reveal->RA.second.message) % prime > maxBid)
		return 0;
	if ((reveal->RB.first.message + reveal->RB.second.message) % prime > maxBid)
		return 0;
	if ((reveal->RC.first.message + reveal->RC.second.message) % prime > maxBid)
		return 0;
	if ((reveal->RD.first.message + reveal->RD.second.message) % prime > maxBid)
		return 0;

//	cout << "i" << endl;

	if ((PairIndex(reveal->RA, bit).message !=
				(reveal->W0Ahalf.message + reveal->A1half.message + FlipT(reveal->twa.message, bit, prime)) % prime) &&
			(PairIndex(reveal->RA, bit).message !=
				(reveal->W1Ahalf.message + reveal->A1half.message + FlipT(reveal->twa.message, bit, prime)) % prime))
		return 0;
//	cout << "i1" << endl;
	if ((PairIndex(reveal->RB, bit).message !=
				(reveal->W0Bhalf.message + reveal->B1half.message + FlipT(reveal->twb.message, bit, prime)) % prime) &&
			(PairIndex(reveal->RB, bit).message !=
				(reveal->W1Bhalf.message + reveal->B1half.message + FlipT(reveal->twb.message, bit, prime)) % prime))
		return 0;
//	cout << "i2" << endl;
	if ((PairIndex(reveal->RC, bit).message !=
				(reveal->W0Chalf.message + reveal->C1half.message + FlipT(reveal->twc.message, bit, prime)) % prime) &&
			(PairIndex(reveal->RC, bit).message !=
				(reveal->W1Chalf.message + reveal->C1half.message + FlipT(reveal->twc.message, bit, prime)) % prime))
		return 0;
//	cout << "i3" << endl;
	if ((PairIndex(reveal->RD, bit).message !=
				(reveal->W0Dhalf.message + reveal->D1half.message + FlipT(reveal->twd.message, bit, prime)) % prime) &&
			(PairIndex(reveal->RD, bit).message !=
				(reveal->W1Dhalf.message + reveal->D1half.message + FlipT(reveal->twd.message, bit, prime)) % prime))
		return 0;

//	cout << "j" << endl;

	return 1;
}

bool Player::checkMultiplications(RevealComparisonMultiplication *reveal, int& bit) {
	ZZ prime = board->getPrime();
	ZZ maxBid = board->getMaxBid();

//	cout << bit << endl;

//	cout << "a" << endl;

	//check mults
	if ((reveal->A.first.message * reveal->A.second.message) % prime != (reveal->MA.first.message + reveal->MA.second.message) % prime)
		return 0;
	if ((reveal->B.first.message * reveal->B.second.message) % prime != (reveal->MB.first.message + reveal->MB.second.message) % prime)
		return 0;
	if ((reveal->C.first.message * reveal->C.second.message) % prime != (reveal->MC.first.message + reveal->MC.second.message) % prime)
		return 0;
	if ((reveal->D.first.message * reveal->D.second.message) % prime != (reveal->MD.first.message + reveal->MD.second.message) % prime)
		return 0;

//	cout << "b" << endl;


	//check W0s and W1s in range and W0-W1=maxBid
	if ((reveal->W0A.first.message + reveal->W0A.second.message) % prime > maxBid)
		return 0;
	if ((reveal->W0B.first.message + reveal->W0B.second.message) % prime > maxBid)
		return 0;
	if ((reveal->W0C.first.message + reveal->W0C.second.message) % prime > maxBid)
		return 0;
	if ((reveal->W0D.first.message + reveal->W0D.second.message) % prime > maxBid)
		return 0;

//	cout << "c" << endl;


	if ((reveal->W1A.first.message + reveal->W1A.second.message) % prime < prime-maxBid)
		return 0;
	if ((reveal->W1B.first.message + reveal->W1B.second.message) % prime < prime-maxBid)
		return 0;
	if ((reveal->W1C.first.message + reveal->W1C.second.message) % prime < prime-maxBid)
		return 0;
	if ((reveal->W1D.first.message + reveal->W1D.second.message) % prime < prime-maxBid)
		return 0;

//	cout << "d" << endl;


	if ((2*prime + reveal->W0A.first.message + reveal->W0A.second.message - (reveal->W1A.first.message + reveal->W1A.second.message)) % prime != maxBid)
		return 0;
	if ((2*prime + reveal->W0B.first.message + reveal->W0B.second.message - (reveal->W1B.first.message + reveal->W1B.second.message)) % prime != maxBid)
		return 0;
	if ((2*prime + reveal->W0C.first.message + reveal->W0C.second.message - (reveal->W1C.first.message + reveal->W1C.second.message)) % prime != maxBid)
		return 0;
	if ((2*prime + reveal->W0D.first.message + reveal->W0D.second.message - (reveal->W1D.first.message + reveal->W1D.second.message)) % prime != maxBid)
		return 0;

//	cout << "e" << endl;


	return 1;
}
