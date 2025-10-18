// COS30008 - Problem Set 3, 2025

#include <iostream>

template<typename T>
void printArray(T aArray[], size_t aSize) {
    std::cout << '[';

    if (aSize > 0) {
        std::cout << aArray[0];

        for (size_t i = 1; i < aSize; i++) {
            std::cout << ", " << aArray[i];
        }
    }

    std::cout << ']' << std::endl;
}

#define P1
#define P2

// #if defined(P1)

#include "SortablePair.h"

void testP1() {
    using MyPair = SortablePair<size_t, int>;

    MyPair lArray[] = {
        {4, 34}, {3, 2}, {2, 890}, {1, 40}, {2, 16},
        {3, 218}, {5, 20}, {3, 49}, {9, 10}, {2, 29}
    };
    size_t lSize = sizeof(lArray) / sizeof(MyPair);

    std::cout << "Test Sortable Pair:" << std::endl;

    printArray(lArray, lSize);

    std::cout << "Test getter:" << std::endl;

    for (size_t i = 0; i < lSize; i++) {
        std::cout << lArray[i].first() << " - " << lArray[i].second() << std::endl;
    }

    std::cout << "Test operator== :" << std::endl;

    for (size_t i = 0; i < lSize; i++) {
        std::cout << i << ": " << (lArray[i] == lArray[0] ? "Yes" : "No") << std::endl;
    }

    std::cout << "Test operator<:" << std::endl;

    for (size_t i = 0; i < lSize; i++) {
        std::cout << i << ":";

        for (size_t j = 0; j < lSize; j++) {
            std::cout << '\t' << (lArray[i] < lArray[j] ? "Yes" : "No");
        }

        std::cout << std::endl;
    }

    std::cout << "Test Sortable Pair completed." << std::endl;
}

// #endif

// #if defined(P2)

#include "PriorityQueue.h"

void testP2() {
    using MyPair = SortablePair<size_t, int>;

    MyPair lArray[] = {
        {4, 34}, {3, 2}, {2, 890}, {1, 40}, {2, 16},
        {3, 218}, {5, 20}, {3, 49}, {9, 10}, {2, 29}
    };
    size_t lSize = sizeof(lArray) / sizeof(MyPair);

    std::cout << "Test Priority Queue:" << std::endl;

    PriorityQueue<int, size_t> lQueue;

    std::cout << "Queue capacity: " << lQueue.capacity() << ", count: " << lQueue.count() << std::endl;

    for (size_t i = 0; i < lSize; i++) {
        lQueue.push(lArray[i].second(), lArray[i].first());

        std::cout << "Add " << lArray[i];
        std::cout << ", top: " << lQueue.top().value();
        std::cout << ", capacity: " << lQueue.capacity() << ", count: " << lQueue.count() << std::endl;
    }

    std::cout << "Access all elements:" << std::endl;

    std::optional<int> lValue = lQueue.top();

    while (lValue) {
        std::cout << lValue.value();

        lQueue.pop();
        lValue = lQueue.top();

        std::cout << ", capacity: " << lQueue.capacity() << ", count: " << lQueue.count() << std::endl;
    }

    std::cout << "Test Priority Queue complete." << std::endl;
}

// #endif


int main() {
#if defined(P1)

    testP1();

#endif

#if defined(P2)

    testP2();

#endif

    return 0;
}
