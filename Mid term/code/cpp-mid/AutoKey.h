
// COS30008, Midterm 2025

#pragma once

#include <string>
#include <ostream>
#include <cctype>
#include <concepts>

class AutoKey
{
private:

    std::string fValue;
    size_t fKeyLength;
    size_t fIndex;
    
public:
    
    using difference_type = std::ptrdiff_t;
    using value_type = char;

    AutoKey( const std::string& aKeyword = "" ) noexcept;

    size_t size() const noexcept;
    
    char operator*() const noexcept;
    AutoKey& operator++() noexcept;
    AutoKey operator++(int) noexcept;

    AutoKey& operator+=( char aChar ) noexcept;

    void reset() noexcept;
};

static_assert(std::input_iterator<AutoKey>);

