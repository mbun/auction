/*
 * DSA
 *
 *  Created on: May 8, 2015
 *      Author: Mark
 */


#include "DSA.h"


// Generate parameters to be used by all signers
DSA::DSA(int L, int N) {
	assert(N <= HASH_LEN);
	this->N = N;
	
	while (true) {
		q = GenPrime_ZZ(N);
	
		ZZ X;
		ZZ c;
		for (int i = 0; i < 4 * N; i++) {
			X = RandomLen_ZZ(L);
			c = X % (2 * q);
			p = X - c + 1;
			if (NumBits(p) >= L-1 && ProbPrime(p)) {
				ZZ h = RandomBnd(p);
				ZZ e = (p - 1) / q;
				g = PowerMod(h, e, p);
				while (g % p == ZZ(1)) {
					h = RandomBnd(p);
					g = PowerMod(h, e, p);
				}
				return;
			}
		}
	}
	
}

void DSA::keyGen(ZZ& publicKey, ZZ& secretKey) {
	secretKey = RandomBnd(q-1) + 1;
	publicKey = PowerMod(g, secretKey, p);
}

static ZZ decHash(const string& message) {
	const string hexDigits = "0123456789abcdef";
	ZZ result = ZZ(0);
	string hashString = SHA256::sha256(message);
	for (int i = 0; i < hashString.length() - 1; i++) {
		result += hexDigits.find(hashString[i]);
		result <<= 4;
	}
	result += hexDigits.find(hashString[hashString.length()-1]);
	return result;
}
	
Signature DSA::sign(const ZZ& secretKey, const string& message) {
	ZZ r = ZZ(0);
	ZZ k = ZZ(0);
	ZZ s = ZZ(0);
	while (r == 0 || s == 0) {
		k = RandomBnd(q-1) + 1;
		r = PowerMod(g, k, p) % q;
		s = InvMod(k, q) * (decHash(message) + secretKey * r) % q;
	}
	return Signature(r, s);
}
	
bool DSA::verify(const ZZ& publicKey, const string& message, const Signature& sig) {
	ZZ r = sig.first;
	ZZ s = sig.second;
	if (r <= 0 || r >= q || s <= 0 || s >= q) {
		return 0;
	}
	ZZ w = InvMod(s, q);
	ZZ u1 = MulMod(decHash(message), w, q);
	ZZ u2 = MulMod(r, w, q);
	ZZ v = MulMod(PowerMod(g, u1, p), PowerMod(publicKey, u2, p), p) % q;
	return (v == r);
}

/*
int main() {
	DSA dsa = DSA(2048, 256);
	cout << dsa.p << ", " << dsa.q << ", " << dsa.g << endl;
	
	ZZ publicKey;
	ZZ secretKey;
	dsa.keyGen(publicKey, secretKey);
	cout << publicKey << ", " << secretKey << endl;
	
	Signature sig = dsa.sign(secretKey, "grapes");
	
	cout << sig.first << ", " << sig.second << endl;
	
	cout << dsa.verify(publicKey, "grapes", sig) << endl;
	
	cout << dsa.verify(publicKey, "herpderp", Signature(ZZ(12345), ZZ(678910))) << endl;
}
*/

