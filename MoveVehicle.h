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

template<typename X, typename Y>
struct IsSame
{
    static constexpr bool value = false;
};

template<typename X>
struct IsSame<X,X>
{
    static constexpr bool value = true;
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


template <typename Board,int R,int C>
struct GetCellAtIndex
{
private:
    typedef GetAtIndex<R,typename Board::board> row;
public:
    typedef GetAtIndex<C, row> cell;
};

template <typename Board,int R,int C,typename V>
struct SetCellAtIndex
{
private:
    typedef GetAtIndex<R,typename Board::board> oldRow;
    typedef SetAtIndex<C,V, oldRow> newCol;
public:
    typedef SetAtIndex<R,newCol, typename Board::board> board;

};



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
struct MoveVehicle<Board, R , C, A,UP>
{
private:

    typedef Transpose<typename Board::board> boardAsList;
    typedef GetAtIndex<C,boardAsList> row;


    static constexpr int lSide = getLeft<board

    typedef GameBoard<boardAsList> transposed;



    //make transpose
    //find left edge
    //find right edge
    //switch U to L`
    //apply as L
    typedef transposed
    //switch L to U
    // make transpose
}







#endif //OOP5_MOVEVEHICLE_H
