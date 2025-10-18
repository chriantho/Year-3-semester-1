
// COS30008, Midterm 2025

#pragma once

#include <concepts>

#include "AutoKey.h"

constexpr size_t CHARACTERS = 26;

enum class EVigenereMode
{
    Encode,
    Decode
};

class VigenereIterator
{
public:
    
    using iterator = VigenereIterator;
    using difference_type = std::ptrdiff_t;
    using value_type = char;
    
    VigenereIterator( const std::string& aKeyword = "",
                      const std::string& aSource = "",
                      EVigenereMode aMode = EVigenereMode::Encode ) noexcept;
    
    char operator*() const noexcept;
    
    VigenereIterator& operator++() noexcept;
    VigenereIterator operator++(int) noexcept;
    
    bool operator==( const VigenereIterator& aOther ) const noexcept;
    
    VigenereIterator begin() const noexcept;
    VigenereIterator end() const noexcept;

private:

    EVigenereMode fMode;
    char fMappingTable[CHARACTERS][CHARACTERS];
    AutoKey fKeys;
    std::string fSource;
    size_t fIndex;
    char fCurrentChar;
    
    void initializeTable() noexcept;
    void encodeCurrentChar() noexcept;
    void decodeCurrentChar() noexcept;
};

template<typename T>
concept BasicForwardIterator =
std::forward_iterator<T> &&              // a basic forward iterator is a forward iterator
requires( const T i, const T j )
{
    { i.begin() } -> std::same_as<T>;   // basic forward iterator provides begin()
    { i.end() } -> std::same_as<T>;     // basic forward iterator provides end()
};

static_assert(BasicForwardIterator<VigenereIterator>);
