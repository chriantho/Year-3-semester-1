
// COS30008, Problem Set 2, 2025

#pragma once

#include <string>
#include <cstdint>
#include <concepts>

constexpr uint64_t MAX_FIBONACCI = 93;

class FibonacciSequence
{
private:
 
    uint64_t fPrevious;     // previous Fibonacci number (initially 0)
    uint64_t fCurrent;      // current Fibonacci number (initially 1)

public:
    
    using iterator = FibonacciSequence;
    using difference_type = std::ptrdiff_t;         // to satisfy concept weakly_incrementable
    using value_type = uint64_t;                    // to satisfy concept indirectly_readable

    FibonacciSequence() noexcept;

    // Retrieve the current Fibonacci number
    const uint64_t& operator*() const noexcept;

    FibonacciSequence& operator++() noexcept;   // prefix, next Fibonacci number
    FibonacciSequence operator++(int) noexcept; // postfix (extra unused argument)

    bool operator==( const FibonacciSequence& aOther ) const noexcept;

    // Position iterator at start
    void begin() noexcept;

    // Position iterator at no limit
    void end() noexcept;
};

static_assert(std::forward_iterator<FibonacciSequence>);
