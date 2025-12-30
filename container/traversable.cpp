
namespace lasd {

/* ************************************************************************** */
// TraversableContainer
template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> f, Accumulator acc) const {
    Traverse([f, &acc](const Data & data) {
        acc = f(data, acc);
    }
            );
    return acc;
}

template <typename Data>
inline bool TraversableContainer<Data>::Exists(const Data & v) const noexcept  {
    bool exists = false;
    Traverse([v, &exists](const Data & data) {
        exists |= (data == v);
    });
    return exists;
}
/* ************************************************************************** */
//PreOrderTraversableContainer
template <typename Data>
template <typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> f, Accumulator acc) const {
    PreOrderTraverse([f, &acc](const Data & data) {
        acc = f(data, acc);
    });
    return acc;
}

template <typename Data>
inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun f) const {
    PreOrderTraverse(f);
}
/* ************************************************************************** */
//PostOrderTraversableContainer
template <typename Data>
template <typename Accumulator>
inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> f, Accumulator acc) const {
    PostOrderTraverse([f, &acc](const Data & data) {
        acc = f(data, acc);
    });
    return acc;
}

template <typename Data>
inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun f) const {
    PostOrderTraverse(f);
}

/* ************************************************************************** */

}
