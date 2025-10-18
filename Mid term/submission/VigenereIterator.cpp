#include "VigenereIterator.h"
#include <cctype>   // for isalpha, toupper, tolower

// Constructor to set up the iterator using a member initializer list and then prepares the mapping table
// if a source text exists, it processes the first character appropriately (encode or decode based on the mode)
VigenereIterator::VigenereIterator(const std::string& aKeyword,
                                   const std::string& aSource,
                                   EVigenereMode aMode) noexcept
    : fMode(aMode),
      fKeys(aKeyword),
      fSource(aSource),
      fIndex(0),
      fCurrentChar('\0')
{
    // Set up the cipher mapping using the evaluator’s definition
    initializeTable();

    // Process the first character from fSource if available
    if (!fSource.empty()) {
        if (fMode == EVigenereMode::Encode)
            encodeCurrentChar();
        else
            decodeCurrentChar();
    }
}

// This function enciphers the character at the current position in fSource and only processes alphabetic characters
// The non alphabetic characters are passed unchanged
// The function first determines whether the letter was lowercase and then converts it to uppercase for processing.
// It uses the current auto key character to lookup the encoded result from fMappingTable,
// restores the letter’s case if necessary, and stores the result in fCurrentChar.
// Finally, it advances the auto key iterator and then appends the processed letter to the key.
void VigenereIterator::encodeCurrentChar() noexcept {
    if (fIndex >= fSource.size()) {
        fCurrentChar = '\0';
        return;
    }

    char current = fSource[fIndex];

    // Non alphabetic characters are not processed by the cipher
    if (!std::isalpha(static_cast<unsigned char>(current))) {
        fCurrentChar = current;
        return;
    }

    // Save whether the current character is lowercase for later restoration
    bool isLower = std::islower(static_cast<unsigned char>(current));
    // Convert the letter to uppercase for cipher processing
    char plainChar = static_cast<char>(std::toupper(static_cast<unsigned char>(current)));

    // Retrieve the current letter from the auto key
    char keyChar = *fKeys;
    int row = keyChar - 'A';
    int col = plainChar - 'A';

    // Find the ciphered character using the mapping table
    char encoded = fMappingTable[row][col];

    // If the original was lowercase, adjust the result accordingly
    if (isLower)
        encoded = static_cast<char>(std::tolower(static_cast<unsigned char>(encoded)));
    fCurrentChar = encoded;

    // Advance the auto key iterator and append the uppercase letter to it
    ++fKeys;
    fKeys += plainChar;
}

// This function deciphers the character at the current position in fSource and only processes alphabetic characters.
// Non alphabetic characters are passed unchanged.
// Alphabetic characters are converted to uppercase and decoded using the auto key row in fMappingTable,
// Then they are restored to their original case.
// Finally the auto key is advanced and updated with the decoded letter.
void VigenereIterator::decodeCurrentChar() noexcept {
    if (fIndex >= fSource.size()) {
        fCurrentChar = '\0';
        return;
    }

    // Get the current character from fSource
    char current = fSource[fIndex];

    // Pass through non alphabetic characters
    if (!std::isalpha(static_cast<unsigned char>(current))) {
        fCurrentChar = current;
        return;
    }

    // Preserve the original case of the character
    bool isLower = std::islower(static_cast<unsigned char>(current));

    // Convert for processing
    char encodedChar = static_cast<char>(std::toupper(static_cast<unsigned char>(current)));

    // Get the current key character
    char keyChar = *fKeys;
    int row = keyChar - 'A';

    // Perform a linear search through the row to find the matching character
    int col = 0;
    for (; col < CHARACTERS; col++) {
        if (fMappingTable[row][col] == encodedChar)
            break;
    }
    char decoded = static_cast<char>('A' + col);
    if (isLower)
        decoded = static_cast<char>(std::tolower(static_cast<unsigned char>(decoded)));
    fCurrentChar = decoded;

    // Advance and update the auto key with the deciphered letter
    ++fKeys;
    fKeys += static_cast<char>(std::toupper(decoded));
}

// Returns the current ciphered or deciphered character
char VigenereIterator::operator*() const noexcept {
    return fCurrentChar;
}

// Moves the iterator forward by incrementing fIndex,
// then processes the next character using either encoding or decoding
VigenereIterator& VigenereIterator::operator++() noexcept {
    fIndex++;  // Move to the next character in fSource
    if (fIndex < fSource.size()) {
        if (fMode == EVigenereMode::Encode)
            encodeCurrentChar();
        else
            decodeCurrentChar();
    } else {
        // Signal the end
        fCurrentChar = '\0';
    }
    return *this;
}

// Returns a copy of the iterator before incrementing, then advances the iterator
VigenereIterator VigenereIterator::operator++(int) noexcept {
    VigenereIterator temp = *this;
    ++(*this);
    return temp;
}

// Two iterators are considered equal if they point to the same position in the same source
bool VigenereIterator::operator==(const VigenereIterator& aOther) const noexcept {
    return (fIndex == aOther.fIndex &&
            fSource == aOther.fSource);
}

// Returns an iterator reset to the start of the source
VigenereIterator VigenereIterator::begin() const noexcept {
    VigenereIterator iter = *this;
    iter.fKeys.reset();
    iter.fIndex = 0;
    if (!iter.fSource.empty()) {
        if (iter.fMode == EVigenereMode::Encode)
            iter.encodeCurrentChar();
        else
            iter.decodeCurrentChar();
    }
    return iter;
}

// Returns an iterator positioned immediately after the last character in the source
VigenereIterator VigenereIterator::end() const noexcept {
    VigenereIterator iter = *this;
    iter.fIndex = fSource.size();
    iter.fCurrentChar = '\0';
    return iter;
}
