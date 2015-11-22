/*
 * SHACommit
 *
 *  Created on: May 6, 2015
 *      Author: Mark
 */

#ifndef SHACOMMIT_H_
#define SHACOMMIT_H_

#include <iostream>
#include <string>
#include <NTL/ZZ.h>
#include "SHA256.h"

using namespace std;
using namespace NTL;

class SHACommit
{
public:

	static const int OPENING_LEN = 5; // opening length in bytes

	static void commit(const string& message, string& commitment, string& opening);
	
	static bool checkReveal(const string& message, const string& commitment, const string& opening);

	static void commit(const ZZ& messageValue, string& commitment, string& opening);

	static bool checkReveal(const ZZ& messageValue, const string& commitment, const string& opening);

};


#endif /* SHACOMMIT_H_ */
