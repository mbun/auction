/*
 * ComparisonProofCommitments.cpp
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#include "ComparisonProofCommitments.h"

/*
ComparisonProofCommitments::ComparisonProofCommitments() {
}
*/

ComparisonProofCommitments::ComparisonProofCommitments(ComparisonProof *proof) {
	if (proof != NULL) {
	Xcom = PairSS(proof->Xcom.first.value, proof->Xcom.second.value);
	Ycom = PairSS(proof->Ycom.first.value, proof->Ycom.second.value);
	Ncom = PairSS(proof->Ncom.first.value, proof->Ncom.second.value);

	A1com = PairSS(proof->A1com.first.value, proof->A1com.second.value);
	A2com = PairSS(proof->A2com.first.value, proof->A2com.second.value);
	B1com = PairSS(proof->B1com.first.value, proof->B1com.second.value);
	B2com = PairSS(proof->B2com.first.value, proof->B2com.second.value);
	C1com = PairSS(proof->C1com.first.value, proof->C1com.second.value);
	C2com = PairSS(proof->C2com.first.value, proof->C2com.second.value);
	D1com = PairSS(proof->D1com.first.value, proof->D1com.second.value);
	D2com = PairSS(proof->D2com.first.value, proof->D2com.second.value);

	AAcom = PairSS(proof->AAcom.first.value, proof->AAcom.second.value);
	BBcom = PairSS(proof->BBcom.first.value, proof->BBcom.second.value);
	CCcom = PairSS(proof->CCcom.first.value, proof->CCcom.second.value);
	DDcom = PairSS(proof->DDcom.first.value, proof->DDcom.second.value);

	MA1com = PairSS(proof->MA1com.first.value, proof->MA1com.second.value);
	MA2com = PairSS(proof->MA2com.first.value, proof->MA2com.second.value);
	MA3com = PairSS(proof->MA3com.first.value, proof->MA3com.second.value);
	MB1com = PairSS(proof->MB1com.first.value, proof->MB1com.second.value);
	MB2com = PairSS(proof->MB2com.first.value, proof->MB2com.second.value);
	MB3com = PairSS(proof->MB3com.first.value, proof->MB3com.second.value);
	MC1com = PairSS(proof->MC1com.first.value, proof->MC1com.second.value);
	MC2com = PairSS(proof->MC2com.first.value, proof->MC2com.second.value);
	MC3com = PairSS(proof->MC3com.first.value, proof->MC3com.second.value);
	MD1com = PairSS(proof->MD1com.first.value, proof->MD1com.second.value);
	MD2com = PairSS(proof->MD2com.first.value, proof->MD2com.second.value);
	MD3com = PairSS(proof->MD3com.first.value, proof->MD3com.second.value);

	W0Acom = PairSS(proof->W0Acom.first.value, proof->W0Acom.second.value);
	W0Bcom = PairSS(proof->W0Bcom.first.value, proof->W0Bcom.second.value);
	W0Ccom = PairSS(proof->W0Ccom.first.value, proof->W0Ccom.second.value);
	W0Dcom = PairSS(proof->W0Dcom.first.value, proof->W0Dcom.second.value);

	W1Acom = PairSS(proof->W1Acom.first.value, proof->W1Acom.second.value);
	W1Bcom = PairSS(proof->W1Bcom.first.value, proof->W1Bcom.second.value);
	W1Ccom = PairSS(proof->W1Ccom.first.value, proof->W1Ccom.second.value);
	W1Dcom = PairSS(proof->W1Dcom.first.value, proof->W1Dcom.second.value);

	RAcom = PairSS(proof->RAcom.first.value, proof->RAcom.second.value);
	RBcom = PairSS(proof->RBcom.first.value, proof->RBcom.second.value);
	RCcom = PairSS(proof->RCcom.first.value, proof->RCcom.second.value);
	RDcom = PairSS(proof->RDcom.first.value, proof->RDcom.second.value);

	t_com = proof->t_com.value;

	ta_com = proof->ta_com.value;
	tb_com = proof->tb_com.value;
	tc_com = proof->tc_com.value;
	td_com = proof->td_com.value;

	tma_com = proof->tma_com.value;
	tmb_com = proof->tmb_com.value;
	tmc_com = proof->tmc_com.value;
	tmd_com = proof->tmd_com.value;

	twa_com = proof->twa_com.value;
	twb_com = proof->twb_com.value;
	twc_com = proof->twc_com.value;
	twd_com = proof->twd_com.value;
	}
}

size_t ComparisonProofCommitments::size() {
	size_t out = sizeof(ComparisonProofCommitments);

	out += Xcom.first.size() + Xcom.second.size();
	out += Ycom.first.size() + Ycom.second.size();
	out += Ncom.first.size() + Ncom.second.size();

	out += A1com.first.size() + A1com.second.size();
	out += A2com.first.size() + A2com.second.size();
	out += B1com.first.size() + B1com.second.size();
	out += B2com.first.size() + B2com.second.size();
	out += C1com.first.size() + C1com.second.size();
	out += C2com.first.size() + C2com.second.size();
	out += D1com.first.size() + D1com.second.size();
	out += D2com.first.size() + D2com.second.size();

	out += AAcom.first.size() + AAcom.second.size();
	out += BBcom.first.size() + BBcom.second.size();
	out += CCcom.first.size() + CCcom.second.size();
	out += DDcom.first.size() + DDcom.second.size();

	out += MA1com.first.size() + MA1com.second.size();
	out += MA2com.first.size() + MA2com.second.size();
	out += MA3com.first.size() + MA3com.second.size();
	out += MB1com.first.size() + MB1com.second.size();
	out += MB2com.first.size() + MB2com.second.size();
	out += MB3com.first.size() + MB3com.second.size();
	out += MC1com.first.size() + MC1com.second.size();
	out += MC2com.first.size() + MC2com.second.size();
	out += MC3com.first.size() + MC3com.second.size();
	out += MD1com.first.size() + MD1com.second.size();
	out += MD2com.first.size() + MD2com.second.size();
	out += MD3com.first.size() + MD3com.second.size();

	out += W0Acom.first.size() + W0Acom.second.size();
	out += W0Bcom.first.size() + W0Bcom.second.size();
	out += W0Ccom.first.size() + W0Ccom.second.size();
	out += W0Dcom.first.size() + W0Dcom.second.size();

	out += W1Acom.first.size() + W1Acom.second.size();
	out += W1Bcom.first.size() + W1Bcom.second.size();
	out += W1Ccom.first.size() + W1Ccom.second.size();
	out += W1Dcom.first.size() + W1Dcom.second.size();

	out += RAcom.first.size() + RAcom.second.size();
	out += RBcom.first.size() + RBcom.second.size();
	out += RCcom.first.size() + RCcom.second.size();
	out += RDcom.first.size() + RDcom.second.size();

	out += t_com.size();

	out += ta_com.size();
	out += tb_com.size();
	out += tc_com.size();
	out += td_com.size();

	out += tma_com.size();
	out += tmb_com.size();
	out += tmc_com.size();
	out += tmd_com.size();

	out += twa_com.size();
	out += twb_com.size();
	out += twc_com.size();
	out += twd_com.size();

	return out;
}
