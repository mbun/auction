/*
 * ComReveal.cpp
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#include "ComReveal.h"

using namespace NTL;

ComReveal::ComReveal() {

}

ComReveal::ComReveal(ZZ message, string opening) {
	this->message = message;
	this->opening = opening;
}

ComReveal::ComReveal(Commitment com) {
	this->message = conv<ZZ>(com.message.c_str());
	this->opening = com.opening;
}

size_t ComReveal::size() {
	return sizeof(ComReveal) + message.size() + opening.size();
}
