
namespace lasd {

/* ************************************************************************** */
//Node

//constructors
template<typename Data>
List<Data>::Node::Node(Data && d) noexcept {
    std::swap(element, d);
}
template<typename Data>
List<Data>::Node::Node(Node && n) noexcept {
    std::swap(element, n.element);
    std::swap(next, n.next);
}
//Destructor
template<typename Data>
List<Data>::Node::~Node() {
    delete next;
}
//Comparison Operators

template<typename Data>
bool List<Data>::Node::operator==(const Node & n) const noexcept {
    return (element == n.element) && ((next == nullptr && n.next == nullptr) || ((next != nullptr && n.next != nullptr) && (*next == *n.next)));
}

template<typename Data>
bool List<Data>::Node::operator!=(const Node & n) const noexcept {
    return !(*this == n);
}
//Clone
template<typename Data>
typename List<Data>::Node * List<Data>::Node::Clone(Node * tail) {
    if(next == nullptr) {
        return tail;
    } else {
        tail->next = new Node(next->element);
        return next->Clone(tail->next);
    }
}

/* ************************************************************************** */
//List

//Constructors

template<typename Data>
List<Data>::List(const TraversableContainer<Data> & c) {
    c.Traverse([this](const Data & data) {
        InsertAtBack(data);
    });
}

template<typename Data>
List<Data>::List(MappableContainer<Data> && c) {
    c.Map([this](Data & data) {
        InsertAtBack(std::move(data));
    });
}
/* ************************************************************************ */

// Copy & Move constructor
template<typename Data>
List<Data>::List(const List<Data> & lst) {
    if(lst.tail != nullptr) {
        head = new Node(*lst.head);
        tail = lst.head->Clone(head);
        size = lst.size;
    }
}

template<typename Data>
List<Data>::List(List<Data> && lst) noexcept {
    std::swap(head, lst.head);
    std::swap(tail, lst.tail);
    std::swap(size, lst.size);
}
/* ************************************************************************ */

// Destructor
template<typename Data>
List<Data>::~List() {
    delete head;
}
/* ************************************************************************ */

// Copy assignment
template<typename Data>
List<Data> & List<Data>::operator=(const List<Data> & lst) {
    List<Data> tmp(lst);
    std::swap(head, tmp.head);
    std::swap(tail, tmp.tail);
    std::swap(size, tmp.size);
    return *this;

}

// Move assignment
template<typename Data>
List<Data> & List<Data>::operator=(List<Data> && lst) noexcept {
    std::swap(head, lst.head);
    std::swap(tail, lst.tail);
    std::swap(size, lst.size);
    return *this;
}
/* ************************************************************************ */

// Comparison operators
template<typename Data>
inline bool List<Data>::operator==(const List<Data> & lst) const noexcept {
    return (size == lst.size) \
           && ((head == nullptr && lst.head == nullptr) || ((head != nullptr && lst.head != nullptr) && (*head == *lst.head)));
}

template<typename Data>
inline bool List<Data>::operator!=(const List<Data> & lst) const noexcept {
    return !(*this == lst);
}
/* ************************************************************************ */
// Specific member functions

template<typename Data>
void List<Data>::InsertAtFront(const Data & dat) {
    Node * ptr = new Node(dat);
    ptr->next = head;
    head = ptr;
    if(tail == nullptr) {
        tail = head;
    }
    ++size;
}

template<typename Data>
void List<Data>::InsertAtFront(Data && dat) {
    Node * ptr = new Node(std::move(dat));
    ptr->next = head;
    head = ptr;
    if(tail == nullptr) {
        tail = head;
    }
    ++size;
}
template<typename Data>
void List<Data>::RemoveFromFront() {
    if(head != nullptr) {
        Node * front = head;
        if(tail == head) {
            head = tail = nullptr;
        } else {
            head = head->next;
        }
        --size;
        front->next = nullptr;
        delete front;
    } else {
        throw std::length_error("Access to an empty list.");
    }
}

template<typename Data>
Data List<Data>::FrontNRemove() {
    if(head != nullptr) {
        Node * front = head;
        if(tail == head) {
            head = tail = nullptr;
        } else {
            head = head->next;
        }
        --size;
        front->next = nullptr;
        Data dat(std::move(front->element));
        delete front;
        return dat;
    } else {
        throw std::length_error("Access to an empty list.");
    }
}

template<typename Data>
void List<Data>::InsertAtBack(const Data & dat) {
    Node * end = new Node(dat);
    if(tail == nullptr) {
        head = end;
    } else {
        tail->next = end;
    }
    tail = end;
    ++size;
}
template<typename Data>
void List<Data>::InsertAtBack(Data && dat) {
    Node * end = new Node(std::move(dat));
    if(tail == nullptr) {
        head = end;
    } else {
        tail->next = end;
    }
    tail = end;
    ++size;
}
template<typename Data>
void List<Data>::RemoveFromBack() {
    if(head != nullptr) {
        if(head == tail) {
            delete tail;
            head = tail = nullptr;
        } else {
            Node* ptr = head;
            while(ptr->next != tail) {
                ptr = ptr->next;
            }
            delete tail;
            tail = ptr;
            tail->next = nullptr;
        }
        --size;
    } else {
        throw std::length_error("Remove from empty list.");
    }
}

template<typename Data>
Data List<Data>::BackNRemove() {
    if(head != nullptr) {
        Data d = tail->element;
        if(head == tail) {
            delete tail;
            head = tail = nullptr;
        } else {
            Node* ptr = head;
            while(ptr->next != tail) {
                ptr = ptr->next;
            }
            delete tail;
            tail = ptr;
            tail->next = nullptr;
        }
        --size;
        return d;
    } else {
        throw std::length_error("BackNRemove from empty list.");
    }
}
/* ************************************************************************ */
// Specific member functions (inherited from MutableLinearContainer)


template<typename Data>
Data & List<Data>::operator[](const ulong index) {
    return const_cast<Data &>(static_cast<const List<Data>* >(this)->operator[](index));
}
template<typename Data>
Data & List<Data>::Front() {
    return const_cast<Data &>(static_cast<const List<Data>*>(this)->Front());
}
template<typename Data>
Data & List<Data>::Back() {
    return const_cast<Data &>(static_cast<const List<Data>*>(this)->Back());
}

/* ************************************************************************ */
// Specific member functions (inherited from LinearContainer)

template<typename Data>
const Data & List<Data>::operator[](const ulong i) const {
    if(i < size) {
        Node * cur = head;
        for(ulong idx = 0; idx < i; ++idx, cur = cur->next) {}
        return cur->element;
    } else {
        throw std::out_of_range("Access at index " + std::to_string(i) + "; list size " + std::to_string(size) + ".");
    }
}

template<typename Data>
const Data & List<Data>::Front() const {
    if(head != nullptr) {
        return head->element;
    } else {
        throw std::length_error("Access to an empty list.");
    }
}

template<typename Data>
const Data & List<Data>::Back() const {
    if(tail != nullptr) {
        return tail->element;
    } else {
        throw std::length_error("Access to an empty list.");
    }
}
/* ************************************************************************ */

// Specific member function (inherited from MappableContainer)
template<typename Data>
inline void List<Data>::Map(MapFun fun) {
    PreOrderMap(fun, head);
}
// Specific member function (inherited from PreOrderMappableContainer)

template<typename Data>
inline void List<Data>::PreOrderMap(MapFun fun) {
    PreOrderMap(fun, head);
}
// Specific member function (inherited from PostOrderMappableContainer)

template<typename Data>
inline void List<Data>::PostOrderMap(MapFun fun) {
    PostOrderMap(fun, head);
}
/* ************************************************************************ */

// Specific member function (inherited from TraversableContainer)

template<typename Data>
inline void List<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun, head);
}

// Specific member function (inherited from PreOrderTraversableContainer)
template<typename Data>
inline void List<Data>::PreOrderTraverse(TraverseFun fun) const {
    PreOrderTraverse(fun, head);
}

// Specific member function (inherited from PostOrderTraversableContainer)

template<typename Data>
inline void List<Data>::PostOrderTraverse(TraverseFun fun) const {
    PostOrderTraverse(fun, head);
}

/* ************************************************************************ */

// Specific member function (inherited from ClearableContainer)
template<typename Data>
void List<Data>::Clear() {
    delete head;
    head = tail = nullptr;
    size = 0;
}
// Auxiliary functions


template<typename Data>
void List<Data>::PreOrderMap(MapFun fun, Node * cur) {
    while(cur != nullptr) {
        fun(cur->element);
        cur = cur->next;
    }
}

template<typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node * cur) {
    if(cur != nullptr) {
        PostOrderMap(fun, cur->next);
        fun(cur->element);
    }
}

template<typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun, const Node * cur) const {
    while(cur != nullptr) {
        fun(cur->element);
        cur = cur->next;
    }
}

template<typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun, const Node * cur) const {
    if(cur != nullptr) {
        PostOrderTraverse(fun, cur->next);
        fun(cur->element);
    }
}

}