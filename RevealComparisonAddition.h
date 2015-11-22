/*
 * RevealComparisonAddition.h
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#ifndef REVEALCOMPARISONADDITION_H_
#define REVEALCOMPARISONADDITION_H_

#include "ComparisonProof.h"

class RevealComparisonAddition {
public:
	ComReveal Xhalf, Yhalf, Nhalf;

	ComReveal A1half, A2half, A3half, B1half, B2half, B3half, C1half, C2half, C3half, D1half, D2half, D3half;
	ComReveal ZA2half, ZA3half, ZB2half, ZB3half, ZC2half, ZC3half, ZD2half, ZD3half;

	ComReveal AAhalf, BBhalf, CChalf, DDhalf;
	ComReveal MA1half, MA2half, MA3half, MB1half, MB2half, MB3half, MC1half, MC2half, MC3half, MD1half, MD2half, MD3half;

	ComReveal W0Ahalf, W0Bhalf, W0Chalf, W0Dhalf;
	ComReveal W1Ahalf, W1Bhalf, W1Chalf, W1Dhalf;

	PairCR RA, RB, RC, RD;

	ComReveal t;
	ComReveal ta, tb, tc, td;
	ComReveal tma, tmb, tmc, tmd;
	ComReveal twa, twb, twc, twd;

	RevealComparisonAddition();
	RevealComparisonAddition(ComparisonProof *proof, int bit);

	size_t size();
};

#endif /* REVEALCOMPARISONADDITION_H_ */
