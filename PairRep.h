/*
 * Pair.h
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#ifndef PAIRREP_H_
#define PAIRREP_H_

#include <NTL/ZZ.h>
using namespace NTL;

class PairRep {
public:
	ZZ first, second, prime;
	PairRep(ZZ first, ZZ second, ZZ prime);
	PairRep(ZZ value, ZZ prime);
    PairRep();
    friend std::ostream& operator<<(std::ostream& os, const PairRep& pair);

	PairRep operator+(const PairRep& b);
	PairRep operator-(const PairRep& b);
	// PairRep operator%(const ZZ& m);
	// bool operator==(const PairRep& b);
	ZZ& operator[](const int index);

    static ZZ getT (PairRep X, PairRep Y); // X = Y + [t, -t]
    static void prepareZ (PairRep X, PairRep Y, PairRep &Z1, PairRep &Z2, PairRep &Z3);

    ZZ value () const;
};

#endif /* PAIRREP_H_ */
