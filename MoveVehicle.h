//
// Created by ofir shapira on 29/06/2023.
//

#ifndef OOP5_MOVEVEHICLE_H
#define OOP5_MOVEVEHICLE_H

#include "CellType.h"
#include "Direction.h"
#include "BoardCell.h"
#include "List.h"
#include "Utilities.h"
#include "BoardUtils.h"
#include "Provided/part2/TransposeList.h"
template<CellType cell,Direction dir,int N>
struct Move
{
    static_assert(cell==EMPTY,"Empty cell is not ok!\n");
    static constexpr CellType type = cell;
    static constexpr Direction direction = dir;
    static constexpr int amount = N;
};

template <typename Board,int R,int C,Direction D>
struct ValidIndexes
{
private:
    static_assert(R >=0 && R < Board::width, "Invalid Index");
    static_assert(C >=0 && C < Board::length, "Invalid Index");

    typedef GetAtIndex<R,typename Board::board> row;
    typedef GetAtIndex<C, row> cell;
    static_assert(cell::type == EMPTY, "Invalid Index");
    static_assert(cell::direction != D, "Invalid Direction");
};

template <typename Board,int R,int C, typename Cell>
struct GetLeft
{
private:
    typedef GetAtIndex<R,typename Board::board> row;
    typedef typename GetAtIndex<C, row>::value cell;
    static constexpr int next =  ConditionalInteger<C==0, C, GetLeft<Board, R, C-1,Cell>::left>::value;
public:
    static constexpr int left =   ConditionalInteger<IsSame<Cell,cell>::value, next, C>::value;

};


template <typename Board, int R,int C, typename Cell>
struct GetRight
{
private:
    typedef GetAtIndex<R,typename Board::board> row;
    typedef GetAtIndex<C, row> cell;
    static constexpr int next = ConditionalInteger<C==Board::length-1, C, GetRight<Board, R, C+1,Cell>::right>::value;
public:
    static constexpr int right =  ConditionalInteger<IsSame<Cell,cell>::value, next, C>::value;

};


template <typename Board, int R,int C, typename Cell>
struct CheckWin
{
private:
    typedef GetAtIndex<R,typename Board::board> row;
    typedef GetAtIndex<C, row> cell;
    static constexpr int next = ConditionalInteger<C==Board::length-1, true, CheckWin<Board, R, C+1,Cell>::win>::value;
public:
    static constexpr int win =  ConditionalInteger<IsSame<Cell,cell>::value, next, false>::value;


//struct get_Left ->
//struct get_right ->
//struct perform move
//struct valid index
//struct get cell


/*
template<typename ,int ,int,Direction,int > - Done
struct MoveVehicle
{
};*/


template <typename Board,int R,int C,Direction D>
struct PerformMove
{
private:
    typedef GetCellAtIndex<Board,R,C>  sourceCell;
    typedef GetCellAtIndex<Board,R,C>  destCell;

    static constexpr int carLength = sourceCell::length;
    static constexpr int newCol = ConditionalInteger<D == R, C +carLength,C-carLength>::value;

    static_assert(destCell::type != EMPTY,"The spot is taken bro\n");
    typedef typename SetCellAtIndex<Board,R,C,BoardCell<EMPTY,UP,0>>::board eraseBoard;

public:
    typedef typename SetCellAtIndex<eraseBoard,R,newCol,sourceCell>::board board;
};


template <typename Board,int R,int C,Direction D,int A>
struct PerformMoves
{
private:
    typedef typename PerformMove<Board,R,C,D>::board boardAfterMove;
public:
    typedef typename PerformMoves<boardAfterMove,R,C,D,A-1>::board board;
};

template <typename Board,int R,int C,Direction D>
struct PerformMoves<Board,R,C,D,0>
{
    typedef Board board;
};



template<typename Board,int R ,int C,int A,Direction D>
struct MoveVehicle{};

template<typename Board ,int R ,int C, int A>
struct MoveVehicle<Board, R , C, A,LEFT>
{
    ValidIndexes<Board,R,C,LEFT>;
public:
    typedef typename PerformMoves<Board,R,C,LEFT,A>::board board;

};
template<typename Board ,int R ,int C, int A>
struct MoveVehicle<Board, R , C, A,RIGHT>
{
    ValidIndexes<Board,R,C,RIGHT>;
public:
    typedef typename PerformMoves<Board,R,C,RIGHT,A>::board board;

};
template<typename Board ,int R ,int C, int A>
struct MoveVehicle<Board, R , C, A,UP>
{
private:

    typedef typename Transpose<typename Board::board>::matrix boardAsList;
    typedef typename GetAtIndex<C,boardAsList>::value row;
    typedef typename GetCellAtIndex<Board,C,R>::value cellDown;
    typedef  BoardCell<cellDown::type,LEFT,cellDown::amount> cellRight;

    static constexpr int dSide = GetLeft<boardAsList,C,R,cellDown>::value;
    static constexpr int USide = GetRight<boardAsList,C,R,cellDown>::value;

    static constexpr int dSideAfter = dSide + A ;
    static constexpr int USideAfter = USide +A   ;


    typedef typename MakeSwitch<typename Board::board,C,dSide,USide,cellRight>::matrix boardAfterSwitchPre;


    typedef MoveVehicle<boardAfterSwitchPre, C,R, A,LEFT> boardAfterMove;

    typedef typename MakeSwitch<boardAfterMove,C,dSideAfter,USideAfter,cellDown>::matrix boardAfterSwitchPost;


    typedef typename Transpose<typename boardAfterSwitchPost::board>::matrix finalTranspose;

public:
    typedef GameBoard<finalTranspose> board;

};



template<typename Board ,int R ,int C, int A>
struct MoveVehicle<Board, R , C, A,DOWN>
{
private:

    typedef typename Transpose<typename Board::board>::matrix boardAsList;
    typedef typename GetAtIndex<C,boardAsList>::value row;
    typedef typename GetCellAtIndex<Board,C,R>::value cellDown;
    typedef  BoardCell<cellDown::type,RIGHT,cellDown::amount> cellRight;

    static constexpr int dSide = GetLeft<boardAsList,C,R,cellDown>::value;
    static constexpr int USide = GetRight<boardAsList,C,R,cellDown>::value;

    static constexpr int dSideAfter = dSide + A;
    static constexpr int USideAfter = USide + A;


    typedef typename MakeSwitch<typename Board::board,C,dSide,USide,cellRight>::matrix boardAfterSwitchPre;


    typedef MoveVehicle<boardAfterSwitchPre, C,R, A,RIGHT> boardAfterMove;

    typedef typename MakeSwitch<boardAfterMove,C,dSideAfter,USideAfter,cellDown>::matrix boardAfterSwitchPost;


    typedef typename Transpose<typename boardAfterSwitchPost::board>::matrix finalTranspose;

public:
    typedef GameBoard<finalTranspose> board;

};





#endif //OOP5_MOVEVEHICLE_H
