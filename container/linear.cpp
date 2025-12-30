
namespace lasd {

/* ************************************************************************** */
//LinearContainer
template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer& container) const noexcept{
    if (size != container.size) return false;
    for (ulong index = 0; index<size; index++){
        if (operator[](index) != container.operator[](index)) return false;
    }
    return true;
}

template<typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer& container) const noexcept{
    return !(*this==container);
}

template<typename Data>
inline const Data & LinearContainer<Data>::Front() const {
    if(this->Empty()) {
        throw std::length_error("Empty container");
    } else {
        return operator[](0);
    }
}
template<typename Data>
inline const Data & LinearContainer<Data>::Back() const {
    if(this->Empty()) {
        throw std::length_error("Empty container");
    } else {
        return operator[](size - 1);
    }
}

template<typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun f) const {
    PreOrderTraverse(f);
}
template<typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun f) const {
    for(ulong i = 0; i < size; ++i) {
        f(operator[](i));
    }

}
template<typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun f) const {
    ulong i = size;
    while(i > 0) {
        f(operator[](--i));
    }
}
/* ************************************************************************** */
//MutableLinearContainer
template <typename Data>
inline Data & MutableLinearContainer<Data>::Front() {
    if(this->Empty()) {
        throw std::length_error("Empty container");
    } else {
        return operator[](0);

    }
}


template <typename Data>
inline Data & MutableLinearContainer<Data>::Back() {
    if(this->Empty()) {
        throw std::length_error("Empty container");
    } else {
        return operator[](size - 1);

    }
}

template<typename Data>
inline void MutableLinearContainer<Data>::Map(MapFun f) {
    PreOrderMap(f);
}
template<typename Data>
inline void MutableLinearContainer<Data>::PreOrderMap(MapFun f) {
    for(ulong i = 0; i < size; ++i) {
        f(operator[](i));
    }
}

template<typename Data>
inline void MutableLinearContainer<Data>::PostOrderMap(MapFun f) {
    ulong i = size;
    while(i > 0) {
        f(operator[](--i));
    }
}
/* ************************************************************************** */
//SortableLinearContainer
//Quick Sort SortableLinearContainer
template<typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
    if(this->size <= 0) {
        return;
    } else {
        QuickSort(0, size - 1);

    }
}

template<typename Data>
void SortableLinearContainer<Data>::QuickSort(ulong p, ulong r) noexcept {
    if(p < r) {
        ulong q = Partition(p, r);
        QuickSort(p, q);
        QuickSort(q + 1, r);
    }
}

template<typename Data>
ulong SortableLinearContainer<Data>::Partition(ulong p, ulong r) noexcept {
    Data x = this->operator[](p);
    ulong i = p - 1;
    ulong j = r + 1;
    do {
        do {
            j--;
        } while(x < this->operator[](j));
        do {
            i++;
        } while(x > this->operator[](i));
        if(i < j) {
            std::swap(this->operator[](i), this->operator[](j));
        }
    } while(i < j);
    return j;
}


/* ************************************************************************** */

}
