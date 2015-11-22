/*
 * AuctionProofCommitments.cpp
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#include "AuctionProofCommitments.h"
/*
AuctionProofCommitments::AuctionProofCommitments() {

}
*/
AuctionProofCommitments::AuctionProofCommitments(AuctionProof *proof) {
	this->proofID = proof->proofID;
	for (int i = 0; i < (int)proof->bidsInRanges.size(); ++i) {
		vector<ComparisonProofCommitments *> bidsInRangeCom;
		for (int j = 0; j < (int)proof->bidsInRanges[i].size(); ++j)
			bidsInRangeCom.push_back(new ComparisonProofCommitments(proof->bidsInRanges[i][j]));
		bidsInRangeComs.push_back(bidsInRangeCom);

		vector<ComparisonProofCommitments *> diffsInRangeCom;
		for (int j = 0; j < (int)proof->diffsInRanges[i].size(); ++j) {
			diffsInRangeCom.push_back(new ComparisonProofCommitments(proof->diffsInRanges[i][j]));
		}
		diffsInRangeComs.push_back(diffsInRangeCom);
		
//		vector<string> tCom;
//		for (int j = 0; j < (int)proof.tcomsValues[i].size(); ++j)
//			tCom.push_back(proof.tcomsValues[i][j].value);
//		tComs.push_back(tCom);
	}
}

size_t AuctionProofCommitments::size() {
	size_t out = sizeof(AuctionProofCommitments);

	for (int i = 0; i < (int)bidsInRangeComs.size(); ++i)
		for (int j = 0; j < (int)bidsInRangeComs[i].size(); ++j)
			out += bidsInRangeComs[i][j]->size();

	for (int i = 0; i < (int)diffsInRangeComs.size(); ++i)
		for (int j = 0; j < (int)diffsInRangeComs[i].size(); ++j)
			out += diffsInRangeComs[i][j]->size();

	return out;
}

