/*

Author: David Dallaire / http://omegairisk.ca / david.dallaire@sympatico.ca - https://ca.linkein.com/in/ddallaire
Date: Dec 13, 2017

Driver for random number generation 
Patterns: Adapter, Decorator

http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/DC/dc.html

*/


#include<UniformThreadedDC.h>
#include<RandomThreadedDC.h>
#include<iostream>
#include <thread>
#include <vector>
#include<chrono>
#include <AntiThetic.h>

#include "dc.h"

void
UniformThreadLoop(long int numRandom)
{

   UniformThreadedDC dc(0);
   //dc.SetSeed(-10000);
   //dc.Ping();
   //dc.PrintGen(numRandom);
   //std::cout << "GET ONE: " << dc.GetOneUniform() << std::endl;	
   dc.MultGen(numRandom);
}


void
TestUniform(long int numRandom, long int numThreads)
{

   std::cout << "----------------------TEST UNIFORM----------------------------------------" << std::endl;
   std::cout << "Number of threads: " << numThreads << std::endl;
   std::cout << "Random numbers per thread: " << numRandom << std::endl;
   

   std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

   std::vector<std::thread> threads;
   for (int i = 0; i < numThreads; ++i) 
	threads.push_back(std::thread {UniformThreadLoop, numRandom});
	
   for (auto& t : threads) {
	t.join();
   }

   //for (int i = 0; i < numThreads; ++i) 
  //	ThreadLoop();
   
   std::cout << "THREADED RESULTS" << std::endl;
   std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
   std::cout << "Time difference in micro = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() <<std::endl;
   std::cout << "Time difference in nano = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;
   std::cout << "Time difference in seconds = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() <<std::endl;	

   std::cout << "LOOP RESULTS" << std::endl;
   begin = std::chrono::steady_clock::now();

   for (int i = 0; i < numThreads; ++i) 
  	UniformThreadLoop(numRandom);

   end= std::chrono::steady_clock::now();
   std::cout << "Time difference in micro = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() <<std::endl;
   std::cout << "Time difference in nano = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;
   std::cout << "Time difference in seconds = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() <<std::endl;	

}


void
RandomThreadLoop(long int numRandom, int thread)
{
   //RandomThreadedDC dc(0);
   std::unique_ptr<RandomBase> thePoint = std::make_unique<RandomThreadedDC>();
   //dc.SetSeed(-10000);
   //dc.Ping();
   //dc.PrintGen(thread, numRandom);
   thePoint->PrintGen(thread, numRandom);
   //dc.PrintGaussian(thread, numRandom);

   //std::cout << "GET ONE: " << dc.GetOneUniform() << std::endl;	
   //dc.MultGen(numRandom);
   //thePoint->MultGen(numRandom);
}


void
TestRandomThreaded(long int numRandom, long int numThreads)
{

   std::cout << "----------------------TEST RANDOM THREADED----------------------------------------" << std::endl;
   std::cout << "Number of threads: " << numThreads << std::endl;
   std::cout << "Random numbers per thread: " << numRandom << std::endl;
   

   std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

   std::vector<std::thread> threads;
   for (int i = 0; i < numThreads; ++i) 
	threads.push_back(std::thread {RandomThreadLoop, numRandom, i});
	
   for (auto& t : threads) {
	t.join();
   }

   //for (int i = 0; i < numThreads; ++i) 
  //	ThreadLoop();
   
   std::cout << "THREADED RESULTS" << std::endl;
   std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
   std::cout << "Time difference in micro = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() <<std::endl;
   std::cout << "Time difference in nano = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;
   std::cout << "Time difference in seconds = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() <<std::endl;	

   std::cout << "LOOP RESULTS" << std::endl;
   begin = std::chrono::steady_clock::now();

   for (int i = 0; i < numThreads; ++i) 
  	RandomThreadLoop(numRandom, i);

   end= std::chrono::steady_clock::now();
   std::cout << "Time difference in micro = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() <<std::endl;
   std::cout << "Time difference in nano = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;
   std::cout << "Time difference in seconds = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() <<std::endl;	

}


void
AntiTheticThreadLoop(long int numRandom, int thread)
{
   std::unique_ptr<RandomBase> thePoint = std::make_unique<RandomThreadedDC>();
   thePoint = std::make_unique<AntiThetic>(std::move(thePoint));

   //dc.SetSeed(-10000);
   //dc.Ping();
   //thePoint->PrintGen(thread, numRandom);
   //dc.PrintGaussian(thread, numRandom);

   //std::cout << "GET ONE: " << dc.GetOneUniform() << std::endl;	
   thePoint->MultGen(numRandom);
}


void
TestAntiThetic(long int numRandom, long int numThreads)
{

   std::cout << "----------------------TEST ANTITHETIC THREADED----------------------------------------" << std::endl;
   std::cout << "Number of threads: " << numThreads << std::endl;
   std::cout << "Random numbers per thread: " << numRandom << std::endl;
   

   std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

   std::vector<std::thread> threads;
   for (int i = 0; i < numThreads; ++i) 
	threads.push_back(std::thread {AntiTheticThreadLoop, numRandom, i});
	
   for (auto& t : threads) {
	t.join();
   }

   //for (int i = 0; i < numThreads; ++i) 
  //	ThreadLoop();
   
   std::cout << "THREADED RESULTS" << std::endl;
   std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
   std::cout << "Time difference in micro = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() <<std::endl;
   std::cout << "Time difference in nano = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;
   std::cout << "Time difference in seconds = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() <<std::endl;	

   std::cout << "LOOP RESULTS" << std::endl;
   begin = std::chrono::steady_clock::now();

   for (int i = 0; i < numThreads; ++i) 
  	AntiTheticThreadLoop(numRandom, i);

   end= std::chrono::steady_clock::now();
   std::cout << "Time difference in micro = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() <<std::endl;
   std::cout << "Time difference in nano = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;
   std::cout << "Time difference in seconds = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() <<std::endl;	

}


int main()
{
 
long int numRandom = 10;
int thread = 7;

/*
   UniformThreadedDC dc1;
   dc1.ping();
   dc1.PrintGen(10);
   
   UniformThreadedDC dc2;
   dc2.ping();
   dc2.PrintGen(10);

*/

   //TestUniform(numRandom, thread);
   TestRandomThreaded(numRandom, thread);

/*
   std::unique_ptr<RandomBase> thePoint = std::make_unique<RandomThreadedDC>();
   std::cout << thePoint->GetUniform() << std::endl;

   thePoint = std::make_unique<AntiThetic>(std::move(thePoint));
   std::cout << thePoint->GetUniform() << std::endl;
   std::cout << thePoint->GetGaussian(thePoint->GetUniform()) << std::endl;
*/

   //TestAntiThetic(numRandom, thread);

   return 0;

}
