//
// Created by ofir shapira on 29/06/2023.
//

#ifndef HW5_UTILITIES_H
#define HW5_UTILITIES_H

template<bool, typename, typename>
struct Conditional
{

};

template< typename T, typename F>
struct Conditional<true,T,F>
{
    typedef T value;
};


template< typename T, typename F>
struct Conditional<false,T,F>
{
    typedef F value;
};


template<bool, int, int>
struct ConditionalInteger
{

};

template< int T, int F>
struct ConditionalInteger<true,T,F>
{
    static constexpr int value = T;
};

template<int T, int F>
struct ConditionalInteger<false,T,F>
{
    static constexpr int value = F;
};


#endif //HW5_UTILITIES_H
