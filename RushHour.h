//
// Created by ofir shapira on 29/06/2023.
//

#ifndef OOP5_RUSHHOUR_H
#define OOP5_RUSHHOUR_H

#include "BoardUtils.h"
#include "MoveVehicle.h"
#include "GameBoard.h"



template <typename Board,int width, int R,int C>
struct CheckWinAux
{
private:
    typedef typename GetCellAtIndex<Board,R,C>::cell cell;
    static constexpr int next = CheckWinAux<Board,Board::width, R, C+1>::result;
public:
    static constexpr int result = ConditionalInteger<cell::type == EMPTY, next, false>::value;

};

template <typename Board,int R,int C>
struct CheckWinAux<Board,C,R,C>
{
    static constexpr bool result = true;
};
template<typename Board,int width>
class CheckWinAux<Board,width,NOT_FOUND,NOT_FOUND>
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
    static constexpr int col = indexes::col;
public:
    static constexpr bool result =  CheckWinAux<Board,Board::width,row,col+length>::result;
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
    typedef typename MakeAllMoves<NewBoard,List<RowsTail...>>::board board;
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
    typedef typename MakeAllMoves<Board, moves>::board BoardAfterMoves;
public:
    static constexpr bool result = CheckWin<BoardAfterMoves>::result;
};

#endif //OOP5_RUSHHOUR_H
