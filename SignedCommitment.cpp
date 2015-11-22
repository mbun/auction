/*
 * SignedCommitment.cpp
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#include "SignedCommitment.h"

SignedCommitment::SignedCommitment() {
}

SignedCommitment::SignedCommitment(string value, Signature signature, DSA* dsa) {
	// Doesn't initialize ordinary commitment fields!
	this->value = value;
    this->signature = signature;
    this->dsa = dsa;
}

SignedCommitment::SignedCommitment(ZZ messageVal, ZZ signingKey, DSA* dsa) : Commitment(messageVal) {
	this->dsa = dsa;
	signature = dsa->sign(signingKey, value);
}

bool SignedCommitment::verify(ZZ verificationKey) {
    return dsa->verify(verificationKey, value, signature);
}

size_t SignedCommitment::size() {
	return sizeof(SignedCommitment) + signature.first.size() + signature.second.size() + value.size() + message.size() + opening.size();
}


/*
int main() {
    DSA dsa;
    ZZ signingKey;
    ZZ publicKey;
    dsa.keyGen(publicKey, signingKey);
    
    SignedCommitment sc(ZZ(1234), signingKey, &dsa);
    
    cout << sc.verify(publicKey) << endl;
}
*/
