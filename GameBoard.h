//
// Created by Yonatan Elbaz on 29/06/2023.
//

#ifndef OOP5_GAMEBOARD_H
#define OOP5_GAMEBOARD_H

#include "List.h"
#include "BoardCell.h"

template<List<List<T>> list, int W, int L>
struct GameBoard{
    typedef list board;
    typedef W width;
    typedef L length;

};

#endif //OOP5_GAMEBOARD_H
