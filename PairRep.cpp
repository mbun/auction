/*
 * Pair.cpp
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#include <cassert>
#include "PairRep.h"

PairRep::PairRep(ZZ first, ZZ second, ZZ prime) {
	this->first = first;
	this->second = second;
	this->prime = prime;
}

PairRep::PairRep (ZZ value, ZZ prime) {
	ZZ r = RandomBnd(prime);
	if (value >= r) {
		this->first = value - r;
	} else {
		this->first = prime + value - r;
	}
	this->second = r;
	this->prime = prime;
}

PairRep::PairRep () {
}

std::ostream& operator<<(std::ostream& os, const PairRep& pair) {
    os << pair.value() << " = (" << pair.first << ", " << pair.second << ")";
    return os;
}

PairRep PairRep::operator+(const PairRep& b) {
	return PairRep((first+b.first) % prime, (second+b.second) % prime, prime);
}

PairRep PairRep::operator-(const PairRep& b) {
	return PairRep((prime+first-b.first) % prime, (prime+second-b.second) % prime, prime);
}

/*
PairRep PairRep::operator%(const ZZ& m) {
	return PairRep(first % m, second % m);
}
*/

/*
bool PairRep::operator==(const PairRep& b) {
	return (first == b.first) && (second == b.second);
}
*/

ZZ& PairRep::operator[](const int index) {
	assert(index >= 0 && index <= 1);

	if (index == 0)
		return first;
	else
		return second;
}

ZZ PairRep::getT (PairRep X, PairRep Y) {
	return (X.prime + X.first - Y.first) % X.prime;
}

void PairRep::prepareZ (PairRep X, PairRep Y, PairRep &Z1, PairRep &Z2, PairRep &Z3) {
	ZZ p = X.prime;
	Z1 = PairRep((X.first * Y.first) % p, (X.second * Y.second) % p, p);
	Z2 = PairRep((X.first * Y.second) % p, p);
	Z3 = PairRep((X.second * Y.first) % p, p);
}

ZZ PairRep::value () const {
	ZZ sum = first + second;
	if (sum < prime) {
		return sum;
	} else {
		return sum - prime;
	}
}
