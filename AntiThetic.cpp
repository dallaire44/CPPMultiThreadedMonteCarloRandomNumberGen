/*

Author: David Dallaire / http://omegairisk.ca / david.dallaire@sympatico.ca - https://ca.linkein.com/in/ddallaire
Date: Dec 13, 2017

Decorator Pattern that call RandomThreadedDC internally
Using std::unique_ptr to manage memomory C++14

http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/DC/dc.html

*/

#include <AntiThetic.h>

AntiThetic::AntiThetic(std::unique_ptr<RandomBase> inGenerator)
	//: RandomBase(*innerGenerator),
	:  innerGenerator( std::move(inGenerator))
{
   innerGenerator->Reset();
   oddEven=true;
}


double
AntiThetic::GetUniform()
{  
   double randomReturn;
   if (oddEven)
   {
       randomHolder=innerGenerator->GetUniform();
       oddEven=false;
       randomReturn=1.0-randomHolder;
       
   }
   else
   {
       randomReturn=randomHolder;
       oddEven=true;
   }
   return randomReturn;
}

void
AntiThetic::SetSeed(unsigned long seed)
{
   innerGenerator->SetSeed(seed);
   oddEven=true;
}

void
AntiThetic::Skip(unsigned long numPaths)
{
   if (numPaths == 0)
      return;

   if (oddEven)
   {
       oddEven=false;
       numPaths--;
   }

   innerGenerator->Skip(numPaths / 2);

   if (numPaths % 2)
   {
       GetUniform();
   }
}


void
AntiThetic::Reset()
{
   innerGenerator->Reset();
   oddEven=true;
}



