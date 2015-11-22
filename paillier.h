/*
 * Paillier
 *
 *  Created on: May 4, 2015
 *      Author: Mark
 */

#ifndef PAILLIER_H_
#define PAILLIER_H_

#include <vector>
#include <iostream>

using namespace NTL;
using namespace std;

class Paillier
{
public:

	static void keyGen(ZZ& publicKey, ZZ& secretKey, long keySize);
	
	static ZZ enc(ZZ publicKey, ZZ message);
	
	static void enc(ZZ publicKey, ZZ message, ZZ& ciphertext, ZZ& randomness);
	
	static void encAux(ZZ publicKey, ZZ message, ZZ& ciphertext, ZZ& randomness, ZZ& randomnessPow);
	
	static ZZ com(ZZ publicKey, ZZ message, ZZ help);
	
	static ZZ dec(ZZ publicKey, ZZ secretKey, ZZ ciphertext);

};


#endif /* PAILLIER_H_ */
