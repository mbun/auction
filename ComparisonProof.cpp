/*
 * ComparisonProof.cpp
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#include "ComparisonProof.h"

ComparisonProof::ComparisonProof(bool b) { // No diffInRange to be prove for winner
}

ComparisonProof::ComparisonProof(PairRep X, PairCom Xcom, PairRep Y, PairCom Ycom, ZZ p, ZZ maxBid) {
	// We need x > y
	//this->x = x;
	//this->y = y;
	//this->X = X;
	//this->Y = Y;

	this->X = X;
	this->Y = Y;
	x = X.value();
	y = Y.value();

	N = X - Y;
	n = N.value();

	NTAlgorithm::FourSquare(n, a, b, c, d);
	aa = a * a;
	bb = b * b;
	cc = c * c;
	dd = d * d;


	AA = PairRep(aa, p);
	BB = PairRep(bb, p);
	CC = PairRep(cc, p);
	DD = PairRep(dd, p);
	
	t = PairRep::getT(N, AA+BB+CC+DD);


	A1 = PairRep(a, p); A2 = PairRep(a, p);
	B1 = PairRep(b, p); B2 = PairRep(b, p);
	C1 = PairRep(c, p); C2 = PairRep(c, p);
	D1 = PairRep(d, p); D2 = PairRep(d, p);

	ta = PairRep::getT(A1, A2);
	tb = PairRep::getT(B1, B2);
	tc = PairRep::getT(C1, C2);
	td = PairRep::getT(D1, D2);

	PairRep::prepareZ(A1, A2, MA1, MA2, MA3);
	PairRep::prepareZ(B1, B2, MB1, MB2, MB3);
	PairRep::prepareZ(C1, C2, MC1, MC2, MC3);
	PairRep::prepareZ(D1, D2, MD1, MD2, MD3);
	tma = PairRep::getT(AA, MA1 + MA2 + MA3);
	tmb = PairRep::getT(BB, MB1 + MB2 + MB3);
	tmc = PairRep::getT(CC, MC1 + MC2 + MC3);
	tmd = PairRep::getT(DD, MD1 + MD2 + MD3);


	w0a = RandomBnd(maxBid+1);
	w0b = RandomBnd(maxBid+1);
	w0c = RandomBnd(maxBid+1);
	w0d = RandomBnd(maxBid+1);
	W0A = PairRep(w0a, p);
	W0B = PairRep(w0b, p);
	W0C = PairRep(w0c, p);
	W0D = PairRep(w0d, p);

	w1a = (p+w0a-maxBid) % p;
	w1b = (p+w0b-maxBid) % p;
	w1c = (p+w0c-maxBid) % p;
	w1d = (p+w0d-maxBid) % p;
	W1A = PairRep(w1a, p);
	W1B = PairRep(w1b, p);
	W1C = PairRep(w1c, p);
	W1D = PairRep(w1d, p);

	ra = (w0a + a) % maxBid;
	rb = (w0b + b) % maxBid;
	rc = (w0c + c) % maxBid;
	rd = (w0d + d) % maxBid;
	RA = PairRep(ra, p);
	RB = PairRep(rb, p);
	RC = PairRep(rc, p);
	RD = PairRep(rd, p);

	if (ra == w0a + a) {
		twa = PairRep::getT(RA, A1 + W0A);
	} else {
		twa = PairRep::getT(RA, A1 + W1A);
	}
	if (rb == w0b + b) {
		twb = PairRep::getT(RB, B1 + W0B);
	} else {
		twb = PairRep::getT(RB, B1 + W1B);
	}
	if (rc == w0c + c) {
		twc = PairRep::getT(RC, C1 + W0C);
	} else {
		twc = PairRep::getT(RC, C1 + W1C);
	}
	if (rd == w0d + d) {
		twd = PairRep::getT(RD, D1 + W0D);
	} else {
		twd = PairRep::getT(RD, D1 + W1D);
	}
/*
	if ((w0a + a) % p <= maxBid) {
		ra = (w0a + a) % p;
		RA = (W0A + A3) % p;
	}
	else {
		ra = (w1a + a) % p;
		RA = (W1A + A3) % p;
	}
	if ((w0b + b) % p <= maxBid) {
		rb = (w0b + b) % p;
		RB = (W0B + B3) % p;
	}
	else {
		rb = (w1b + b) % p;
		RB = (W1B + B3) % p;
	}
	if ((w0c + c) % p <= maxBid) {
		rc = (w0c + c) % p;
		RC = (W0C + C3) % p;
	}
	else {
		rc = (w1c + c) % p;
		RC = (W1C + C3) % p;
	}
	if ((w0d + d) % p <= maxBid) {
		rd = (w0d + d) % p;
		RD = (W0D + D3) % p;
	}
	else {
		rd = (w1d + d) % p;
		RD = (W1D + D3) % p;
	}
*/

	//Commitments:
	this->Xcom = Xcom;
	this->Ycom = Ycom;
	//Xcom = PairCom(Com(X[0]),Com(X[1]));
	//Ycom = PairCom(Com(Y[0]),Com(Y[1]));
	Ncom = PairCom(Com(N[0]),Com(N[1]));

	AAcom = PairCom(Com(AA[0]), Com(AA[1]));
	BBcom = PairCom(Com(BB[0]), Com(BB[1]));
	CCcom = PairCom(Com(CC[0]), Com(CC[1]));
	DDcom = PairCom(Com(DD[0]), Com(DD[1]));
    t_com = Com(t);

	A1com = PairCom(Com(A1[0]), Com(A1[1]));
	A2com = PairCom(Com(A2[0]), Com(A2[1]));
	B1com = PairCom(Com(B1[0]), Com(B1[1]));
	B2com = PairCom(Com(B2[0]), Com(B2[1]));
	C1com = PairCom(Com(C1[0]), Com(C1[1]));
	C2com = PairCom(Com(C2[0]), Com(C2[1]));
	D1com = PairCom(Com(D1[0]), Com(D1[1]));
	D2com = PairCom(Com(D2[0]), Com(D2[1]));
    ta_com = Com(ta);
    tb_com = Com(tb);
    tc_com = Com(tc);
    td_com = Com(td);

	MA1com = PairCom(Com(MA1[0]), Com(MA1[1]));
	MA2com = PairCom(Com(MA2[0]), Com(MA2[1]));
	MA3com = PairCom(Com(MA3[0]), Com(MA3[1]));
	MB1com = PairCom(Com(MB1[0]), Com(MB1[1]));
	MB2com = PairCom(Com(MB2[0]), Com(MB2[1]));
	MB3com = PairCom(Com(MB3[0]), Com(MB3[1]));
	MC1com = PairCom(Com(MC1[0]), Com(MC1[1]));
	MC2com = PairCom(Com(MC2[0]), Com(MC2[1]));
	MC3com = PairCom(Com(MC3[0]), Com(MC3[1]));
	MD1com = PairCom(Com(MD1[0]), Com(MD1[1]));
	MD2com = PairCom(Com(MD2[0]), Com(MD2[1]));
	MD3com = PairCom(Com(MD3[0]), Com(MD3[1]));
    tma_com = Com(tma);
    tmb_com = Com(tmb);
    tmc_com = Com(tmc);
    tmd_com = Com(tmd);

	W0Acom = PairCom(Com(W0A[0]), Com(W0A[1]));
	W0Bcom = PairCom(Com(W0B[0]), Com(W0B[1]));
	W0Ccom = PairCom(Com(W0C[0]), Com(W0C[1]));
	W0Dcom = PairCom(Com(W0D[0]), Com(W0D[1]));

	W1Acom = PairCom(Com(W1A[0]), Com(W1A[1]));
	W1Bcom = PairCom(Com(W1B[0]), Com(W1B[1]));
	W1Ccom = PairCom(Com(W1C[0]), Com(W1C[1]));
	W1Dcom = PairCom(Com(W1D[0]), Com(W1D[1]));

	RAcom = PairCom(Com(RA[0]), Com(RA[1]));
	RBcom = PairCom(Com(RB[0]), Com(RB[1]));
	RCcom = PairCom(Com(RC[0]), Com(RC[1]));
	RDcom = PairCom(Com(RD[0]), Com(RD[1]));
    twa_com = Com(twa);
    twb_com = Com(twb);
    twc_com = Com(twc);
    twd_com = Com(twd);
}
