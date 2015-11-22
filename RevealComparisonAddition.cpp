/*
 * RevealComparisonAddition.cpp
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#include "RevealComparisonAddition.h"
#include "Macros.h"

RevealComparisonAddition::RevealComparisonAddition() {}

RevealComparisonAddition::RevealComparisonAddition(ComparisonProof *proof, int bit) {
	Xhalf = ComReveal(PairIndex(proof->Xcom, bit));
	Yhalf = ComReveal(PairIndex(proof->Ycom, bit));
	Nhalf = ComReveal(PairIndex(proof->Ncom, bit));

	A1half = ComReveal(PairIndex(proof->A1com, bit));
	A2half = ComReveal(PairIndex(proof->A2com, bit));
	B1half = ComReveal(PairIndex(proof->B1com, bit));
	B2half = ComReveal(PairIndex(proof->B2com, bit));
	C1half = ComReveal(PairIndex(proof->C1com, bit));
	C2half = ComReveal(PairIndex(proof->C2com, bit));
	D1half = ComReveal(PairIndex(proof->D1com, bit));
	D2half = ComReveal(PairIndex(proof->D2com, bit));

	AAhalf = ComReveal(PairIndex(proof->AAcom, bit));
	BBhalf = ComReveal(PairIndex(proof->BBcom, bit));
	CChalf = ComReveal(PairIndex(proof->CCcom, bit));
	DDhalf = ComReveal(PairIndex(proof->DDcom, bit));

	MA1half = ComReveal(PairIndex(proof->MA1com, bit));
	MA2half = ComReveal(PairIndex(proof->MA2com, bit));
	MA3half = ComReveal(PairIndex(proof->MA3com, bit));
	MB1half = ComReveal(PairIndex(proof->MB1com, bit));
	MB2half = ComReveal(PairIndex(proof->MB2com, bit));
	MB3half = ComReveal(PairIndex(proof->MB3com, bit));
	MC1half = ComReveal(PairIndex(proof->MC1com, bit));
	MC2half = ComReveal(PairIndex(proof->MC2com, bit));
	MC3half = ComReveal(PairIndex(proof->MC3com, bit));
	MD1half = ComReveal(PairIndex(proof->MD1com, bit));
	MD2half = ComReveal(PairIndex(proof->MD2com, bit));
	MD3half = ComReveal(PairIndex(proof->MD3com, bit));

	W0Ahalf = ComReveal(PairIndex(proof->W0Acom, bit));
	W0Bhalf = ComReveal(PairIndex(proof->W0Bcom, bit));
	W0Chalf = ComReveal(PairIndex(proof->W0Ccom, bit));
	W0Dhalf = ComReveal(PairIndex(proof->W0Dcom, bit));

	W1Ahalf = ComReveal(PairIndex(proof->W1Acom, bit));
	W1Bhalf = ComReveal(PairIndex(proof->W1Bcom, bit));
	W1Chalf = ComReveal(PairIndex(proof->W1Ccom, bit));
	W1Dhalf = ComReveal(PairIndex(proof->W1Dcom, bit));

	RA = PairCR(ComReveal(proof->RAcom.first), ComReveal(proof->RAcom.second));
	RB = PairCR(ComReveal(proof->RBcom.first), ComReveal(proof->RBcom.second));
	RC = PairCR(ComReveal(proof->RCcom.first), ComReveal(proof->RCcom.second));
	RD = PairCR(ComReveal(proof->RDcom.first), ComReveal(proof->RDcom.second));

	t = ComReveal(proof->t_com);

	ta = ComReveal(proof->ta_com);
	tb = ComReveal(proof->tb_com);
	tc = ComReveal(proof->tc_com);
	td = ComReveal(proof->td_com);

	tma = ComReveal(proof->tma_com);
	tmb = ComReveal(proof->tmb_com);
	tmc = ComReveal(proof->tmc_com);
	tmd = ComReveal(proof->tmd_com);

	twa = ComReveal(proof->twa_com);
	twb = ComReveal(proof->twb_com);
	twc = ComReveal(proof->twc_com);
	twd = ComReveal(proof->twd_com);
}

size_t RevealComparisonAddition::size() {
	size_t out = sizeof(RevealComparisonAddition);

	out += Xhalf.size();
	out += Yhalf.size();
	out += Nhalf.size();

	out += A1half.size();
	out += A2half.size();
	out += A3half.size();
	out += B1half.size();
	out += B2half.size();
	out += B3half.size();
	out += C1half.size();
	out += C2half.size();
	out += C3half.size();
	out += D1half.size();
	out += D2half.size();
	out += D3half.size();

	out += ZA2half.size();
	out += ZA3half.size();
	out += ZB2half.size();
	out += ZB3half.size();
	out += ZC2half.size();
	out += ZC3half.size();
	out += ZD2half.size();
	out += ZD3half.size();

	out += AAhalf.size();
	out += BBhalf.size();
	out += CChalf.size();
	out += DDhalf.size();

	out += MA1half.size();
	out += MA2half.size();
	out += MA3half.size();
	out += MB1half.size();
	out += MB2half.size();
	out += MB3half.size();
	out += MC1half.size();
	out += MC2half.size();
	out += MC3half.size();
	out += MD1half.size();
	out += MD2half.size();
	out += MD3half.size();

	out += W0Ahalf.size();
	out += W0Bhalf.size();
	out += W0Chalf.size();
	out += W0Dhalf.size();

	out += W1Ahalf.size();
	out += W1Bhalf.size();
	out += W1Chalf.size();
	out += W1Dhalf.size();

	out += RA.first.size() + RA.second.size();
	out += RB.first.size() + RB.second.size();
	out += RC.first.size() + RC.second.size();
	out += RD.first.size() + RD.second.size();

	out += t.size();

	out += ta.size();
	out += tb.size();
	out += tc.size();
	out += td.size();

	out += tma.size();
	out += tmb.size();
	out += tmc.size();
	out += tmd.size();

	out += twa.size();
	out += twb.size();
	out += twc.size();
	out += twd.size();

	return out;
}
