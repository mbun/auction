/*
 * DSA
 *
 *  Created on: May 8, 2015
 *      Author: Mark
 */

#ifndef DSA_H_
#define DSA_H_

#include <iostream>
#include <string>
#include <NTL/ZZ.h>
#include <assert.h>
#include "sha256.h"

using namespace std;
using namespace NTL;

typedef pair<ZZ, ZZ> Signature;

class DSA
{
public:

	static const int HASH_LEN = 256;
	static const int DEFAULT_L = 2048;
	static const int DEFAULT_N = 224;
	
	ZZ p, q, g, N;

	//FIPS 186-3 specifies L and N length pairs of (1024,160), (2048,224), (2048,256), and (3072,256)
	DSA(int L = DEFAULT_L, int N = DEFAULT_N);
	
	void keyGen(ZZ& publicKey, ZZ& secretKey);
	Signature sign(const ZZ& secretKey, const string& message);
	bool verify(const ZZ& publicKey, const string& message, const Signature& sig);

};


#endif /* DSA_H_ */
