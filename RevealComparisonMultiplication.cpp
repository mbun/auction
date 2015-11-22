/*
 * RevealComparisonMultiplication.cpp
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#include "RevealComparisonMultiplication.h"
#include "Macros.h"

RevealComparisonMultiplication::RevealComparisonMultiplication() {}

RevealComparisonMultiplication::RevealComparisonMultiplication(ComparisonProof *proof, int bit, bool revealY) {
	if (revealY)
		Y = PairCR(ComReveal(proof->Ycom.first), ComReveal(proof->Ycom.second));

	A = PairCR(ComReveal(PairIndex(proof->A1com, bit)), ComReveal(PairIndex(proof->A2com, bit ^ 1)));
	B = PairCR(ComReveal(PairIndex(proof->B1com, bit)), ComReveal(PairIndex(proof->B2com, bit ^ 1)));
	C = PairCR(ComReveal(PairIndex(proof->C1com, bit)), ComReveal(PairIndex(proof->C2com, bit ^ 1)));
	D = PairCR(ComReveal(PairIndex(proof->D1com, bit)), ComReveal(PairIndex(proof->D2com, bit ^ 1)));

	if (bit == 0) {
		MA = PairCR(ComReveal(proof->MA2com.first), ComReveal(proof->MA2com.second));
		MB = PairCR(ComReveal(proof->MB2com.first), ComReveal(proof->MB2com.second));
		MC = PairCR(ComReveal(proof->MC2com.first), ComReveal(proof->MC2com.second));
		MD = PairCR(ComReveal(proof->MD2com.first), ComReveal(proof->MD2com.second));
	}
	else {
		MA = PairCR(ComReveal(proof->MA3com.first), ComReveal(proof->MA3com.second));
		MB = PairCR(ComReveal(proof->MB3com.first), ComReveal(proof->MB3com.second));
		MC = PairCR(ComReveal(proof->MC3com.first), ComReveal(proof->MC3com.second));
		MD = PairCR(ComReveal(proof->MD3com.first), ComReveal(proof->MD3com.second));
	}

	W0A = PairCR(ComReveal(proof->W0Acom.first), ComReveal(proof->W0Acom.second));
	W0B = PairCR(ComReveal(proof->W0Bcom.first), ComReveal(proof->W0Bcom.second));
	W0C = PairCR(ComReveal(proof->W0Ccom.first), ComReveal(proof->W0Ccom.second));
	W0D = PairCR(ComReveal(proof->W0Dcom.first), ComReveal(proof->W0Dcom.second));
	W1A = PairCR(ComReveal(proof->W1Acom.first), ComReveal(proof->W1Acom.second));
	W1B = PairCR(ComReveal(proof->W1Bcom.first), ComReveal(proof->W1Bcom.second));
	W1C = PairCR(ComReveal(proof->W1Ccom.first), ComReveal(proof->W1Ccom.second));
	W1D = PairCR(ComReveal(proof->W1Dcom.first), ComReveal(proof->W1Dcom.second));
}

size_t RevealComparisonMultiplication::size() {
	size_t out = sizeof(RevealComparisonMultiplication);

	out += Y.first.size() + Y.second.size();

	out += A.first.size() + A.second.size();
	out += B.first.size() + B.second.size();
	out += C.first.size() + C.second.size();
	out += D.first.size() + D.second.size();

	out += MA.first.size() + MA.second.size();
	out += MB.first.size() + MB.second.size();
	out += MC.first.size() + MC.second.size();
	out += MD.first.size() + MD.second.size();

	out += W0A.first.size() + W0A.second.size();
	out += W0B.first.size() + W0B.second.size();
	out += W0C.first.size() + W0C.second.size();
	out += W0D.first.size() + W0D.second.size();

	out += W1A.first.size() + W1A.second.size();
	out += W1B.first.size() + W1B.second.size();
	out += W1C.first.size() + W1C.second.size();
	out += W1D.first.size() + W1D.second.size();

	return out;
}
