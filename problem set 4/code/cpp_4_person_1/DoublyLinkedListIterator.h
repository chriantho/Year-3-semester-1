
// COS30008, Tutorial 11, 2025

#pragma once

#include <cassert>

#include "DoublyLinkedList.h"

template<typename T>
class DoublyLinkedListIterator
{
public:
    using iterator = DoublyLinkedListIterator<T>;
    using node = DoublyLinkedList<T>::node;
    using difference_type = std::ptrdiff_t;                     // to satisfy concept weakly_incrementable
    using value_type = T;                                       // to satisfy concept indirectly_readable

    enum class States { BEFORE, DATA, AFTER };

    DoublyLinkedListIterator() noexcept : fState(States::AFTER) {}
    DoublyLinkedListIterator( const node& aHead, const node& aTail ) noexcept :
        fHead(aHead),
        fTail(aTail),
        fPosition(aHead),
        fState(States::DATA)
    {
        // sound head and tail values
        assert( !fHead == !fTail );
        
        if ( !fHead )
        {
            fState = States::AFTER;
        }
    }

    
    const T& operator*() const noexcept
    {
        return fPosition->data;
    }

    iterator& operator++() noexcept                // prefix
    {
        switch ( fState )
         {
             case States::BEFORE:
                 fPosition = fHead;
                 
                 if ( fPosition )
                 {
                     fState = States::DATA;
                 }
                 else
                 {
                     fState = States::AFTER;
                 }
                 
                 break;
                 
             case States::DATA:
                 fPosition = fPosition->next;

                 if ( !fPosition )
                 {
                     fState = States::AFTER;
                 }

                 break;
             
             case States::AFTER:
                 break;
         }
         
         return *this;
    }

    iterator operator++(int) noexcept              // postfix
    {
        iterator old = *this;
        
        ++(*this);
        
        return old;
    }

    iterator& operator--() noexcept                // prefix
    {
        switch ( fState )
         {
             case States::BEFORE:

                 break;
                 
             case States::DATA:
                 fPosition = fPosition->previous.lock();

                 if ( !fPosition )
                 {
                     fState = States::BEFORE;
                 }

                 break;
             
             case States::AFTER:
                 fPosition = fTail;
                 
                 if ( fPosition )
                 {
                     fState = States::DATA;
                 }
                 else
                 {
                     fState = States::BEFORE;
                 }
                 
                 break;
         }
         
         return *this;
    }

    iterator operator--(int) noexcept              // postfix
    {
        iterator old = *this;
        
        --(*this);
        
        return old;
    }

    bool operator==( const iterator& aOther ) const noexcept
    {
        return
            fHead == aOther.fHead &&
            fTail == aOther.fTail &&
            fPosition == aOther.fPosition &&
            fState == aOther.fState;
    }

    iterator begin() const noexcept
    {
        return ++(rend());
    }

    iterator end() const noexcept
    {
        iterator iter = *this;
            
        iter.fPosition = nullptr;
        iter.fState = States::AFTER;
            
        return iter;
    }

    iterator rbegin() const noexcept
    {
        return --(end());
    }
    
    iterator rend() const noexcept
    {
        iterator iter = *this;
            
        iter.fPosition = nullptr;
        iter.fState = States::BEFORE;
            
        return iter;
    }

private:
    node fHead;
    node fTail;
    node fPosition;
    States fState;
};

template<typename T>
concept BasicBidirectionalIterator =
std::bidirectional_iterator<T> &&
requires( T i, T j )
{
    { i.begin() } -> std::same_as<T>;
    { i.end() } -> std::same_as<T>;
};

static_assert( BasicBidirectionalIterator<DoublyLinkedListIterator<int>>);
