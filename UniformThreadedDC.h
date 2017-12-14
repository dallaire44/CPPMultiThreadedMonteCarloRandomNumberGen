/*

Author: David Dallaire / http://omegairisk.ca / david.dallaire@sympatico.ca - https://ca.linkein.com/in/ddallaire
Date: Dec 13, 2017

Adapter Pattern calling the multi-threaded Mersenne Twister

http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/DC/dc.html

*/



#ifndef UNIFORMTHREADEDDC_H
#define UNIFORMTHREADEDDC_H

extern "C" {
#include "dc.h"
}
#include<cmath>
#include<vector>
#include<iostream>
#include<string>

const std::string genRootName="Gen_";

class UniformThreadedDC
{
public:
   UniformThreadedDC(uint32_t seed=4172);
   ~UniformThreadedDC() {}

   //get on uniform number
   double Gen() {return ((double)genrand_mt(mts)/rand_denom);}

   double GetOneUniform();

   void SetSeed(uint32_t seed) { _seed = seed;}

   //diagnostic
   void PrintGen(int loop=1) {for (int i=0; i < loop; i++)
				   std::cout << "GEN: " << objId << " -> " << Gen() << std::endl;}
   //for performance test 
   virtual void MultGen(int loop=1) {for (int i=0; i < loop; i++)
				   Gen();} 
   //Check number of generators when multi-threaded
   void Ping() { std::cout << "Ping UniformThreadedDC - number of threaded generators: " << genCount << std::endl;}
   std::string objId;

private:
   const double rand_denom = std::pow(2.0,32.0) - 1;
   static int genCount;
   mt_struct *mts;
   uint32_t _seed;
};


#endif
