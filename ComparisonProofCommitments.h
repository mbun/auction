/*
 * ComparisonProofCommitments.h
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#ifndef COMPARISONPROOFCOMMITMENTS_H_
#define COMPARISONPROOFCOMMITMENTS_H_

#include <utility>
using namespace std;

#include "ComparisonProof.h"

typedef pair<string,string> PairSS;

class ComparisonProofCommitments {
public:
	PairSS Xcom, Ycom, Ncom;
	PairSS A1com, A2com, B1com, B2com, C1com, C2com, D1com, D2com;
	PairSS AAcom, BBcom, CCcom, DDcom;
	PairSS MA1com, MA2com, MA3com, MB1com, MB2com, MB3com, MC1com, MC2com, MC3com, MD1com, MD2com, MD3com;
	PairSS W0Acom, W0Bcom, W0Ccom, W0Dcom;
	PairSS W1Acom, W1Bcom, W1Ccom, W1Dcom;
	PairSS RAcom, RBcom, RCcom, RDcom;

	string t_com;
	string ta_com, tb_com, tc_com, td_com;
	string tma_com, tmb_com, tmc_com, tmd_com;
	string twa_com, twb_com, twc_com, twd_com;

	//ComparisonProofCommitments();

	ComparisonProofCommitments(ComparisonProof *proof);

	size_t size();
};

#endif /* COMPARISONPROOFCOMMITMENTS_H_ */
