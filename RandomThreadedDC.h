/*

Author: David Dallaire / http://omegairisk.ca / david.dallaire@sympatico.ca - https://ca.linkein.com/in/ddallaire
Date: Dec 13, 2017

Adapter Pattern calling the multi-threaded Mersenne Twister

http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/DC/dc.html

*/



#ifndef RANDOMTHREADEDDC_H
#define RANDOMTHREADEDDC_H

#include<cmath>
#include<vector>
#include<iostream>
#include<string>
#include<RandomBase.h>
#include<UniformThreadedDC.h>


class RandomThreadedDC : public RandomBase
{
public:
   RandomThreadedDC(uint32_t Seed=4172);
   
    virtual double GetUniform();    
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();
    //for performance test 
    virtual void MultGen(int loop=1) {for (int i=0; i < loop; i++)
				   GetUniform();} 

   //diagnostic
   void PrintGen(int thread, int loop=1) {for (int i=0; i < loop; i++)
				   std::cout << "GEN_" << thread << " -> "  << GetUniform() << std::endl;}

   //diagnostic
   void PrintGaussian(int thread, int loop=1) {for (int i=0; i < loop; i++)
				   std::cout << "GAUSS_" << thread << " -> "  << GetGaussian(GetUniform()) << std::endl;}


private:

    UniformThreadedDC InnerGenerator;
    unsigned long InitialSeed;

};


#endif
