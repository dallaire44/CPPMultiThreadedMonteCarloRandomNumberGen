/*

Author: David Dallaire / http://omegairisk.ca / david.dallaire@sympatico.ca - https://ca.linkein.com/in/ddallaire
Date: Dec 13, 2017

Adapter Pattern calling the multi-threaded Mersenne Twister

http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/DC/dc.html

*/


#include <RandomBase.h>
#include <Distributions.h>

double RandomBase::GetGaussian(double uniform)
{
	return MoroQuantile(uniform);
}


