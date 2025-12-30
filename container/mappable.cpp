
namespace lasd {

/* ************************************************************************** */
//MappableContainer

/* ************************************************************************** */
//PreOrderMappableContainer

template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun f){
    PreOrderMap(f);
}
/* ************************************************************************** */
//PostOrderMappableContainer

template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun f){
    PostOrderMap(f);
}

/* ************************************************************************** */

}
