/*
 * NTAlgorithm.h
 *
 *  Created on: May 6, 2015
 *      Author: Yi-Hsiu Chen
 */

#ifndef NTALGORITHM_H_
#define NTALGORITHM_H_

#include <NTL/ZZ.h>
using namespace NTL;

class NTAlgorithm
{
public:
	static void TwoSquare(ZZ p, ZZ &x, ZZ &y);
    static void FourSquare(ZZ n, ZZ &x, ZZ &y, ZZ &z, ZZ &w);
};



#endif /* NTALGORITHM_H_ */
