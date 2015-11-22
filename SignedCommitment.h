/*
 * SignedCommitment.h
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#ifndef SIGNEDCOMMITMENT_H_
#define SIGNEDCOMMITMENT_H_

#include "Commitment.h"
#include "DSA.h"

using namespace std;

class SignedCommitment: public Commitment {
public:
	DSA* dsa;
    Signature signature;
    
    bool verify(ZZ verificationKey);
    
    SignedCommitment();
	SignedCommitment(string value, Signature signature, DSA* dsa);
	SignedCommitment(ZZ messageVal, ZZ signingKey, DSA* dsa);

	size_t size();
};

#endif /* SIGNEDCOMMITMENT_H_ */
