/*

Author: David Dallaire / http://omegairisk.ca / david.dallaire@sympatico.ca - https://ca.linkein.com/in/ddallaire
Date: Dec 13, 2017

Adapter Pattern calling the multi-threaded Mersenne Twister

http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/DC/dc.html

*/


#ifndef RANDOMBASE_H
#define RANDOMBASE_H



class RandomBase
{
public:
   RandomBase(){};

   virtual double GetUniform()=0;
   virtual void Skip(unsigned long numberOfPaths)=0;
   virtual void SetSeed(unsigned long Seed) =0;
   virtual void Reset()=0;

   virtual double GetGaussian(double uniform);
   //performance test
   virtual void MultGen(int loop=1)=0;
   //diagnostic
   virtual void PrintGen(int thread, int loop=1)=0;

};


#endif
