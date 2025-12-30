
namespace lasd {

/* ************************************************************************** */
// Specific constructors

template<typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data> & c):  HeapVec<Data>(c) {
    this->capacity = this->size;
}

template<typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data> && c):  HeapVec<Data>(std::move(c)) {
    this->capacity = this->size;

}


template<typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data>& pqheap): HeapVec<Data>(pqheap) {
    this->capacity = pqheap.capacity;
}

template<typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data> && pqheap) noexcept:  HeapVec<Data>(std::move(pqheap)) {
    std::swap(this->capacity, pqheap.capacity);

}

/* ************************************************************************** */


// Copy & Move assignment
template<typename Data>
PQHeap<Data> & PQHeap<Data>::operator=(const PQHeap<Data> & pqheap) {
    HeapVec<Data>::operator=(pqheap);
    this->capacity = pqheap.capacity;

    return *this;

}
template<typename Data>
PQHeap<Data> & PQHeap<Data>::operator=(PQHeap<Data> && pqheap) noexcept {
    HeapVec<Data>::operator=(std::move(pqheap));
    std::swap(this->capacity, pqheap.capacity);

    return *this;

}


/* ************************************************************************** */

template <typename Data>
const Data& PQHeap<Data>::Tip() const {
    if(size <= 0) throw std::length_error("The priority queue is empty");
    return this->Elements[0];
}

template <typename Data>
void PQHeap<Data>::RemoveTip() {
    if(size <= 0) throw std::length_error("The priority queue is empty");
    if(size == 1) {
        size = 0;
        this->Resize(0);
        return;
    }

    this->Elements[0] =  this->Elements[size - 1];
    size--;
    if((size * 100) / capacity <= 20) {

        this->Resize(capacity / 2);
    }
    if(size > 0) this->heapify(size, 0);
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
    if(size <= 0) throw std::length_error("The priority queue is empty");
    Data val = this->Elements[0];
    RemoveTip();
    return val;
}

/* ************************************************************************** */


template <typename Data>
void PQHeap<Data>::Insert(const Data& value) {
    if(capacity == 0) {
        this->Resize(1);
    }
    if((this->size  * 100) / capacity >= 80) {
        this->Resize(capacity * 2);
    }

    this->Elements[this->size ] = value;
    this->size++;
    this->siftUp(this->size  - 1);
}

template <typename Data>
void PQHeap<Data>::Insert(Data&& value) {
    if(capacity == 0) {
        this->Resize(1);

    }
    if((size * 100) / capacity >= 80) {
        std::cout << "Insert move resize" << std::endl;
        this->Resize(capacity * 2);
    }
    this->Elements[this->size ] = std::move(value);
    this->size++;
    this->siftUp(this->size  - 1);

}

/* ************************************************************************** */

template <typename Data>
void PQHeap<Data>::Change(ulong index, const Data& value) {
    if(size <= 0) throw std::length_error("The priority queue is empty");
    if(size <= index) throw std::out_of_range("Access to an invalid index");

    this->Elements[index] = value;
    this->Heapify();
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, Data&& value) {
    if(size <= 0) throw std::length_error("The priority queue is empty");
    if(size <= index) throw std::out_of_range("Access to an invalid index");
    this->Elements[index] = std::move(value);
    this->Heapify();
}


/* ************************************************************************** */

template<typename Data>
void PQHeap<Data>::Clear() {
    this->Resize(0);
}


template<typename Data>
const Data& PQHeap<Data>::operator[](ulong idx) const   {
    return HeapVec<Data>::operator[](idx);
}




/* ************************************************************************** */
template <typename Data>
void PQHeap<Data>::siftUp(ulong index) {
    if(index == 0) return;
    ulong parent = (index - 1) / 2;
    if(this->Elements[index] > this->Elements[parent]) {
        std::swap(this->Elements[index], this->Elements[parent]);
        siftUp(parent);
    }
}

template <typename Data>
void PQHeap<Data>::Resize(ulong newSize) {

    if(newSize == 0) {
        delete[]  this->Elements;
        this->Elements = nullptr;
        size = 0;
        capacity = 0;
        return;
    } else if(size != newSize) {
        Data * TmpE = new Data[newSize] {};
        ulong minsize = (size < newSize) ? size : newSize;
        for(ulong i = 0; i < minsize; i++) {
            std::swap(this->Elements[i], TmpE[i]);
        }
        std::swap(this->Elements, TmpE);
        size = minsize;
        capacity = newSize;
        delete[] TmpE;
    }

}



}
