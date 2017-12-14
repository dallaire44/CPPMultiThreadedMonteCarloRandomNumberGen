/*

Author: David Dallaire / http://omegairisk.ca / david.dallaire@sympatico.ca - https://ca.linkein.com/in/ddallaire
Date: Dec 13, 2017

Adapter Pattern calling the multi-threaded Mersenne Twister

http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/DC/dc.html


*/

#include<UniformThreadedDC.h>
#include<iostream>


int UniformThreadedDC::genCount;

UniformThreadedDC::UniformThreadedDC(uint32_t seed) : _seed(seed)
{
   genCount++;
   objId= genRootName + std::to_string(genCount);
   mts = get_mt_parameter_id_st(32,521,genCount,_seed); //i is for the id, period is 2^521
   //This primes the generator
   sgenrand_mt(genCount, mts);
}

double 
UniformThreadedDC::GetOneUniform()
{

   double uniformNumber = ((double)genrand_mt(mts)/rand_denom);
   //std::cout << "UniformThreadedDC GEN: " << objId << " uniform = " << uniformNumber << std::endl;
   return uniformNumber;

}
