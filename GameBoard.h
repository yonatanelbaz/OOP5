//
// Created by Yonatan Elbaz on 29/06/2023.
//

#ifndef OOP5_GAMEBOARD_H
#define OOP5_GAMEBOARD_H

#include "List.h"
#include "BoardCell.h"

template<typename RowsHead, typename... RowsTail>
struct GameBoard
{

};


template<typename RowsHead, typename... RowsTail>
struct GameBoard<List<RowsHead, RowsTail...>>
{
    typedef List<RowsHead, RowsTail...> board;
    typedef typename RowsHead::size width;
    typedef typename board::size length;

};

#endif //OOP5_GAMEBOARD_H
