
// COS30008, Midterm 2025

#include <iostream>
#include <string>
#include <cctype>

#define P1
#define P2

static size_t gCount = 0;

#include "AutoKey.h"
#include "VigenereIterator.h"

void VigenereIterator::initializeTable() noexcept
{
    for ( char row = 0; row < CHARACTERS; row++ )
    {
        char lChar = 'B' + row;

        for ( char column = 0; column < CHARACTERS; column++ )
        {
            if ( lChar > 'Z' )
                lChar = 'A';

            fMappingTable[row][column] = lChar++;
        }
    }
}

// #ifdef P1

void runP1()
{
    gCount++;

    std::cout << "Test AutoKey:" << std::endl;

    std::string lKeyword = "G'day mate.";

    AutoKey lAutoKey( lKeyword );

    std::cout << "Initial lAutoKey: \"";

    for ( size_t i = 0; i < lAutoKey.size(); i++ )
    {
        std::cout << *lAutoKey++;
    }

    std::cout << "\", Length = " << lAutoKey.size() << std::endl;

    lAutoKey.reset();

    std::string lPhrase = "To be, or not to be: that is the question:";

    std::cout << "Test phrase: \"" << lPhrase << "\"" << std::endl;

    size_t lAdded = 0;

    for ( char c : lPhrase )
    {
        lAutoKey += c;

        if ( std::isalpha(c) )
        {
            std::cout << "Character '" << c << "' must be added." << std::endl;

            lAdded++;
        }
        else
        {
            std::cout << "Character '" << c << "' must be skipped." << std::endl;
        }
    }

    std::cout << "Number of characters added to lKeyword: " << lAdded << std::endl;

    std::cout << "lAutoKey after the lPhrase has been added: \"";

    for ( size_t i = 0; i < lAutoKey.size(); i++ )
    {
        std::cout << *lAutoKey++;
    }

    std::cout << "\", Length = " << lAutoKey.size() << std::endl;

    lAutoKey.reset();

    std::cout << "lAutoKey after reset: \"";

    for ( size_t i = 0; i < lAutoKey.size(); i++ )
    {
        std::cout << *lAutoKey++;
    }

    std::cout << "\", Length = " << lAutoKey.size() << std::endl;

    std::cout << "Test AutoKey complete." << std::endl;
}

// #endif

// #ifdef P2

void runP2()
{
    gCount++;

    std::cout << "Test VigenereIterator:" << std::endl;

    std::string lKeyword = "G'day mate.";

    std::string lPhrase1 = "To be, or not to be: that is the question:";
    std::string lPhrase2 = "Be cool.";
    std::string lPhrase3 = "12345";


    std::cout << "First phrase: \"" << lPhrase1 << "\"" << std::endl;

    std::string lEncoded1;
    VigenereIterator iter1(lKeyword, lPhrase1);

    for (; iter1 != iter1.end(); ++iter1)
    {
        lEncoded1 += *iter1;
    }

    std::cout << "Encoded text: \"" << lEncoded1 << "\"" << std::endl;

    std::string lDecoded1;
    VigenereIterator iter2(lKeyword, lEncoded1, EVigenereMode::Decode);

    for (; iter2 != iter2.end(); iter2++)
    {
        lDecoded1 += *iter2;
    }

    std::cout << "Decoded text: \"" << lDecoded1 << "\"" << std::endl;

    std::cout << "Second phrase: \"" << lPhrase2 << "\"" << std::endl;
    std::string lEncoded2;

    for (char c : VigenereIterator(lKeyword, lPhrase2))
    {
        lEncoded2 += c;
    }

    std::cout << "Encoded text: \"" << lEncoded2 << "\"" << std::endl;

    std::string lDecoded2;

    for (char c : VigenereIterator(lKeyword, lEncoded2, EVigenereMode::Decode))
    {
        lDecoded2 += c;
    }

    std::cout << "Decoded text: \"" << lDecoded2 << "\"" << std::endl;

    std::cout << "Third phrase: \"" << lPhrase3 << "\"" << std::endl;
    std::string lEncoded3;

    for (char c : VigenereIterator(lKeyword, lPhrase3))
    {
        lEncoded3 += c;
    }

    std::cout << "Encoded text: \"" << lEncoded3 << "\"" << std::endl;

    std::string lDecoded3;

    for (char c : VigenereIterator(lKeyword, lEncoded3, EVigenereMode::Decode))
    {
        lDecoded3 += c;
    }

    std::cout << "Decoded text: \"" << lDecoded3 << "\"" << std::endl;

    std::cout << "Test VigenereIterator complete." << std::endl;
}

// #endif

int main(int argc, char* argv[])
{
// #ifdef P1

    runP1();

// #endif

// #ifdef P2

    runP2();

// #endif

    if (gCount != 0)
    {
        std::cout << gCount << " Test(s) completed." << std::endl;
    }
    else
    {
        std::cout << "No Test enabled." << std::endl;
    }

    return 0;
}
