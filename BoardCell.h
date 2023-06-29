#ifndef OOP5_BOARDCELL_H
#define OOP5_BOARDCELL_H

#include "CellType.h"
#include "Direction.h"
template<CellType type, Direction dir, int N>
struct BoardCell{
    typedef type type;
    typedef dir direction;
    typedef N length;

};
#endif //OOP5_BOARDCELL_H
