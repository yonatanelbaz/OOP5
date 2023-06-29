#ifndef OOP5_BOARDCELL_H
#define OOP5_BOARDCELL_H
#include "CellType.h"
#include "Direction.h"

template<CellType T, typename T2, typename T3>
struct BoardCell{
    typedef T type;
    typedef T2 direction;
    typedef T3 length;

};
#endif //OOP5_BOARDCELL_H
