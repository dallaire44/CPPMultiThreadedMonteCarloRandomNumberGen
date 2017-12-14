/*

Author: David Dallaire / http://omegairisk.ca / david.dallaire@sympatico.ca - https://ca.linkein.com/in/ddallaire
Date: Dec 13, 2017

Decorator Pattern that call RandomThreadedDC internally
Using std::unique_ptr to manage memomory C++14

http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/DC/dc.html

*/


#ifndef ANTITHETIC_H
#define ANTITHETIC_H

#include <RandomBase.h>
#include <memory>
#include <iostream>

class AntiThetic : public RandomBase
{
public:
   AntiThetic(std::unique_ptr<RandomBase> inGenerator);

    virtual double GetUniform();    
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();
    //for performance test 
    void MultGen(int loop=1) {for (int i=0; i < loop; i++)
				   GetUniform();} 

   //diagnostic
   void PrintGen(int thread, int loop=1) {for (int i=0; i < loop; i++)
				   std::cout << "GEN_" << thread << "-" << i << " -> "  << GetUniform() << std::endl;}

   //diagnostic
   void PrintGaussian(int thread, int loop=1) {for (int i=0; i < loop; i++)
				   std::cout << "GAUSS_" << thread << " -> "  << GetGaussian(GetUniform()) << std::endl;}   

private:
   std::unique_ptr<RandomBase> innerGenerator;
   bool oddEven;
   double randomHolder;

};

#endif
