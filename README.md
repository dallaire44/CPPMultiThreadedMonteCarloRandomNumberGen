This repo holds Multi-Threaded C++14 object oriented library that does Monte Carlo pseudo random number generation.

The pseudo random number generation is the Dynamic Creator Multi-Threaded (DCMT) version of the Mersenne Twister found here:

http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/DC/dc.html

The tar file is dcmt0.6.2.tgz.

This compiled to a static library in a sister directory '../dcmt0.6.2/lib' by running the makefile found there.


The DCMT generation is called in C++ via an adapter pattern in UniformThreadedDC.h. Each threaded generator is initialized using a static variable that increments by one each time an instance of UniformThreaded is created. Here is the constructor:


int UniformThreadedDC::genCount;

UniformThreadedDC::UniformThreadedDC(uint32_t seed) : _seed(seed)
{
   genCount++;
   objId= genRootName + std::to_string(genCount);
   mts = get_mt_parameter_id_st(32,521,genCount,_seed); //i is for the id, period is 2^521
   //This primes the generator
   sgenrand_mt(genCount, mts);
}


In order to use the Decorator pattern, a RandomBase.h has both virtual and pure virtual methods. The RandomThreadedDC.h, also an Adapter pattern, inherits from RandomBase and has the UniformThrededDC as its inner generator.

Using the Decorator pattern, the AntiThetic.h also inherits from RandomBase, but gets its inner generator via the constructor. For memory management, it uses the std::unique_ptr. 

The Driver.cpp holds the main. It can be modified to do various tests. 

In Unbuntu 16.04, type the following at xterm command line to link to the static library libdcmt.a and to compile:


g++ -Wall -O3 -I ./ -I../dcmt0.6.2/include  -L../dcmt0.6.2/lib -o driver ./Distributions.cpp ./RandomBase.cpp ./UniformThreadedDC.cpp ./RandomThreadedDC.cpp  ./AntiThetic.cpp ./DCDriver.cpp -ldcmt  -lpthread -std=c++14


Note in the performance numbers below, the virtual inheritance adds 5s extra (21s RandomThreadedDC minus 16s for UniformThreadedDC) via vlookups over the 1B generated numbers. The 5s is a small hit compared to the benefits, such as easier maintenance and quicker addition of new functionality, of the virtual inheritance.

Plan to add a Strategy pattern that will keep a record of the numbers generated and then put through a battery of test statistics:

https://en.wikipedia.org/wiki/Diehard_tests



Performance Numbers:



----------------------TEST UNIFORM----------------------------------------
Number of threads: 7
Random numbers per thread: 1000000000
THREADED RESULTS
Time difference in micro = 16757512
Time difference in nano = 16757512487
Time difference in seconds = 16
LOOP RESULTS
Time difference in micro = 62358692
Time difference in nano = 62358692073
Time difference in seconds = 62
----------------------TEST RANDOM THREADED----------------------------------------
Number of threads: 7
Random numbers per thread: 1000000000
THREADED RESULTS
Time difference in micro = 21461692
Time difference in nano = 21461692806
Time difference in seconds = 21
LOOP RESULTS
Time difference in micro = 71030661
Time difference in nano = 71030661089
Time difference in seconds = 71
----------------------TEST ANTITHETIC THREADED----------------------------------------
Number of threads: 7
Random numbers per thread: 1000000000
THREADED RESULTS
Time difference in micro = 15142801
Time difference in nano = 15142801119
Time difference in seconds = 15
LOOP RESULTS
Time difference in micro = 53342698
Time difference in nano = 53342698132
Time difference in seconds = 53

