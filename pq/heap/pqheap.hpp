
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap: virtual public PQ<Data>, protected HeapVec<Data> {

  private:

  protected:

    using Container::size;
    ulong capacity = 0;

  public:

    // Default constructor
    PQHeap() = default;

    /* ************************************************************************ */

    // Specific constructors
    PQHeap(const TraversableContainer<Data> &); // A priority queue obtained from a TraversableContainer
    PQHeap(MappableContainer<Data> &&); // A priority queue obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    PQHeap(const PQHeap &);

    // Move constructor
    PQHeap(PQHeap &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~PQHeap() = default;

    /* ************************************************************************ */

    // Copy assignment
    PQHeap & operator=(const PQHeap &);

    // Move assignment
    PQHeap & operator=(PQHeap &&) noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from PQ)

    const Data &  Tip() const override; // Override PQ member (must throw std::length_error when empty)
    void RemoveTip() override; // Override PQ member (must throw std::length_error when empty)
    Data TipNRemove() override; // Override PQ member (must throw std::length_error when empty)

    void Insert(const Data &) override; // Override PQ member (Copy of the value)
    void Insert(Data &&) override ; // Override PQ member (Move of the value)

    void Change(ulong index, const Data &) override; // Override PQ member (Copy of the value)
    void Change(ulong index, Data &&) override; // Override PQ member (Move of the value)

    const Data & operator[](ulong) const override;

    void Clear() override;

    /* ************************************************************************** */

    using LinearContainer<Data>::operator==;
    using LinearContainer<Data>::operator!=;
    using LinearContainer<Data>::Front;
    using LinearContainer<Data>::Back;

  protected:

    // Auxiliary functions
    void siftUp(ulong);
    void Resize(ulong);
};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
