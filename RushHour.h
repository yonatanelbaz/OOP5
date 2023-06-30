//
// Created by ofir shapira on 29/06/2023.
//

#ifndef OOP5_RUSHHOUR_H
#define OOP5_RUSHHOUR_H

#include "MoveVehicle.h"
#include "GameBoard.h"



template <typename Board, int R,int C>
struct CheckWinAux
{
private:
    typedef GetAtIndex<R,typename Board::board> row;
    typedef GetAtIndex<C, row> cell;
    static constexpr int next = ConditionalInteger<C==Board::length-1, true, CheckLeftWay<Board, R, C+1>::win>::value;
public:
    //static constexpr int win =  ConditionalInteger<IsSame<Cell,cell>::value, next, false>::value;
    static constexpr int win =  ConditionalInteger<cell::type == EMPTY, next, false>::value;

};

template<typename Board>
class CheckWinAux<Board,NOT_FOUND,NOT_FOUND>
{
    static constexpr bool result = false;
};

template<typename Board>
struct CheckWin
{
private:
    typedef typename FindCar<Board, X>::res indexes;
    static constexpr int length = GetCellAtIndex<Board,indexes::row,indexes::col>::cell::length;
    static constexpr int row = indexes::row;
    static constexpr int col = indexes::clo + length;
    static constexpr bool result =  CheckWinAux<Board,row,col>::result;
};

template<typename Board, typename moves>
struct CheckSolution{
    typedef typename moves::head CurrMove;
    typedef typename CurrMove::type X;
    typedef typename List<> EmptyList;
    static constexpr int row = FindCar<Board, X>::res::row;
    typedef typename MoveVehicle<Board, X, CurrMove::direction, CurrMove::steps>::Board NewBoard;
    static constexpr int win =  ConditionalInteger<IsSame<EmptyList, moves::next>::value, CheckWin<Board>::result, CheckSolution<NewBoard>>::value;

};



#endif //OOP5_RUSHHOUR_H
