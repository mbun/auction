/*
 * SHACommit.cpp
 *
 *  Created on: May 6, 2015
 *      Author: Mark
 */

#include <sstream>
#include "SHACommit.h"

using namespace std;

void SHACommit::commit(const string& message, string& commitment, string& opening) {
	opening.resize(SHACommit::OPENING_LEN);
	for (int i = 0; i < SHACommit::OPENING_LEN; i++) {
		opening[i] = RandomBnd(256) - 128;
	}
	commitment = SHA256::sha256(opening + message);
}

void SHACommit::commit(const ZZ& messageValue, string& commitment, string& opening) {
	stringstream buffer;
	buffer << messageValue;
	string message = buffer.str();
	commit(message, commitment, opening);
}

bool SHACommit::checkReveal(const string& message, const string& commitment, const string& opening) {
	return (commitment.compare(SHA256::sha256(opening + message)) == 0);
}

bool SHACommit::checkReveal(const ZZ& messageValue, const string& commitment, const string& opening) {
	stringstream buffer;
	buffer << messageValue;
	string message = buffer.str();
	return checkReveal(message, commitment, opening);
}




/*
int main()
{
	string message = "onions";
	string commitment;
	string opening;
	
    commit(message, commitment, opening);
    
    
    cout << message << ", " << commitment << ", " << opening << endl;
    
    cout << checkReveal(message, commitment, opening) << endl;
    cout << checkReveal("garbage", "more garbage", "most garbage") << endl;
    
    return 0;
}
*/

