
namespace lasd {

/* ************************************************************************** */
//Vector

//Constructors
template <typename Data>
Vector<Data>::Vector(const ulong s) {
    size = s;
    Elements = new Data[size] {};
}

template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data> & c) : Vector(c.Size()) {
    ulong i = 0;
    c.Traverse([this, &i](const Data & data) {
        Elements[i] = data;
        i++;
    }
  );
}
template<typename Data>
Vector<Data>::Vector(MappableContainer<Data> && c) : Vector(c.Size()) {
    ulong i = 0;
    c.Map([this, &i](Data & data) {
        Elements[i] = std::move(data);
        i++;
    }
         );
}

//Copy & Move constructor
template<typename Data>
Vector<Data>::Vector(const Vector<Data> & v) {
    size = v.size;
    Elements = new Data[size];
    std::copy(v.Elements, v.Elements + size, Elements);
}

template<typename Data>
Vector<Data>::Vector(Vector<Data> && v) noexcept {
    std::swap(size, v.size);
    std::swap(Elements, v.Elements);
}
// Destructor
template<typename Data>
Vector<Data>::~Vector() {
    delete[] Elements;
}
//Copy & Move assignment
template<typename Data>
Vector<Data> & Vector<Data>::operator=(const Vector<Data> & v) {
    Vector<Data> * tmp = new Vector<Data>(v);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
}

// Move assignment (Vector)
template<typename Data>
Vector<Data> & Vector<Data>::operator=(Vector<Data> && v) noexcept {
    std::swap(size, v.size);
    std::swap(Elements, v.Elements);
    return *this;
}

// Comparison operators

template<typename Data>
bool Vector<Data>::operator==(const Vector<Data> & v) const noexcept {
    if(size == v.size) {

        for(ulong i = 0; i < size; ++i) {
            if(Elements[i] != v.Elements[i]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

template<typename Data>
bool Vector<Data>::operator!=(const Vector<Data> & v) const noexcept {
    return !(*this == v);
}
// Specific member functions (inherited from MutableLinearContainer)
template<typename Data>
Data & Vector<Data>::operator[](const ulong i) {
    return const_cast<Data &>(static_cast<const Vector<Data>* >(this)->operator[](i));
}
template<typename Data>
Data & Vector<Data>::Front() {
    return const_cast<Data &>(static_cast<const Vector<Data>*>(this)->Front());
}
template<typename Data>
Data & Vector<Data>::Back() {
    return const_cast<Data &>(static_cast<const Vector<Data>*>(this)->Back());
}

// Specific member functions (inherited from LinearContainer)
template<typename Data>
const Data & Vector<Data>::operator[](const ulong i) const {
    if(i < size) {
        return Elements[i];
    } else {
        throw std::out_of_range("Access at index " + std::to_string(i) + "; vector size " + std::to_string(size) + ".");
    }
}

template<typename Data>
const Data & Vector<Data>::Front() const {
    if(size != 0) {
        return Elements[0];
    } else {
        throw std::length_error("Access to an empty vector.");
    }
}
template<typename Data>
const Data & Vector<Data>::Back() const {
    if(size != 0) {
        return Elements[size - 1];
    } else {
        throw std::length_error("Access to an empty vector.");
    }
}
//Resize & Clear
template<typename Data>
void Vector<Data>::Resize(const ulong newsize) {

    if(newsize == 0) {
        delete[] Elements;
        Elements = nullptr;
        size = 0;
    } else if(size != newsize) {
        Data * TmpE = new Data[newsize] {};
        ulong minsize = (size < newsize) ? size : newsize;
        for(ulong i = 0; i < minsize; i++) {
            std::swap(Elements[i], TmpE[i]);
        }
        std::swap(Elements, TmpE);
        size = newsize;
        delete[] TmpE;
    }
}

template<typename Data>
void Vector<Data>::Clear() {
    Resize(0);
}


/* ************************************************************************** */
//SortableVector

//Constructors
template<typename Data>
SortableVector<Data>::SortableVector(const ulong s) : Vector<Data>(s) {}

template<typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data> & c) : Vector<Data>(c) {}

template<typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data> && c) : Vector<Data>(std::move(c)) {}


// Copy & Move constructor
template<typename Data>
SortableVector<Data>::SortableVector(const SortableVector<Data> & v) : Vector<Data>(v) {}

template<typename Data>
SortableVector<Data>::SortableVector(SortableVector<Data> && v) noexcept : Vector<Data>(std::move(v)) {}


// Copy & Move assignment
template<typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(const SortableVector<Data> & v) {
    Vector<Data>::operator=(v);
    return *this;
}


template<typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(SortableVector<Data> && v) noexcept {
    Vector<Data>::operator=(std::move(v));
    return *this;
}
/* ************************************************************************** */

}
