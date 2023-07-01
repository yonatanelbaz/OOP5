//
// Created by ofir shapira on 29/06/2023.
//

#ifndef OOP5_RUSHHOUR_H
#define OOP5_RUSHHOUR_H

#include "BoardUtils.h"
#include "MoveVehicle.h"
#include "GameBoard.h"



template <typename Board, int R,int C>
struct CheckWinAux
{
private:
    typedef GetCellAtIndex<Board,R,C> cell;
    static constexpr int next = ConditionalInteger<C==Board::length-1, true, CheckWinAux<Board, R, C+1>::result>::value;
public:
    static constexpr int result =  ConditionalInteger<cell::type == EMPTY, next, false>::value;

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
    typedef typename FindCar<Board, X>::res indexes;//X is RED TYPE
    static constexpr int length = GetCellAtIndex<Board,indexes::row,indexes::col>::cell::length;
    static constexpr int row = indexes::row;
    static constexpr int col = indexes::clo + length;
public:
    static constexpr bool result =  CheckWinAux<Board,row,col>::result;
};

template<typename Board,typename L>
struct MakeAllMoves
{

};

template<typename Board,typename RowsHead, typename... RowsTail>
struct MakeAllMoves<Board,List<RowsHead,RowsTail...>>
{
private:
    typedef RowsHead CurrMove;
    typedef  List<> EmptyList;
    static constexpr int row = FindCar<Board, CurrMove::type>::res::row;
    static constexpr int col = FindCar<Board, CurrMove::type>::res::col;
    typedef typename MoveVehicle<Board, row,col, CurrMove::direction,CurrMove::amount>::board NewBoard;
public:
    typedef typename MakeAllMoves<Board,List<RowsTail...>>::board board;

};


template<typename Board>
struct MakeAllMoves<Board,List<>>
{
    typedef Board board;
};


template<typename Board, typename moves>
struct CheckSolution
{
private:
    typedef MakeAllMoves<Board, moves> BoardAfterMoves;
public:
    static constexpr bool result = CheckWin<BoardAfterMoves>::result;
};

#endif //OOP5_RUSHHOUR_H
