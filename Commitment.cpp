/*
 * Commitment.cpp
 *
 *  Created on: May 7, 2015
 *      Author: Tom
 */

#include <sstream>
#include "Commitment.h"

Commitment::Commitment() {
}

Commitment::Commitment(string message) {
	this->message = message;
	SHACommit::commit(message, value, opening);
}

Commitment::Commitment(ZZ messageValue) {
	stringstream buffer;
	buffer << messageValue;
	message = buffer.str();
	SHACommit::commit(message, value, opening);
}

//bool Commitment::checkReveal(string message, string opening) {
//    return SHACommit::checkReveal(message, this->value, opening);
//}
