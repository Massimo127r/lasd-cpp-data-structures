
#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Heap: virtual public SortableLinearContainer<Data>, virtual public ClearableContainer {

  private:

  protected:

  public:

    // Destructor
    virtual ~Heap() = default;

    /* ************************************************************************ */

    // Copy assignment
    Heap & operator=(const Heap &) = delete;

    // Move assignment
    Heap & operator=(Heap &&) noexcept = delete; // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member functions

    virtual bool IsHeap() const = 0;

    virtual void Heapify() = 0;

};

/* ************************************************************************** */

}

#endif
