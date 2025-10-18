#include "AutoKey.h"
#include <cctype>   // for isalpha and toupper

// Constructor to constructs the auto key by filtering the input keyword
AutoKey::AutoKey(const std::string &aKeyword) noexcept
    : fValue(), fKeyLength(0), fIndex(0)
{
    // Process each character in the provided keyword
    for (char ch : aKeyword) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            fValue.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(ch))));
        }
    }
    // Set the original keyword length for use in reset
    fKeyLength = fValue.size();
}

// Returns current size of the auto key string
size_t AutoKey::size() const noexcept {
    return fValue.size();
}

// Returns the character at the current index of the auto key string
char AutoKey::operator*() const noexcept {
    return fValue[fIndex];
}

// Increments the internal index to move to the next character
AutoKey& AutoKey::operator++() noexcept {
    ++fIndex;
    return *this;
}

// Returns the current state and then advances the auto key iterator
AutoKey AutoKey::operator++(int) noexcept {
    AutoKey temp = *this;
    ++(*this);
    return temp;
}

// Checks if the provided character is an alphabet letter
AutoKey& AutoKey::operator+=(char aChar) noexcept {
    // converts the letter to uppercase and appends it to the auto key string
    if (std::isalpha(static_cast<unsigned char>(aChar))) {
        fValue.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(aChar))));
    }
    return *this;
}

// Restores the auto key to its initial state by resizing the key to its original length and resetting the iterator index to zero
void AutoKey::reset() noexcept {
    fValue.resize(fKeyLength);
    fIndex = 0;
}
