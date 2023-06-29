//
// Created by ofir shapira on 29/06/2023.
//

#ifndef OOP5_CHECKWIN_H
#define OOP5_CHECKWIN_H

#include "BoardUtils.h"

template<typename Board>
struct CheckWin
{
private:
    typedef typename FindRed<Board>::res indexes;
    static constexpr bool result =  CheckWinAux<Board,indexes::row,indexes::col>::res;
};

template<typename Board,int R,int C>
class CheckWinAux
{
private:
    typedef typename GetCellAtIndex<Board,R,C>::cell cell;
    static constexpr int length = cell::length;
    static constexpr int amount = Board::width-C-length;

public:
    static constexpr bool result = MoveVehicle<Board,R,C,amount>;
    //TODO: get a function who checks if available by boolean only without assert
    //Shouldn't be MoveVehicle who changes board and makes assert
};


template<typename Board>
class CheckWinAux<Board,NOT_FOUND,NOT_FOUND>
{
    static constexpr bool result = false;
};

#endif //OOP5_CHECKWIN_H
