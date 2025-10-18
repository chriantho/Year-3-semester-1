#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"
#include <utility>

template<typename T>
class List {
private:
    using node = typename DoublyLinkedList<T>::node;

    node    fHead;    // first element
    node    fTail;    // last element
    size_t  fSize;    // element count

    // Destroys all nodes
    void clear() noexcept {
        while (fTail) {
            auto prev = fTail->previous.lock();
            fTail->next.reset();
            fTail = prev;
        }
        fHead.reset();
        fSize = 0;
    }

public:
    using iterator = DoublyLinkedListIterator<T>;

    List() noexcept
        : fHead(nullptr), fTail(nullptr), fSize(0) {
    }

    ~List() {
        clear();
    }

    size_t size() const noexcept {
        return fSize;
    }

    template<typename U>
    void push_front(U &&aData) {
        // create new node and link at head
        auto n = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));
        node nullPrev;
        n->link(nullPrev, fHead);

        if (fHead)
            fHead->previous = n;
        else
            fTail = n;

        fHead = n;
        ++fSize;
    }

    template<typename U>
    void push_back(U &&aData) {
        // create new node and link at tail
        auto n = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));
        node nullNext;
        n->link(fTail, nullNext);

        if (fTail)
            fTail->next = n;
        else
            fHead = n;

        fTail = n;
        ++fSize;
    }

    void remove(const T &aElement) noexcept {
        // remove first matching element
        auto cur = fHead;
        while (cur && cur->data != aElement)
            cur = cur->next;
        if (!cur) return;

        if (cur == fHead) fHead = cur->next;
        if (cur == fTail) fTail = cur->previous.lock();

        cur->isolate();
        --fSize;
    }

    const T &operator[](size_t aIndex) const {
        // random access by index, choose shortest path
        auto cur = (aIndex < fSize / 2 ? fHead : fTail);
        if (aIndex < fSize / 2) {
            for (size_t i = 0; i < aIndex; ++i)
                cur = cur->next;
        } else {
            for (size_t i = fSize - 1; i > aIndex; --i)
                cur = cur->previous.lock();
        }
        return cur->data;
    }

    iterator begin() const noexcept { return iterator(fHead, fTail).begin(); }
    iterator end() const noexcept { return iterator(fHead, fTail).end(); }
    iterator rbegin() const noexcept { return iterator(fHead, fTail).rbegin(); }
    iterator rend() const noexcept { return iterator(fHead, fTail).rend(); }

    // copy constructor
    List(const List &aOther)
        : fHead(nullptr), fTail(nullptr), fSize(0) {
        // copy each element in order
        for (auto cur = aOther.fHead; cur; cur = cur->next)
            push_back(cur->data);
    }

    // copy‐assignment
    List &operator=(const List &aOther) {
        if (this == &aOther)
            return *this;

        clear();
        for (auto cur = aOther.fHead; cur; cur = cur->next)
            push_back(cur->data);
        return *this;
    }

    // move constructor
    List(List &&aOther) noexcept
        : fHead(std::exchange(aOther.fHead, nullptr))
          , fTail(std::exchange(aOther.fTail, nullptr))
          , fSize(std::exchange(aOther.fSize, 0)) {
    }

    // swap helper
    void swap(List &aOther) noexcept {
        using std::swap;
        swap(fHead, aOther.fHead);
        swap(fTail, aOther.fTail);
        swap(fSize, aOther.fSize);
    }

    // move‐assignment (clear then swap)
    List &operator=(List &&aOther) noexcept {
        if (this == &aOther)
            return *this;

        clear();
        swap(aOther);
        return *this;
    }
};
