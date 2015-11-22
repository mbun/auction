/*
 * PublicKeyInfrastructure
 *
 *  Created on: May 8, 2015
 *      Author: Mark
 */

#ifndef PUBLIC_KEY_INFRASTRUCTURE_H_
#define PUBLIC_KEY_INFRASTRUCTURE_H_

#include <iostream>
#include <string>
#include <NTL/ZZ.h>
#include <map>
#include "DSA.h"

using namespace std;
using namespace NTL;

class PublicKeyInfrastructure
{
public:
	
	PublicKeyInfrastructure() : dsa(PKI_L, PKI_N) {}

	map<int, ZZ> keyMap;
	DSA dsa;
	
	// adds <playerID, publicKey> to keyMap and returns secretKey
	ZZ keyGen(int playerID);
	
	Signature sign(const ZZ& secretKey, const string& message);
	
	bool verify(int playerID, const string& message, const Signature& sig);

};


#endif /* PUBLIC_KEY_INFRASTRUCTURE_H_ */