// COS30008, Problem Set 2, 2025

#include <iostream>
#include <iomanip>

//#define P1
//#define P2

static size_t gCount = 0;

// #ifdef P1

#include "FibonacciSequence.h"

void runP1()
{
    gCount++;

    FibonacciSequence iter;

    std::cout << "Fibonacci sequence for unsigned long long:" << std::endl;

    for ( size_t i = 1; i <= MAX_FIBONACCI; i++ )
    {
        std::cout << std::setw(2) << i << ": " << *iter++ << std::endl;
    }
    
    if ( (iter.begin(), *iter) == 1 &&
         (iter.begin(), *(++iter)) == 1 &&
         (iter.end(), *iter) == 0 &&
         (iter.end(), *(++iter)) == 0 )
    {
        std::cout << "FibonacciSequence is sound." << std::endl;
    }
    else
    {
        std::cout << "There are issues with FibonacciSequence." << std::endl;
    }
}

// #endif

// #ifdef P2

#include "FibonacciSequence.h"
#include "FibonacciSequenceIterator.h"

void runP2()
{
    gCount++;

    FibonacciSequence lSequence;
    long long lCount = 0;
    
    std::cout << "Fibonacci sequence for 5 numbers:" << std::endl;

    for ( size_t i = 1; i <= 5; i++ )
    {
        std::cout << std::setw(2) << i << ": " << *lSequence++ << std::endl;
    }
    
    std::cout << "\nFibonacci sequence for unsigned long long:" << std::endl;

    for (const auto& n : FibonacciSequenceIterator( &lSequence ) )
    {
        std::cout << std::setw(2) << ++lCount << ": " << n << std::endl;
    }

    if (lCount == MAX_FIBONACCI)
    {
        std::cout << "The Fibonacci sequence was generated successfully." << std::endl;
    }
    else
    {
        std::cout << "The iterator finished at the wrong number." << std::endl;
    }
}

// #endif

int main() {
// #ifdef P1
    runP1();
// #endif

// #ifdef P2
    runP2();
// #endif

    if (gCount == 0) {
        std::cout << "No test enabled." << std::endl;
    } else {
        std::cout << gCount << " test(s) run." << std::endl;
    }

    return 0;
}
