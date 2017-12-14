/*

Author: David Dallaire / http://omegairisk.ca / david.dallaire@sympatico.ca - https://ca.linkein.com/in/ddallaire
Date: Dec 13, 2017

Adapter Pattern calling the multi-threaded Mersenne Twister

http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/DC/dc.html


*/

#include<RandomThreadedDC.h>
#include<iostream>

RandomThreadedDC::RandomThreadedDC(uint32_t Seed) 
:    RandomBase(),
     InnerGenerator(Seed),
     InitialSeed(Seed)
{
}

double RandomThreadedDC::GetUniform()
{
   return InnerGenerator.GetOneUniform();
}

void RandomThreadedDC::Skip(unsigned long numberOfPaths)
{
   for (unsigned long i=0; i < numberOfPaths; i++)
       GetUniform();
}

void RandomThreadedDC::SetSeed(unsigned long Seed)
{
    InitialSeed = Seed;
    InnerGenerator.SetSeed(Seed);
}

void RandomThreadedDC::Reset()
{
    InnerGenerator.SetSeed(InitialSeed);
}



