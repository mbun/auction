#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
using namespace NTL;

#include "paillier.h"

#define PRICE_LIMIT 1000000
#define N_BUYERS 10
#define KEY_SIZE 2048
#define SOUNDNESS 10    // # of repetitions

typedef vector<ZZ> TestSet;

struct OpenedTest {
	ZZ ciphertext;
	ZZ plaintext;
	ZZ randomness;
	ZZ randomnessPow;
	
	OpenedTest(ZZ c, ZZ p, ZZ r, ZZ rP) :
		ciphertext(c), plaintext(p), randomness(r), randomnessPow(rP) {}
};

typedef vector<OpenedTest> OpenedTestSet;


struct RangeProof {
	vector<ZZ> ciphertexts;
	ZZ help;
	
	RangeProof(vector<ZZ> c, ZZ h): ciphertexts(c), help(h) {}
};


bool verifyTestSet(TestSet* testSet, OpenedTestSet* openedTestSet) {
	int t = NumBits(PRICE_LIMIT) + 1;
	int numZeroes = 0;
	vector<bool> hitList(t);
	
	for (int i = 0; i < openedTestSet->size(); i++) {
		OpenedTest* opened = &((*openedTestSet)[i]);
		ZZ ciphertext = (*testSet)[i];
		if (opened->ciphertext != ciphertext) {
			return 0;
		}
		ZZ plaintext = opened->plaintext;
		if (plaintext == 0) {
			numZeroes++;
			continue;
		}
		if (weight(plaintext) != 1) { //plaintext not a power of 2
			return 0;
		}
		hitList[NumBits(plaintext) - 1] = 1;
	}
	
	if (numZeroes != t) {
		return 0;
	}
	
	for (int i = 0; i < t; i++) {
		if (!hitList[i]) {
			return 0;
		}
	}
	return 1;
}


// Prove that ciphertext is an encryption of something < 2^t
RangeProof prove(ZZ publicKey, ZZ plaintext, ZZ ciphertext, ZZ randomness, OpenedTestSet* testSet) {
	set<int> hotBits;
	for (int i = 0; i < NumBits(plaintext); i++) {
		if (bit(plaintext, i) == 1) {
			hotBits.insert(i);
		}
	}
	int l = hotBits.size();
	int zeroesNeeded =  NumBits(PRICE_LIMIT) + 1 - l;
	
	vector<ZZ> ciphertexts;
	vector<ZZ> openings;
	for (int i = 0; i < testSet->size(); i++) {
		OpenedTest test = (*testSet)[i];
		if (hotBits.count(NumBits(test.plaintext) - 1) == 1) {
			ciphertexts.push_back(test.ciphertext);
			openings.push_back(test.randomness);
		} else if (zeroesNeeded > 0 && test.plaintext == ZZ(0)) {
			ciphertexts.push_back(test.ciphertext);
			openings.push_back(test.randomness);
			zeroesNeeded--;
		}
	}
	ZZ help = InvMod(randomness, publicKey);
	for (int i = 0; i < openings.size(); i++) {
		MulMod(help, help, openings[i], publicKey);
	}
	return RangeProof(ciphertexts, help);
}

bool verifyProof(ZZ publicKey, RangeProof proof, ZZ ciphertext, TestSet* testSet) {
	vector<ZZ>* ciphertexts = &proof.ciphertexts;
	ZZ help = proof.help;
	for (int i = 0; i < ciphertexts->size(); i++) {
		if (count(testSet->begin(), testSet->end(), (*ciphertexts)[i]) == 0) {
			cerr << "TEST SET MISMATCH" << endl;
			return 0;
		}
	}
	ZZ modulus = publicKey * publicKey;
	ZZ check = InvMod(ciphertext, modulus);
	for (int i = 0; i < ciphertexts->size(); i++) {
		MulMod(check, check, (*ciphertexts)[i], modulus);
	}
	return check == Paillier::com(publicKey, ZZ(0), help);
}




