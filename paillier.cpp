/*
 * Paillier.cpp
 *
 *  Created on: May 4, 2015
 *      Author: Mark
 */

#include <NTL/ZZ.h>
#include "paillier.h"


void Paillier::keyGen(ZZ& publicKey, ZZ& secretKey, long keySize) {
	ZZ p = GenPrime_ZZ(keySize);
	ZZ q = GenPrime_ZZ(keySize);
	publicKey=p*q;
	secretKey=(p-1)*(q-1);
}

ZZ Paillier::enc(ZZ publicKey, ZZ message) {
	message = message % publicKey;
	ZZ r;
	while (GCD(r, publicKey) != 1) {
		r = RandomBnd(publicKey);
	}
	ZZ modulus = publicKey * publicKey;
	ZZ result = PowerMod(r, publicKey, modulus);
	result *= (1 + message * publicKey);
	return result % modulus;
}

void Paillier::enc(ZZ publicKey, ZZ message, ZZ& ciphertext, ZZ& randomness) {
	message = message % publicKey;
	randomness = ZZ(0);
	while (GCD(randomness, publicKey) != 1) {
		randomness = RandomBnd(publicKey);
	}
	ZZ modulus = publicKey * publicKey;
	ZZ result = PowerMod(randomness, publicKey, modulus);
	result *= (1 + message * publicKey);
	ciphertext = result % modulus;
}

void Paillier::encAux(ZZ publicKey, ZZ message, ZZ& ciphertext, ZZ& randomness, ZZ& randomnessPow) {
	message = message % publicKey;
	randomness = ZZ(0);
	while (GCD(randomness, publicKey) != 1) {
		randomness = RandomBnd(publicKey);
	}
	ZZ modulus = publicKey * publicKey;
	randomnessPow = PowerMod(randomness, publicKey, modulus);
	ciphertext = MulMod((1 + message * publicKey), randomnessPow, modulus);
}

ZZ Paillier::com(ZZ publicKey, ZZ message, ZZ help) {
	message = message % publicKey;
	ZZ modulus = publicKey * publicKey;
	ZZ result = PowerMod(help, publicKey, modulus);
	result *= (1 + message * publicKey);
	return result % modulus;
}

ZZ Paillier::dec(ZZ publicKey, ZZ secretKey, ZZ ciphertext) {
	ZZ modulus = publicKey * publicKey;
	ZZ message = PowerMod(ciphertext, secretKey, modulus);
	message = (message - 1) * InvMod(secretKey, modulus);
	message /= publicKey;
	return message % publicKey;
}

/*

int main()
{
   ZZ pk;
   ZZ sk;
   keyGen(pk, sk, 100);
   cout << pk << ", " << sk << endl;
   ZZ ciphertext = enc(pk, conv<ZZ>("1234567891011121314151617181920"));
   cout << ciphertext << endl;
   cout << dec(pk, sk, ciphertext) << endl;
}

*/
