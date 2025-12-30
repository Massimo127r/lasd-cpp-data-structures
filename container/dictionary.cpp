
namespace lasd {

/* ************************************************************************** */
template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &c) {
    bool all = true;
    c.Traverse([this, &all](const Data & data) {
        all &= Insert(data);
    });
    return all;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> &&c) {
    bool all = true;
    c.Map([this, &all](Data & data) {
        all &= Insert(std::move(data));
    });
    return all;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> &c) {
    bool all = true;
    c.Traverse([this, &all](const Data & data) {
        all &= Remove(data);
    });
    return all;
}
template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &c) {
    bool some = false;
    c.Traverse([this, &some](const Data & data) {
        some |= Insert(data);
    });
    return some;
}
template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> &&c) {
    bool some = false;
    c.Map([this, &some]( Data & data) {
        some |= Insert(std::move(data));
    });
    return some;
}
template <typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &c) {
    bool some = false;
    c.Traverse([this, &some](const Data & data) {
        some |= Remove(data);
    });
    return some;
}

/* ************************************************************************** */

}