int main(int argc, char *argv[]) {

	double genStart = 0;
	double genEnd = 0;
	double verStart = 0;
	double verEnd = 0;
	
	
	// Sample crypto parameters
	
	ZZ publicKey;
	ZZ secretKey;
	
	Paillier::keyGen(publicKey, secretKey, KEY_SIZE);
	
	ZZ modulus = publicKey * publicKey;
	
	ZZ helpRecovery = InvMod(publicKey % secretKey, secretKey);
	
	srand ( unsigned ( time(0) ) );


	int numTestSets = 25; // Should be 2500, but that will take forever
	
	vector<int> permutation;
	for (int i = 0; i < numTestSets; i++) {
		permutation.push_back(i);
	}
	random_shuffle(permutation.begin(), permutation.end());



	// Generate test sets

	int t = NumBits(PRICE_LIMIT) + 1;
	vector<TestSet*> testSets;
	vector<OpenedTestSet*> openedTestSets;
	
	genStart += clock();
	
	for (int i = 0; i < numTestSets; i++) {
		OpenedTestSet* nextOpenedTestSet = new OpenedTestSet();
		
		// Add t encryptions of 0
		for (int i = 0; i < t; i++) {
			ZZ ciphertext, randomness, randomnessPow;
			Paillier::encAux(publicKey, ZZ(0), ciphertext, randomness, randomnessPow);
			OpenedTest nextOpenedTest(ciphertext, ZZ(0), randomness, randomnessPow);
			nextOpenedTestSet->push_back(nextOpenedTest);
		}
		
		// Add encryptions of 2^0, ..., 2^{t-1}
		for (int i = 0; i < t; i++) {
			ZZ plaintext = power2_ZZ(i);
			ZZ ciphertext, randomness, randomnessPow;
			Paillier::encAux(publicKey, plaintext, ciphertext, randomness, randomnessPow);
			OpenedTest nextOpenedTest(ciphertext, plaintext, randomness, randomnessPow);
			nextOpenedTestSet->push_back(nextOpenedTest);
		}
		
		random_shuffle(nextOpenedTestSet->begin(), nextOpenedTestSet->end());
		
		TestSet* nextTestSet = new TestSet();
		for (OpenedTestSet::iterator it = nextOpenedTestSet->begin() ; it != nextOpenedTestSet->end(); ++it) {
			nextTestSet->push_back(it->ciphertext);
		}
		
		testSets.push_back(nextTestSet);
		openedTestSets.push_back(nextOpenedTestSet);
	}
	
	genEnd += clock();



	// Reveal and verify test sets
	
	verStart += clock();

	int revealed = 5; // Should be 500
	int testSetIndex = 0;
	for (; testSetIndex < revealed; testSetIndex++) {
		int nextIndex = permutation[testSetIndex];
		if (!verifyTestSet(testSets[nextIndex], openedTestSets[nextIndex])) {
			cerr << "TEST SET " << testSetIndex << " FAILED TO VERIFY!!!" << endl;
		}
	}
	
	verEnd += clock();


	// Sample and publish bids
	vector<int> bids;
	int winner = 0;
	int winningBid = 0;
	for(int i = 0; i < N_BUYERS; i++) {
		int nextBid = RandomBnd(PRICE_LIMIT);
		if (nextBid > winningBid) {
			winner = i;
			winningBid = nextBid;
		}
		bids.push_back(nextBid);
	}
	
	vector<ZZ> commitments;
	vector<ZZ> openings;
	
	for(int i = 0; i < N_BUYERS; i++) {
		ZZ ciphertext;
		ZZ randomness;
		Paillier::enc(publicKey, ZZ(bids[i]), ciphertext, randomness);
		commitments.push_back(ciphertext);
		openings.push_back(randomness);
	}
	
	
	
	
	// Check encryptions
	
	for(int i = 0; i < N_BUYERS; i++) {
		if (Paillier::com(publicKey, ZZ(bids[i]), openings[i]) != commitments[i]) {
			cerr << "BID " << i << " FAILED TO VERIFY!!!" << endl;
		}
	}
	
	cout << "WINNER IS BIDDER #" << winner << " WITH BID " << winningBid << endl;
	
	
	for(int i = 0; i < N_BUYERS; i++) {
	
		// Generate and check proof that bids[i] < 2^t
		
		genStart += clock();
		
		RangeProof nextProof = 
			prove(publicKey, ZZ(bids[i]), commitments[i], openings[i], openedTestSets[permutation[testSetIndex]]);
			
		genEnd += clock();
		
		verStart += clock();
			
		if (!verifyProof(publicKey, nextProof, commitments[i], testSets[permutation[testSetIndex]])) {
			cerr << "PROOF THAT BID " << i << " IN RANGE FAILED TO VERIFY!!!" << endl;
		} else {
			cout << "VERIFIED BID " << i << " IN RANGE" << endl;
		}
		
		verEnd += clock();
			
		testSetIndex++;	
		
		
		if (i != winner) {
		
		// Generate and check proof that bids[i] <= winningBid
		
			ZZ ciphertext = MulMod(commitments[winner], InvMod(commitments[i], modulus), modulus);
			
			ZZ help = PowerMod(ciphertext % publicKey, helpRecovery, publicKey);
			
			genStart += clock();
		
			RangeProof nextProof = 
				prove(	publicKey,
						ZZ(winningBid - bids[i]),
						ciphertext,
						help,
						openedTestSets[permutation[testSetIndex]]);
						
			genEnd += clock();
						
			verStart += clock();
			if (!verifyProof(publicKey, nextProof, ciphertext, testSets[permutation[testSetIndex]])) {
				cerr << "PROOF THAT BID " << i << " LOSES FAILED TO VERIFY!!!" << endl;
			} else {
				cout << "VERIFIED BID " << i << " LOSES" << endl;
			}
			verEnd+= clock();
			testSetIndex++;	
			
		}
		
	cout << "Proof preparation time: " << 1.0 * (genEnd-genStart) / CLOCKS_PER_SEC << endl;
	cout << "Proof verification time: " << 1.0 * (verEnd-verStart) / CLOCKS_PER_SEC << endl;


	
	}

}
