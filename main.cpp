#include <iostream>
#include "List.h"
#include "Int.h"
#include "Utilities.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    typedef List<Int<1>, Int<2>, Int<3>> list;
    typedef List<> emptyList;
    typedef typename SetAtIndex<0, Int<5>, list>::list listA; // = List<Int<5>,///Int<2>, Int<3>>
    typedef typename SetAtIndex<2, Int<7>, list>::list listB; // = List<Int<1>,//Int<2>, Int<7>>
    std::cout<<listA::head::value<<std::endl;
    std::cout<<listA::next::next::head::value<<std::endl;
    std::cout<<listB::head::value<<std::endl;
    std::cout<<listB::next::next::head::value<<std::endl;
    std::cout<< PrependList<Int<4>,emptyList>::list::size<<std::endl;
    std::cout<< typeid(listA).name()<<std::endl;
    std::cout<< typeid(listB).name()<<std::endl;

    int val = ConditionalInteger<(0 != 1), 0, 1>::value; // = 0
    std::cout<<val<<std::endl;
    val = ConditionalInteger<(0 == 1), 0, 1>::value; // = 1
    std::cout<<val<<std::endl;

    typedef typename Conditional<(0 != 1), Int<0>, Int<1>>::value test1; // = Int<0>
    std::cout<<test1::value<<std::endl;

    typedef typename Conditional<(0 == 1), Int<0>, Int<1>>::value test2; // = Int<1>
    std::cout<<test2::value<<std::endl;

}
