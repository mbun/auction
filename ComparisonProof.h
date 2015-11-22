/*
 * ComparisonProof.h
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#ifndef COMPARISONPROOF_H_
#define COMPARISONPROOF_H_

#include <utility>
#include <NTL/ZZ.h>
using namespace NTL;
using namespace std;

#include "PairRep.h"
#include "NTAlgorithm.h"
#include "Commitment.h"
#include "ComReveal.h"

typedef pair<ComReveal,ComReveal> PairCR;
typedef pair<Commitment,Commitment> PairCom;
typedef Commitment Com;

class ComparisonProof {
private:
	ZZ x, y, n;
	PairRep X, Y, N;

	ZZ aa, bb, cc, dd; //aa = a^2
	PairRep AA, BB, CC, DD; //pair reps of above
	ZZ t; // used to prove N = AA + BB + CC + DD

	ZZ a, b, c, d; // a^2 + b^2 + c^2 + d^2 = n
	PairRep A1, A2, B1, B2, C1, C2, D1, D2; // remember to prove that A1 = A2
	ZZ ta, tb, tc, td; // used to prove A1 = A2

	PairRep MA1, MA2, MA3, MB1, MB2, MB3, MC1, MC2, MC3, MD1, MD2, MD3; // used to prove A1*A2 = AA
	ZZ tma, tmb, tmc, tmd; // used to prove AA = MA1 + MA2 + MA3

	ZZ w0a, w0b, w0c, w0d; //w0a in [0,maxBid], used to prove -maxBid<=a<=2*maxBid
	PairRep W0A, W0B, W0C, W0D; //pair reps of above

	ZZ w1a, w1b, w1c, w1d; //w1a = w0a - maxBid
	PairRep W1A, W1B, W1C, W1D; //pair reps of above

	ZZ ra, rb, rc, rd; //ra is either w0a+a or w1a+a, whichever is in [0,maxBid]
	PairRep RA, RB, RC, RD; //pair reps of above

	ZZ twa, twb, twc, twd; // used to prove RA = WiA + A1

public:
	PairCom Xcom, Ycom, Ncom; //commitments to X, Y and N

	PairCom AAcom, BBcom, CCcom, DDcom;
	Com t_com;

	PairCom A1com, A2com, B1com, B2com, C1com, C2com, D1com, D2com;
	Com ta_com, tb_com, tc_com, td_com;

	PairCom MA1com, MA2com, MA3com, MB1com, MB2com, MB3com, MC1com, MC2com, MC3com, MD1com, MD2com, MD3com;
	Com tma_com, tmb_com, tmc_com, tmd_com;

	PairCom W0Acom, W0Bcom, W0Ccom, W0Dcom;
	PairCom W1Acom, W1Bcom, W1Ccom, W1Dcom;
	PairCom RAcom, RBcom, RCcom, RDcom;
	Com twa_com, twb_com, twc_com, twd_com;

	ComparisonProof(bool b);
	ComparisonProof(PairRep X, PairCom Xcom, PairRep Y, PairCom Ycom, ZZ p, ZZ maxBid);
};

#endif /* COMPARISONPROOF_H_ */
