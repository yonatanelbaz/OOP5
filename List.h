//
// Created by ofir shapira on 29/06/2023.
//

#ifndef HW5_LIST_H
#define HW5_LIST_H

template<typename... TT>
struct List {};//primary


template<typename T, typename... TT>
struct List<T,TT... >
{
    static constexpr int size = sizeof...(TT)+1;
    typedef T head;
    typedef List<TT...> next;
};


template<>
struct List<>
{
    static constexpr int size = 0;
    typedef List<> next;
};

template<typename T,typename... TT>
struct PrependList
{
};

template<typename T,typename... TT>
struct PrependList<T,List<TT...>>
{
    typedef List<T,TT...> list;
};

template<typename T>
struct PrependList<T,List<>>
{
    typedef List<T> list;
};



template<int N,typename... TT>
struct GetAtIndex
{};


template<int N,typename... TT>
struct GetAtIndex<N,List<TT...>>
{
    typedef GetAtIndex<N-1, typename List<TT...>::next> value;
};

template<typename... TT>
struct GetAtIndex<0,List<TT...>>
{
    typedef typename List<TT...>::head value;
};





template<int N, typename T,typename... TT>
struct SetAtIndex{};



template<int N, typename T,typename... TT>
struct SetAtIndex<N,T,List<TT...>>
{
private:
    typedef typename List<TT...>::head head;
    typedef typename  SetAtIndex<N-1,T,typename List<TT...>::next>::list tail;
public:
    typedef typename PrependList<head,tail>::list list;
};

template< typename T,typename... TT>
struct SetAtIndex<0,T,List<TT...>>
{
public:
    typedef typename PrependList<T,typename List<TT...>::next>::list list;
};









#endif //HW5_LIST_H
