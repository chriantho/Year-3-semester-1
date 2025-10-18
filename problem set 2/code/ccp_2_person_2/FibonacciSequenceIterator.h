
// COS30008, Problem Set 2, 2025

#pragma once

#include "FibonacciSequence.h"

class FibonacciSequenceIterator
{
private:

    FibonacciSequence* fSequence;   // sequence object
    uint64_t fIndex;                // current iterator position

public:
    
    using iterator = FibonacciSequenceIterator;
    using difference_type = std::ptrdiff_t;         // to satisfy concept weakly_incrementable
    using value_type = uint64_t;                    // to satisfy concept indirectly_readable

    // iterator constructor
    FibonacciSequenceIterator( FibonacciSequence* aSequence = nullptr,
                               uint64_t aStart = 0 ) noexcept;
    
    // iterator methods
    const uint64_t& operator*() const noexcept;         // return current Fibonacci number
    FibonacciSequenceIterator& operator++() noexcept;   // prefix, next Fibonacci number
    FibonacciSequenceIterator operator++(int) noexcept; // postfix (extra unused argument)

    bool operator==( const FibonacciSequenceIterator& aOther ) const noexcept;

    // return new iterator positioned at start
    FibonacciSequenceIterator begin() const noexcept;

    // return new iterator positioned at limit
    FibonacciSequenceIterator end() const noexcept;
};

template<typename T>
concept BasicForwardIterator =
std::forward_iterator<T> &&                     // a basic forward iterator is a forward iterator
requires( const T i, const T j )
{    // { expression } -> type_constraint;
    { i.begin() } -> std::same_as<T>;           // basic forward iterator provides begin()
    { i.end() } -> std::same_as<T>;             // basic forward iterator provides end()
};

static_assert(BasicForwardIterator<FibonacciSequenceIterator>);
