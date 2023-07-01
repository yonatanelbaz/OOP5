#ifndef OOP5_BOARDCELL_H
#define OOP5_BOARDCELL_H

#include "CellType.h"
#include "Direction.h"
template<CellType givenType, Direction dir, int N>
struct BoardCell{
    static constexpr CellType type=givenType;
    static constexpr Direction direction=dir;
    static constexpr int length =N;

};
#endif //OOP5_BOARDCELL_H
