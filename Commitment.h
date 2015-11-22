/*
 * Commitment.h
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#ifndef COMMITMENT_H_
#define COMMITMENT_H_

#include <string>
#include "SHACommit.h"
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

class Commitment {
public:
    string value, message, opening;
//    bool checkReveal(string message, string opening);
    
    Commitment();
	Commitment(string message);
	Commitment(ZZ messageValue);
};

#endif /* COMMITMENT_H_ */
