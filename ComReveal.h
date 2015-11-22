/*
 * ComReveal.h
 *
 *  Created on: May 8, 2015
 *      Author: Tom
 */

#ifndef COMREVEAL_H_
#define COMREVEAL_H_

#include <NTL/ZZ.h>
#include "Commitment.h"

class ComReveal {
public:
	ZZ message;
	string opening;
	ComReveal();
	ComReveal(ZZ message, string opening);
	ComReveal(Commitment com);
	size_t size();
};

#endif /* COMREVEAL_H_ */
