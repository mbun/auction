/*
 * PublicKeyInfrastructure
 *
 *  Created on: May 8, 2015
 *      Author: Mark
 */


#include "PublicKeyInfrastructure.h"

ZZ PublicKeyInfrastructure::keyGen(int playerID) {
	ZZ publicKey, secretKey;
	dsa.keyGen(publicKey, secretKey);
	keyMap[playerID] = publicKey;
	return secretKey;
}

Signature PublicKeyInfrastructure::sign(const ZZ& secretKey, const string& message) {
	return dsa.sign(secretKey, message);
}
	
bool PublicKeyInfrastructure::verify(int playerID, const string& message, const Signature& sig) {
	if (keyMap.count(playerID) == 0) {
		cerr << "Public key for player " << playerID << " not found" << endl;
		return 0;
	}
	return dsa.verify(keyMap[playerID], message, sig);
}


/*
int main() {
	PublicKeyInfrastructure pki = PublicKeyInfrastructure();
	ZZ sk1 = pki.keyGen(1);
	Signature sig1 = pki.sign(sk1, "message1");
	cout << pki.verify(1, "message1", sig1) << endl;
	
	ZZ sk2 = pki.keyGen(2);
	Signature sig2 = pki.sign(sk2, "message2");
	cout << pki.verify(2, "message2", sig2) << endl;
	
	cout << pki.verify(2, "message2", sig1) << endl;
}
*/
